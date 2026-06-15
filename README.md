# pairs_lib

Shared C++ utility library that underpins the rest of the PAIRS UAV stack. It collects the common building blocks — attitude/quaternion math, Kalman and signal filters, type-safe YAML parameter loading, geometry helpers, tf2 transformation wrappers, and convenience handlers for ROS publishers, subscribers, services, and timers — so that the control, estimation, and planning packages can depend on one consistent set of primitives.

## Branches

| Branch | ROS version | Build system |
|--------|-------------|--------------|
| `ros1` | ROS 1 Noetic | catkin |
| `ros2` | ROS 2 Jazzy | ament_cmake |

## Contents

Compiled libraries:

| Library | Description |
|---------|-------------|
| `PairsLib_AttitudeConverter` | Euler/quaternion/rotation-matrix conversions |
| `PairsLib_Transformer` | tf2 wrapper with frame-aware transforms |
| `PairsLib_TransformBroadcaster` | tf2 broadcaster wrapper |
| `PairsLib_ParamLoader` / `PairsLib_ParamProvider` | YAML parameter loading with type-safe defaults |
| `PairsLib_Geometry` | 3D geometry: shapes, cyclic math, conversions |
| `PairsLib_SafetyZone` | Polygon-based safety-area checking |
| `PairsLib_Profiler` | Callback timing profiler |
| `PairsLib_ScopeTimer` | Scoped execution timer |
| `PairsLib_Timer` | ROS-rate-aware timer abstractions |
| `PairsLib_TimeoutManager` | Callback timeout tracking |
| `PairsLib_IirFilter` | IIR digital filter |
| `PairsLib_NotchFilter` | Notch filter for vibration rejection |
| `PairsLib_MedianFilter` | Sliding-window median filter |
| `PairsLib_Math` | Math utilities (probit, statistics) |
| `PairsLib_Utils` | Miscellaneous ROS utilities |
| `PairsLib_BatchVisualizer` | RViz marker batch publisher |
| `PairsLib_ImagePublisher` | Throttled image publisher |
| `PairsLib_DynamicPublisher` | Type-erased dynamic topic publisher |
| `PairsLib_OdomLKF` | Linear Kalman filter for odometry |

Header-only utilities live under `include/pairs_lib/` — Kalman-family estimators (LKF, UKF, NCKF, DKF, JLKF), RHEIV fitting, the repredictor for delayed measurements, and the subscribe/publisher/service handlers and vector converters. The `src/*/example.cpp` files double as runnable usage demos.

## Install (ROS 1 Noetic)

```bash
sudo apt install ros-noetic-pairs-lib
```

## License

BSD 3-Clause. Derived from the CTU-MRS `pairs_lib` package; the original copyright is retained in [LICENSE](LICENSE).
