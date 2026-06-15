# pairs_lib

PAIRS shared C++ utility library — attitude math, filters, parameter loading, geometry utilities, ROS transformations.

## Branches

| Branch | ROS version | Build system |
|--------|-------------|--------------|
| `ros1` | ROS 1 Noetic | catkin |
| `ros2` | ROS 2 Jazzy | ament_cmake |

## Libraries

| Library | Description |
|---------|-------------|
| `PairsLib_AttitudeConverter` | Euler/quaternion/rotation-matrix conversions |
| `PairsLib_Transformer` | ROS tf2 wrapper with frame-aware transforms |
| `PairsLib_ParamLoader` | YAML parameter loading with type-safe defaults |
| `PairsLib_Geometry` | 3D geometry utilities: shapes, cyclic math, projections |
| `PairsLib_SafetyZone` | Polygon-based safety area checking |
| `PairsLib_Profiler` | Callback timing profiler |
| `PairsLib_ScopeTimer` | Scoped execution timer |
| `PairsLib_IirFilter` | IIR digital filter |
| `PairsLib_NotchFilter` | Notch filter for vibration rejection |
| `PairsLib_MedianFilter` | Sliding-window median filter |
| `PairsLib_Math` | Math utilities (probit, statistics) |
| `PairsLib_Utils` | Miscellaneous ROS utilities |
| `PairsLib_BatchVisualizer` | RViz marker batch publisher |
| `PairsLib_Timer` | ROS-rate-aware timer abstractions |
| `PairsLib_TransformBroadcaster` | tf2 broadcaster wrapper |
| `PairsLib_TimeoutManager` | Callback timeout tracking |
| `PairsLib_DynamicPublisher` | Type-erased dynamic topic publisher |
| `PairsLib_ImagePublisher` | Throttled image publisher |
| `PairsLib_OdomLKF` | Linear Kalman filter for odometry |

Header-only utilities (Kalman filters, UKF/LKF/NCKF/DKF, RHEIV, repredictor, subscribe/publisher/service handlers, vector converters) live under `include/pairs_lib/`.

## License

BSD 3-Clause. Derived from the CTU-MRS `pairs_lib` package; the original copyright is retained in [LICENSE](LICENSE).
