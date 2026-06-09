cmake_minimum_required(VERSION 3.28)
project(pairs_lib)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_definitions("-Wall")
add_definitions("-Wextra")
add_definitions("-Wpedantic")

# 1 == use rclcpp::Timer implementation
# 0 == use MRS's thread timer implementation
set(USE_ROS_TIMER 0)

if(${USE_ROS_TIMER})
  MESSAGE(WARNING "[pairs_lib]: Compiling with ROS Timers. This can cause high CPU load in runtime.")
endif()

if(ENABLE_COVERAGE)
  message(WARNING "building for coverage, the performance might be limited")

  set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} --coverage -fprofile-arcs")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --coverage -fprofile-arcs")

  add_definitions("-O1")
  add_definitions("-g")
endif()

find_package(ament_cmake_python REQUIRED)
find_package(mrs_cmake REQUIRED)

set(DEPENDENCIES
  geometry_msgs
  pairs_msgs
  nav_msgs
  # pcl_conversions
  # pcl_msgs
  # pcl_ros
  rclcpp
  rclcpp_components
  std_msgs
  tf2_geometry_msgs
  tf2_ros
  tf2_eigen
  yaml-cpp
  visualization_msgs
  Eigen3
  yaml-cpp
  Boost
)

foreach(DEP IN LISTS DEPENDENCIES)
  find_package(${DEP} REQUIRED)
endforeach()

# find_package(OpenCV REQUIRED HINTS /usr/local/lib)

## --------------------------------------------------------------
## |                       compile                              |
## --------------------------------------------------------------

add_library(pairs_lib_pairs_lib SHARED)
add_library(pairs_lib::pairs_lib ALIAS pairs_lib_pairs_lib)
set_target_properties(pairs_lib_pairs_lib
  PROPERTIES
    EXPORT_NAME pairs_lib
    OUTPUT_NAME pairs_lib
)

target_sources(pairs_lib_pairs_lib
  PRIVATE
    # src/attitude_converter
    "src/attitude_converter/attitude_converter.cpp"
    # src/batch_visualizer
    "src/batch_visualizer/batch_visualizer.cpp"
    "src/batch_visualizer/visual_object.cpp"
    # src/coro/internal
    "src/coro/internal/thread_local_continuation_scheduler.cpp"
    # src/dynparam_mgr
    "src/dynparam_mgr/dynparam_mgr.cpp"
    # src/errorgraph
    "src/errorgraph/errorgraph.cpp"
    "src/errorgraph/error_publisher.cpp"
    # src/geometry
    "src/geometry/conversions.cpp"
    "src/geometry/cyclic.cpp"
    "src/geometry/misc.cpp"
    "src/geometry/shapes.cpp"
    # src/iir_filter
    "src/iir_filter/iir_filter.cpp"
    # src/math
    "src/math/math.cpp"
    # src/median_filter
    "src/median_filter/median_filter.cpp"
    # src/msg_extractor
    "src/msg_extractor/msg_extractor.cpp"
    # src/notch_filter
    "src/notch_filter/notch_filter.cpp"
    # src/param_loader
    "src/param_loader/param_loader.cpp"
    # src/param_provider
    "src/param_provider/param_provider.cpp"
    # src/profiler
    "src/profiler/profiler.cpp"
    # src/safety_zone
    "src/safety_zone/line_operations.cpp"
    "src/safety_zone/polygon.cpp"
    "src/safety_zone/prism.cpp"
    "src/safety_zone/safety_zone.cpp"
    "src/safety_zone/static_edges_visualization.cpp"
    # src/scope_timer
    "src/scope_timer/scope_timer.cpp"
    # src/timeout_manager
    "src/timeout_manager/timeout_manager.cpp"
    # src/timer_handler
    "src/timer_handler/timer_handler.cpp"
    # src/transform_broadcaster
    "src/transform_broadcaster/transform_broadcaster.cpp"
    # src/transformer
    "src/transformer/transformer.cpp"
    # src/utils
    "src/utils/utils.cpp"
  PUBLIC FILE_SET HEADERS BASE_DIRS "include"
  FILES
    # include/pairs_lib
    "include/pairs_lib/attitude_converter.h"
    "include/pairs_lib/batch_visualizer.h"
    "include/pairs_lib/dkf.h"
    "include/pairs_lib/dynparam_mgr.h"
    "include/pairs_lib/gps_conversions.h"
    "include/pairs_lib/iir_filter.h"
    "include/pairs_lib/integration_test.h"
    "include/pairs_lib/kalman_filter.h"
    "include/pairs_lib/lkf.h"
    "include/pairs_lib/lockable.h"
    "include/pairs_lib/math.h"
    "include/pairs_lib/median_filter.h"
    "include/pairs_lib/pairs_lib.h"
    "include/pairs_lib/msg_extractor.h"
    "include/pairs_lib/mutex.h"
    "include/pairs_lib/nckf.h"
    "include/pairs_lib/node.h"
    "include/pairs_lib/notch_filter.h"
    "include/pairs_lib/param_loader.h"
    "include/pairs_lib/param_provider.h"
    "include/pairs_lib/profiler.h"
    "include/pairs_lib/publisher_handler.h"
    "include/pairs_lib/quadratic_throttle_model.h"
    "include/pairs_lib/repredictor.h"
    "include/pairs_lib/safety_zone.h"
    "include/pairs_lib/scope_timer.h"
    "include/pairs_lib/service_client_handler.h"
    "include/pairs_lib/service_server_handler.h"
    "include/pairs_lib/subscriber_handler.h"
    "include/pairs_lib/timeout_manager.h"
    "include/pairs_lib/timer_handler.h"
    "include/pairs_lib/transform_broadcaster.h"
    "include/pairs_lib/transformer.h"
    "include/pairs_lib/ukf.h"
    "include/pairs_lib/utils.h"
    "include/pairs_lib/visual_object.h"
    # include/pairs_lib/coro
    "include/pairs_lib/coro/runners.hpp"
    "include/pairs_lib/coro/task.hpp"
    "include/pairs_lib/coro/task.impl.hpp"
    # include/pairs_lib/coro/internal
    "include/pairs_lib/coro/internal/attributes.hpp"
    "include/pairs_lib/coro/internal/thread_local_continuation_scheduler.hpp"
    # include/pairs_lib/errorgraph
    "include/pairs_lib/errorgraph/node_id.h"
    "include/pairs_lib/errorgraph/errorgraph.h"
    "include/pairs_lib/errorgraph/error_publisher.h"
    # include/pairs_lib/geometry
    "include/pairs_lib/geometry/conversions_eigen.h"
    "include/pairs_lib/geometry/conversions.h"
    "include/pairs_lib/geometry/cyclic.h"
    "include/pairs_lib/geometry/misc.h"
    "include/pairs_lib/geometry/shapes.h"
    # include/pairs_lib/impl
    "include/pairs_lib/impl/dynparam_mgr.hpp"
    "include/pairs_lib/impl/param_loader.hpp"
    "include/pairs_lib/impl/param_provider.hpp"
    "include/pairs_lib/impl/publisher_handler.hpp"
    "include/pairs_lib/impl/service_client_handler.hpp"
    "include/pairs_lib/impl/service_server_handler.hpp"
    "include/pairs_lib/impl/subscriber_handler.hpp"
    "include/pairs_lib/impl/timer_handler.hpp"
    "include/pairs_lib/impl/transformer.hpp"
    "include/pairs_lib/impl/ukf.hpp"
    # include/pairs_lib/internal
    "include/pairs_lib/internal/coroutine_callback_helpers.hpp"
    # include/pairs_lib/safety_zone
    "include/pairs_lib/safety_zone/line_operations.h"
    "include/pairs_lib/safety_zone/polygon.h"
    "include/pairs_lib/safety_zone/prism.h"
    "include/pairs_lib/safety_zone/static_edges_visualization.h"
)

target_link_libraries(pairs_lib_pairs_lib
  PUBLIC
    rclcpp::rclcpp
    Eigen3::Eigen
    yaml-cpp::yaml-cpp
    tf2_eigen::tf2_eigen
    Boost::headers
    # ${OpenCV_LIBRARIES}
    # msgs
    ${geometry_msgs_TARGETS}
    ${tf2_ros_TARGETS}
    ${tf2_geometry_msgs_TARGETS}
    ${std_msgs_TARGETS}
    ${pairs_msgs_TARGETS}
    ${nav_msgs_TARGETS}
    ${visualization_msgs_TARGETS}
)

# Dynamic param manager tests

add_executable(dynparam_tests
  examples/dynparam_mgr/dynparam_tests.cpp
)

target_link_libraries(dynparam_tests
  PRIVATE
    rclcpp::rclcpp
    pairs_lib::pairs_lib
)

## | --------------- subscribe handler examples --------------- |

# TODO why is it built from all these different files?
add_executable(subscribe_handler_example
  examples/subscriber_handler/example.cpp
  src/timeout_manager/timeout_manager.cpp
  src/timer_handler/timer_handler.cpp
)

target_link_libraries(subscribe_handler_example
  PRIVATE
    rclcpp::rclcpp
    ${std_msgs_TARGETS}
    pairs_lib::pairs_lib
)

## --------------------------------------------------------------
## |                           Testing                          |
## --------------------------------------------------------------

if(ENABLE_TESTS)

  add_subdirectory(test)

  if(NOT DEFINED ENV{IN_NIX_SHELL})
    message(WARNING "Compiling lint tests")
    find_package(ament_cmake_clang_format REQUIRED)
    ament_clang_format(CONFIG_FILE "${PROJECT_SOURCE_DIR}/.clang-format")
    find_package(ament_cmake_xmllint REQUIRED)
    ament_xmllint()
  endif()

  mrs_verify_interface_header_sets(pairs_lib_pairs_lib)

endif()

## --------------------------------------------------------------
## |                           install                          |
## --------------------------------------------------------------

install(
  TARGETS
    pairs_lib_pairs_lib
  EXPORT export_${PROJECT_NAME}
  ARCHIVE DESTINATION lib
  LIBRARY DESTINATION lib
  RUNTIME DESTINATION bin
  FILE_SET HEADERS DESTINATION "include/${PROJECT_NAME}"
)

ament_export_targets(
  export_${PROJECT_NAME} HAS_LIBRARY_TARGET
)

# Kept for backward compatibility
ament_export_libraries(
  pairs_lib_pairs_lib
)

# Kept for backward compatibility
ament_export_include_directories(
  "include/${PROJECT_NAME}"
)

ament_export_dependencies(
  ${DEPENDENCIES}
)

ament_python_install_package(${PROJECT_NAME})

ament_package()
