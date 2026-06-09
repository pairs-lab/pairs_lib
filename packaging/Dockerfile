# Toolchain image for building ROS 1 Noetic .deb packages for pairs_lib.
# Noetic only runs on Ubuntu 20.04, so we build inside this container
# regardless of the host OS (e.g. Ubuntu 24.04).
FROM ros:noetic-ros-base

ENV DEBIAN_FRONTEND=noninteractive

RUN apt-get update && apt-get install -y --no-install-recommends \
      python3-bloom \
      python3-rosdep \
      python3-catkin-pkg \
      fakeroot \
      debhelper \
      dh-python \
      git \
 && rm -rf /var/lib/apt/lists/*

# rosdep is already initialized in the base image; just make sure it can update.
WORKDIR /ws
COPY build_deb.sh /usr/local/bin/build_deb.sh
RUN chmod +x /usr/local/bin/build_deb.sh

ENTRYPOINT ["/usr/local/bin/build_deb.sh"]
