cmake_minimum_required(VERSION 3.1.2)
project(pairs_lib)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_definitions(-Wall)
add_definitions(-Wextra)
add_definitions(-Wpedantic)

if(COVERAGE)
  message(WARNING "building with --coverage, the performance might be limited")
  set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} --coverage")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --coverage")
endif()

set(PCL_FIND_QUIETLY INTERNAL)

set(CATKIN_DEPENDENCIES
  cmake_modules
  cv_bridge
  geometry_msgs
  image_transport
  pairs_msgs
  nav_msgs
  pcl_conversions
  pcl_msgs
  pcl_ros
  roscpp
  sensor_msgs
  std_msgs
  tf2
  tf2_geometry_msgs
  tf_conversions
  visualization_msgs
  )

find_package(catkin REQUIRED COMPONENTS ${CATKIN_DEPENDENCIES})
find_package(yaml-cpp REQUIRED)
find_package(Eigen3 REQUIRED)
set(Eigen_INCLUDE_DIRS ${EIGEN3_INCLUDE_DIRS})
set(Eigen_LIBRARIES ${EIGEN3_LIBRARIES})
find_package(OpenCV REQUIRED HINTS /usr/local/lib)

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

catkin_package(
  INCLUDE_DIRS include
  CATKIN_DEPENDS ${CATKIN_DEPENDENCIES}
  DEPENDS Eigen YAML_CPP
  LIBRARIES ${LIBRARIES}
  )

include_directories(
  include
  ${catkin_INCLUDE_DIRS}
  ${Eigen_INCLUDE_DIRS}
  ${OpenCV_INCLUDE_DIRS}
  ${pcl_ros_INCLUDE_DIRS}
  ${YAML_CPP_INCLUDE_DIRS}
  )

## -------------------------------------------------------
## |                    Libraries                        |
## -------------------------------------------------------

add_library(PairsLib_SafetyZone
  src/safety_zone/safety_zone.cpp
  src/safety_zone/line_operations.cpp
  src/safety_zone/polygon/polygon.cpp
  )

add_library(PairsLib_Profiler
  src/profiler/profiler.cpp
  )

add_library(PairsLib_ScopeTimer
  src/scope_timer/scope_timer.cpp
  )

add_library(PairsLib_IirFilter
  src/iir_filter/iir_filter.cpp
  )

add_library(PairsLib_NotchFilter
  src/notch_filter/notch_filter.cpp
  )

add_library(PairsLib_Utils
  src/utils/utils.cpp
  )

add_library(PairsLib_ParamProvider
  src/param_loader/param_provider.cpp
  )

add_library(PairsLib_ParamLoader
  src/param_loader/param_loader.cpp
  )

add_library(PairsLib_MedianFilter
  src/median_filter/median_filter.cpp
  )

add_library(PairsLib_OdomLKF
  src/lkf/LKF_PAIRS_odom.cpp
  )

add_library(PairsLib_Geometry
  src/geometry/misc.cpp
  src/geometry/cyclic.cpp
  src/geometry/shapes.cpp
  src/geometry/conversions.cpp
  )

add_library(PairsLib_BatchVisualizer
  src/batch_visualizer/batch_visualizer.cpp
  src/batch_visualizer/visual_object.cpp
  )

add_library(PairsLib_AttitudeConverter
  src/attitude_converter/attitude_converter.cpp
  )

add_library(PairsLib_Transformer
  src/transformer/transformer.cpp
  )

add_library(PairsLib_ImagePublisher
  src/image_publisher/image_publisher.cpp
  )

add_library(PairsLib_Timer
  src/timer/timer.cpp
  )

add_library(PairsLib_TransformBroadcaster
  src/transform_broadcaster/transform_broadcaster.cpp
  )

add_library(PairsLib_Math
  src/math/math.cpp
  )

add_library(PairsLib_DynamicPublisher
  src/dynamic_publisher/dynamic_publisher.cpp
  )

add_library(PairsLib_TimeoutManager
  src/timeout_manager/timeout_manager.cpp
  )

foreach(target ${LIBRARIES})
  add_dependencies(${target}
    ${${PROJECT_NAME}_EXPORTED_TARGETS}
    ${catkin_EXPORTED_TARGETS}
    )
  target_link_libraries(${target}
    ${catkin_LIBRARIES}
    ${Eigen_LIBRARIES}
    ${OpenCV_LIBRARIES}
    yaml-cpp
    )
endforeach()

## -------------------------------------------------------
## |                     Testing                         |
## -------------------------------------------------------

if(CATKIN_ENABLE_TESTING AND PAIRS_ENABLE_TESTING)
  message(WARNING "Testing enabled.")
  add_subdirectory(test)
endif()

## -------------------------------------------------------
## |                     Install                         |
## -------------------------------------------------------

install(TARGETS ${LIBRARIES}
  ARCHIVE DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
  LIBRARY DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
  RUNTIME DESTINATION ${CATKIN_GLOBAL_BIN_DESTINATION}
  )

install(DIRECTORY include/pairs_lib/
  DESTINATION ${CATKIN_PACKAGE_INCLUDE_DESTINATION}
  )
