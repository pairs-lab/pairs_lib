#!/usr/bin/env bash
#
# Runs INSIDE the ros:jazzy packaging container (see Dockerfile).
# Builds Debian packages for pairs_msgs (dependency) and pairs_lib, in order,
# and copies the resulting .deb files to /output.
#
# Expected mounts (handled by make.sh):
#   /src     -> the colcon src/ directory containing pairs_lib/ and pairs_msgs/
#   /output  -> host directory where built .deb files are collected
#
set -eo pipefail

ROS_DISTRO_NAME="jazzy"
OS_NAME="ubuntu"
OS_VERSION="noble"     # Jazzy targets Ubuntu 24.04 (noble)

# ROS setup scripts reference unbound vars, so source before enabling nounset.
source "/opt/ros/${ROS_DISTRO_NAME}/setup.bash"
set -u

# --- register local rosdep rules so pairs_* deps resolve -------------------
LOCAL_RULES="/src/pairs_lib/packaging/rosdep/pairs.yaml"
echo "yaml file://${LOCAL_RULES}" | sudo tee /etc/ros/rosdep/sources.list.d/10-pairs.list >/dev/null
rosdep update

# The base image ships with an empty apt index; refresh it so rosdep can
# apt-install build dependencies.
sudo apt-get update

mkdir -p /output

# build_one <package_dir>
build_one() {
  local pkg_dir="$1"
  local pkg_name
  pkg_name="$(basename "$pkg_dir")"

  echo "=================================================================="
  echo " Building Debian package for: ${pkg_name}"
  echo "=================================================================="

  # Work on a clean copy so we never dirty the mounted source tree.
  local work="/ws/${pkg_name}"
  rm -rf "$work"
  cp -a "$pkg_dir" "$work"
  cd "$work"
  rm -rf debian obj-*  # stale artifacts

  # Pull any apt-resolvable build deps for this package.
  rosdep install --from-paths . --ignore-src -r -y || true

  # Generate debian/ and build the binary .deb.
  bloom-generate rosdebian --os-name "$OS_NAME" --os-version "$OS_VERSION" --ros-distro "$ROS_DISTRO_NAME"
  fakeroot debian/rules binary

  # Collect + locally install so downstream packages can depend on it.
  local deb
  for deb in /ws/ros-${ROS_DISTRO_NAME}-*"${pkg_name//_/-}"*.deb ../ros-${ROS_DISTRO_NAME}-*.deb; do
    [ -f "$deb" ] || continue
    cp -v "$deb" /output/
    apt-get install -y "$deb" || dpkg -i "$deb" || true
  done
}

# Order matters: pairs_msgs first (pairs_lib depends on it).
if [ -d /src/pairs_msgs ]; then
  build_one /src/pairs_msgs
else
  echo "WARNING: /src/pairs_msgs not found; pairs_lib build may fail on the pairs_msgs dependency." >&2
fi

build_one /src/pairs_lib

echo "=================================================================="
echo " Done. Built packages in /output:"
ls -1 /output/*.deb
echo "=================================================================="
