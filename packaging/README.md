# Packaging pairs_lib as an apt-installable ROS 1 (Noetic) package

> **Why a self-hosted apt repo?** ROS Noetic reached end-of-life in May 2025, so
> the official ROS build farm (`packages.ros.org`) no longer accepts new Noetic
> releases. To let users `sudo apt-get install ros-noetic-pairs-lib`, we build the
> Debian package ourselves and serve it from our own apt repository.

Noetic only runs on Ubuntu 20.04, so the `.deb` is built inside a `ros:noetic`
Docker container — this works on any host OS (including Ubuntu 24.04).

## 1. Build the .deb packages

```bash
cd pairs_lib/packaging
./make.sh
```

This builds, in order:
1. `ros-noetic-pairs-msgs_*.deb`  (dependency)
2. `ros-noetic-pairs-lib_*.deb`

Artifacts land in `pairs_lib/packaging/output/`.

> The build reads the **currently checked-out** `pairs_lib/` and `pairs_msgs/`
> working copies (both must be on the `ros1` branch). `pairs_msgs/` must sit next
> to `pairs_lib/` in the same `src/` directory.

## 2. Host an apt repository

Any static file host works (a VM, S3, GitHub Pages, GitLab Pages…). The simplest
is a flat repo served over HTTP. Using [`aptly`](https://www.aptly.info):

```bash
sudo apt-get install -y aptly
aptly repo create -distribution=focal -component=main pairs
aptly repo add pairs pairs_lib/packaging/output/*.deb
aptly publish repo pairs            # signs + lays out the repo under ~/.aptly/public
# then serve ~/.aptly/public/ over HTTP (nginx, `aptly serve`, GitHub Pages, ...)
```

Or, for an unsigned quick-and-dirty repo (lab/internal use only):

```bash
cd pairs_lib/packaging/output
dpkg-scanpackages . /dev/null | gzip -9c > Packages.gz
# serve this directory over HTTP; users add [trusted=yes] (see below)
```

## 3. What your users run

Once the repo is hosted at e.g. `https://apt.pairs-lab.example/noetic`:

```bash
# add the PAIRS apt source (replace URL with your host)
echo "deb [trusted=yes] https://apt.pairs-lab.example/noetic focal main" \
  | sudo tee /etc/apt/sources.list.d/pairs.list

sudo apt-get update
sudo apt-get install ros-noetic-pairs-lib   # pulls ros-noetic-pairs-msgs automatically
```

(For a signed repo, drop `[trusted=yes]` and have users import your GPG public key
into `/etc/apt/trusted.gpg.d/` instead.)

## Notes
- Bump `<version>` in `package.xml` for each release so apt sees an upgrade.
- The local rosdep rules in `rosdep/pairs.yaml` let `bloom`/`rosdep` resolve the
  `pairs_msgs` → `ros-noetic-pairs-msgs` dependency during the build.
- For the ROS 2 (Jazzy) package, see `packaging/` on the `ros2` branch — Jazzy is
  still supported, so it can additionally go through the **official** ROS index.
