# Route A — Official release to the ROS index (ROS 2 Jazzy)

This makes `sudo apt install ros-jazzy-pairs-lib` work for everyone off
`packages.ros.org`, built and hosted by the official ROS build farm. You do this
**once** per package; subsequent versions are a single `bloom-release` call.

> Prerequisite: `pairs_msgs` must be released the same way **first** (pairs_lib
> depends on it, and the build farm needs the dependency to already exist in the
> Jazzy distribution).

## One-time setup

```bash
sudo apt-get install -y python3-bloom
# A GitHub account with push access to the github.com/pairs-lab org.
```

## Per-package release

1. Make sure the source repo is pushed and tagged, with `<version>` in
   `package.xml` bumped and a matching `CHANGELOG.rst` entry.

2. Run bloom-release (creates/uses a `pairs_lib-release` repo and opens a PR to
   `ros/rosdistro`):

   ```bash
   bloom-release pairs_lib --rosdistro jazzy --track jazzy
   ```

   On first run it asks for:
   - the upstream repo URL: `https://github.com/pairs-lab/pairs_lib.git`
   - the upstream branch/tag to release from: `ros2`
   - a release repo (let it create `https://github.com/pairs-lab/pairs_lib-release`)

3. bloom pushes the release repo and opens a pull request against
   [`ros/rosdistro`](https://github.com/ros/rosdistro) adding pairs_lib to the
   `jazzy/distribution.yaml`.

4. A ROS maintainer reviews and merges the PR. Within a day or two the build farm
   builds `ros-jazzy-pairs-lib` for all supported platforms and publishes it to
   `packages.ros.org`.

## Requirements the build farm enforces
- `package.xml` is **format 3**, valid, with a real maintainer + email and an
  OSI license (BSD 3-Clause ✓).
- Every dependency is itself resolvable in the Jazzy index (hence: release
  `pairs_msgs` first).
- The package builds cleanly with `colcon build` from a clean checkout.

## Subsequent releases
Just bump `<version>`, update `CHANGELOG.rst`, push, then:
```bash
bloom-release pairs_lib --rosdistro jazzy --track jazzy
```
and merge the auto-opened rosdistro PR.

---

For ROS 1 Noetic there is **no Route A** — Noetic is end-of-life on
`packages.ros.org`. Use the self-hosted apt repo (`ros1` branch `packaging/`).
