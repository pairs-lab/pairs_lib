cmake_minimum_required(VERSION 3.8)
project(pairs_lib)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(ament_cmake REQUIRED)
find_package(pairs_msgs REQUIRED)
find_package(geometry_msgs REQUIRED)
find_package(nav_msgs REQUIRED)
find_package(rclcpp REQUIRED)
find_package(sensor_msgs REQUIRED)
find_package(std_msgs REQUIRED)
find_package(tf2 REQUIRED)
find_package(tf2_geometry_msgs REQUIRED)
find_package(tf2_ros REQUIRED)
find_package(visualization_msgs REQUIRED)
find_package(cv_bridge REQUIRED)
find_package(image_transport REQUIRED)
find_package(pcl_conversions REQUIRED)
find_package(Eigen3 REQUIRED)
find_package(yaml-cpp REQUIRED)
find_package(OpenCV REQUIRED)

set(DEPS
  pairs_msgs geometry_msgs nav_msgs rclcpp sensor_msgs std_msgs
  tf2 tf2_geometry_msgs tf2_ros visualization_msgs
  cv_bridge image_transport pcl_conversions
  )

set(LIBRARIES
  PairsLib_SafetyZone
  PairsLib_Profiler
  PairsLib_ScopeTimer
  PairsLib_IirFilter
  PairsLib_NotchFilter
  PairsLib_Utils
  PairsLib_ParamProvider
  PairsLib_ParamLoader
  PairsLib_MedianFilter
  PairsLib_OdomLKF
  PairsLib_Geometry
  PairsLib_BatchVisualizer
  PairsLib_AttitudeConverter
  PairsLib_Transformer
  PairsLib_ImagePublisher
  PairsLib_Timer
  PairsLib_TransformBroadcaster
  PairsLib_Math
  PairsLib_DynamicPublisher
  PairsLib_TimeoutManager
  )

# --- Library definitions ---

add_library(PairsLib_SafetyZone
  src/safety_zone/safety_zone.cpp
  src/safety_zone/line_operations.cpp
  src/safety_zone/polygon/polygon.cpp
  )
add_library(PairsLib_Profiler       src/profiler/profiler.cpp)
add_library(PairsLib_ScopeTimer     src/scope_timer/scope_timer.cpp)
add_library(PairsLib_IirFilter      src/iir_filter/iir_filter.cpp)
add_library(PairsLib_NotchFilter    src/notch_filter/notch_filter.cpp)
add_library(PairsLib_Utils          src/utils/utils.cpp)
add_library(PairsLib_ParamProvider  src/param_loader/param_provider.cpp)
add_library(PairsLib_ParamLoader    src/param_loader/param_loader.cpp)
add_library(PairsLib_MedianFilter   src/median_filter/median_filter.cpp)
add_library(PairsLib_OdomLKF        src/lkf/LKF_PAIRS_odom.cpp)
add_library(PairsLib_Geometry
  src/geometry/misc.cpp src/geometry/cyclic.cpp
  src/geometry/shapes.cpp src/geometry/conversions.cpp
  )
add_library(PairsLib_BatchVisualizer
  src/batch_visualizer/batch_visualizer.cpp
  src/batch_visualizer/visual_object.cpp
  )
add_library(PairsLib_AttitudeConverter src/attitude_converter/attitude_converter.cpp)
add_library(PairsLib_Transformer    src/transformer/transformer.cpp)
add_library(PairsLib_ImagePublisher src/image_publisher/image_publisher.cpp)
add_library(PairsLib_Timer          src/timer/timer.cpp)
add_library(PairsLib_TransformBroadcaster src/transform_broadcaster/transform_broadcaster.cpp)
add_library(PairsLib_Math           src/math/math.cpp)
add_library(PairsLib_DynamicPublisher src/dynamic_publisher/dynamic_publisher.cpp)
add_library(PairsLib_TimeoutManager src/timeout_manager/timeout_manager.cpp)

foreach(target ${LIBRARIES})
  target_include_directories(${target} PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
    ${EIGEN3_INCLUDE_DIRS}
    )
  ament_target_dependencies(${target} ${DEPS})
  target_link_libraries(${target} yaml-cpp ${OpenCV_LIBRARIES})
endforeach()

## -------------------------------------------------------
## |                     Install                         |
## -------------------------------------------------------

install(TARGETS ${LIBRARIES}
  EXPORT export_${PROJECT_NAME}
  ARCHIVE DESTINATION lib
  LIBRARY DESTINATION lib
  RUNTIME DESTINATION bin
  )

install(DIRECTORY include/
  DESTINATION include
  )

ament_export_targets(export_${PROJECT_NAME} HAS_LIBRARY_TARGET)
ament_export_dependencies(${DEPS})

ament_package()
