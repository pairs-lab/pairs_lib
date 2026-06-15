# pairs_lib

Shared C++ utility library that underpins the rest of the PAIRS UAV stack. It collects the common building blocks — attitude/quaternion math, Kalman and signal filters, type-safe parameter loading, geometry helpers, tf2 transformation wrappers, and convenience handlers for publishers, subscribers, services, and timers — so the control, estimation, and planning packages can share one consistent set of primitives.

This is the **ros2** branch (ROS 2 Jazzy, ament_cmake). For ROS 1 Noetic (catkin), see the `ros1` branch.

## Branches

| Branch | ROS version | Build system |
|--------|-------------|--------------|
| `ros1` | ROS 1 Noetic | catkin |
| `ros2` | ROS 2 Jazzy | ament_cmake |

## Contents

- A single shared library, `pairs_lib::pairs_lib`, exporting the full set of utilities: attitude converter, transformer and transform broadcaster, parameter loader/provider, geometry, safety zone, profiler, scope timer, timer handler, timeout manager, IIR/notch/median filters, math, batch visualizer, and message extractors.
- Header-only estimators and helpers under `include/pairs_lib/` — Kalman-family filters (LKF, UKF, NCKF, DKF), the repredictor for delayed measurements, error-graph utilities, and the subscriber/publisher/service handlers.
- A small Python module (`pairs_lib/`) with launch-time helpers for custom-config path sanitizing and remappings parsing.
- Runnable usage demos under `examples/`.

## Install (ROS 2 Jazzy)

```bash
sudo apt install ros-jazzy-pairs-lib
```

## License

BSD 3-Clause. Derived from the CTU-MRS package; the original copyright is retained in [LICENSE](LICENSE).
