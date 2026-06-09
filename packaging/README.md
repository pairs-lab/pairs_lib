# Packaging pairs_lib as an apt-installable ROS 2 (Jazzy) package

ROS 2 Jazzy is actively supported, so you have **two** ways to ship pairs_lib:

| Route | Result | Effort |
|-------|--------|--------|
| **A — Official ROS index** | `sudo apt install ros-jazzy-pairs-lib` for everyone, worldwide, off `packages.ros.org` | one-time `bloom-release` + a PR to `ros/rosdistro` |
| **B — Self-hosted apt repo** | `apt install ros-jazzy-pairs-lib` after users add your repo | build `.deb` locally + host it |

See [RELEASING.md](RELEASING.md) for Route A. Route B is below.

---

## Route B — build the .deb yourself

```bash
cd pairs_lib/packaging
./make.sh
```

Builds, in order:
1. `ros-jazzy-pairs-msgs_*.deb`  (dependency)
2. `ros-jazzy-pairs-lib_*.deb`

Artifacts land in `pairs_lib/packaging/output/`.

> The build reads the **currently checked-out** `pairs_lib/` and `pairs_msgs/`
> working copies (both must be on the `ros2` branch), sitting side by side in the
> same `src/` directory.

### Host an apt repository

```bash
sudo apt-get install -y aptly
aptly repo create -distribution=noble -component=main pairs
aptly repo add pairs pairs_lib/packaging/output/*.deb
aptly publish repo pairs           # serve ~/.aptly/public/ over HTTP
```

### What your users run

```bash
echo "deb [trusted=yes] https://apt.pairs-lab.example/jazzy noble main" \
  | sudo tee /etc/apt/sources.list.d/pairs.list
sudo apt-get update
sudo apt-get install ros-jazzy-pairs-lib   # pulls ros-jazzy-pairs-msgs automatically
```

## Notes
- Bump `<version>` in `package.xml` for each release.
- `rosdep/pairs.yaml` lets bloom resolve the `pairs_msgs` → `ros-jazzy-pairs-msgs`
  dependency during the build.
- For ROS 1 Noetic, see `packaging/` on the `ros1` branch (self-hosted only — Noetic
  is EOL on `packages.ros.org`).
