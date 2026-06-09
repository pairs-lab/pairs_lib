cmake_minimum_required(VERSION 3.1.2)
project(pairs_lib)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# please, NEVER commit those alternative flags with specific overrides of optimization
#  add the address sanitizer compiler flags to debug build type
# set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -fno-omit-frame-pointer -fsanitize=address,undefined -fno-omit-frame-pointer") # because normal release is just -O2
#  add the address sanitizer linker flags to debug build type
# set(CMAKE_LD_FLAGS_DEBUG  "${CMAKE_LD_FLAGS_DEBUG} -fno-omit-frame-pointer -fsanitize=address,undefined") # because normal release is just -O2
# set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O3") # because normal release is just -O2
# please, really do not commit your temporary custom flags :-)

add_definitions(-Wall)
add_definitions(-Wextra)
add_definitions(-Wpedantic)

# if(CATKIN_ENABLE_TESTING AND PAIRS_ENABLE_TESTING)
#   add_definitions(-fsanitize=address -g3 -fno-omit-frame-pointer)
#   add_link_options(-fsanitize=address)
# endif()

if(COVERAGE)
  message(WARNING "building with --coverage, the performance might be limited")
  set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} --coverage")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --coverage")
endif()

# remove warning info from PCL
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

find_package(catkin REQUIRED COMPONENTS
  ${CATKIN_DEPENDENCIES}
  )

find_package(yaml-cpp REQUIRED)

# include Eigen3
find_package(Eigen3 REQUIRED)
set(Eigen_INCLUDE_DIRS ${EIGEN3_INCLUDE_DIRS})
set(Eigen_LIBRARIES ${EIGEN3_LIBRARIES})

# include OpenCV
find_package(OpenCV REQUIRED HINTS /usr/local/lib)

###################################
## catkin specific configuration ##
###################################

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

## --------------------------------------------------------------
## |                            Build                           |
## --------------------------------------------------------------

include_directories(
  include
  ${catkin_INCLUDE_DIRS}
  ${Eigen_INCLUDE_DIRS}
  ${OpenCV_INCLUDE_DIRS}
  ${pcl_ros_INCLUDE_DIRS}
  ${YAML_CPP_INCLUDE_DIRS}
  )

add_library(PairsLib_TimeoutManager src/timeout_manager/timeout_manager.cpp)
target_link_libraries(PairsLib_TimeoutManager
  ${catkin_LIBRARIES}
  )

add_library(PairsLib_DynamicPublisher src/dynamic_publisher/dynamic_publisher.cpp)
target_link_libraries(PairsLib_DynamicPublisher
  ${catkin_LIBRARIES}
  )

add_executable(dynamic_publisher_example src/dynamic_publisher/example.cpp)
target_link_libraries(dynamic_publisher_example
  PairsLib_DynamicPublisher
  ${catkin_LIBRARIES}
  ${Eigen_LIBRARIES}
  )

add_executable(repredictor_example src/repredictor/example.cpp)
target_link_libraries(repredictor_example
  ${catkin_LIBRARIES}
  ${Eigen_LIBRARIES}
  )

add_executable(service_client_handler_example src/service_client_handler/example.cpp)
target_link_libraries(service_client_handler_example
  ${catkin_LIBRARIES}
  ${Eigen_LIBRARIES}
  )

add_library(PairsLib_OdomLKF src/lkf/LKF_PAIRS_odom.cpp)
target_link_libraries(PairsLib_OdomLKF
  ${catkin_LIBRARIES}
  ${Eigen_LIBRARIES}
  )

add_executable(lkf_example src/lkf/example.cpp)
target_link_libraries(lkf_example
  ${catkin_LIBRARIES}
  ${Eigen_LIBRARIES}
  )

add_executable(dkf_example src/dkf/example.cpp)
target_link_libraries(dkf_example
  PairsLib_Geometry
  ${catkin_LIBRARIES}
  ${Eigen_LIBRARIES}
  )

# # Slows the compilation of the library waaaay too much - just generate the conversions on-demand
# # instead of pre-generating all combinations.
# add_library(PairsLib_VectorConverter src/vector_converter/vector_converter.cpp)
# target_link_libraries(PairsLib_VectorConverter
#   ${catkin_LIBRARIES}
#   ${Eigen_LIBRARIES}
#   ${pcl_ros_LIBRARIES}
#   )
# target_include_directories(PairsLib_VectorConverter PRIVATE
#   ${pcl_ros_INCLUDE_DIRS}
#   )

add_executable(vector_converter_example src/vector_converter/example.cpp)

target_link_libraries(vector_converter_example
  # PairsLib_VectorConverter
  ${catkin_LIBRARIES}
  ${Eigen_LIBRARIES}
  ${pcl_ros_LIBRARIES}
  )
target_include_directories(vector_converter_example PRIVATE
  ${pcl_ros_INCLUDE_DIRS}
  )

add_executable(ukf_example src/ukf/example.cpp)
target_link_libraries(ukf_example
  ${catkin_LIBRARIES}
  ${Eigen_LIBRARIES}
  )

add_executable(nckf_tests src/nckf/nckf_tests.cpp)

target_link_libraries(nckf_tests
  ${catkin_LIBRARIES}
  ${Eigen_LIBRARIES}
  )

add_library(PairsLib_SafetyZone src/safety_zone/safety_zone.cpp
  src/safety_zone/line_operations.cpp
  src/safety_zone/polygon/polygon.cpp
  )

target_link_libraries(PairsLib_SafetyZone
  ${catkin_LIBRARIES}
  ${Eigen_LIBRARIES}
  )

add_library(PairsLib_Profiler src/profiler/profiler.cpp)
target_link_libraries(PairsLib_Profiler
  ${catkin_LIBRARIES}
  ${Eigen_LIBRARIES}
  )

add_library(PairsLib_ScopeTimer src/scope_timer/scope_timer.cpp)
target_link_libraries(PairsLib_ScopeTimer
  ${catkin_LIBRARIES}
  ${Eigen_LIBRARIES}
  )

add_library(PairsLib_MedianFilter src/median_filter/median_filter.cpp)
target_link_libraries(PairsLib_MedianFilter
  ${catkin_LIBRARIES}
  ${Eigen_LIBRARIES}
  )

add_library(PairsLib_IirFilter src/iir_filter/iir_filter.cpp)
target_link_libraries(PairsLib_IirFilter
  ${catkin_LIBRARIES}
  ${Eigen_LIBRARIES}
  )

add_library(PairsLib_NotchFilter src/notch_filter/notch_filter.cpp)
target_link_libraries(PairsLib_NotchFilter
  PairsLib_IirFilter
  ${catkin_LIBRARIES}
  ${Eigen_LIBRARIES}
  )

add_executable(mutex_tests src/mutex/mutex_tests.cpp)
target_link_libraries(mutex_tests
  ${catkin_LIBRARIES}
  ${Eigen_LIBRARIES}
  )

add_library(PairsLib_AttitudeConverter src/attitude_converter/attitude_converter.cpp)
target_link_libraries(PairsLib_AttitudeConverter
  PairsLib_Geometry
  ${catkin_LIBRARIES}
  ${Eigen_LIBRARIES}
  )

add_library(PairsLib_Transformer src/transformer/transformer.cpp)
target_link_libraries(PairsLib_Transformer
  PairsLib_Geometry
  ${catkin_LIBRARIES}
  ${Eigen_LIBRARIES}
  )
target_include_directories(PairsLib_Transformer PRIVATE
  ${pcl_ros_INCLUDE_DIRS}
  )

add_executable(transformer_example src/transformer/example.cpp)
target_link_libraries(transformer_example
  PairsLib_Transformer
  ${catkin_LIBRARIES}
  ${Eigen_LIBRARIES}
  )

add_library(PairsLib_Utils src/utils/utils.cpp)
target_link_libraries(PairsLib_Utils
  ${catkin_LIBRARIES}
  ${Eigen_LIBRARIES}
  )

add_library(PairsLib_ParamProvider src/param_loader/param_provider.cpp)
target_link_libraries(PairsLib_ParamProvider
  ${catkin_LIBRARIES}
  ${Eigen_LIBRARIES}
  ${YAML_CPP_LIBRARIES}
  )

add_library(PairsLib_ParamLoader src/param_loader/param_loader.cpp)
target_link_libraries(PairsLib_ParamLoader
  ${catkin_LIBRARIES}
  ${Eigen_LIBRARIES}
  PairsLib_ParamProvider
  )

add_library(PairsLib_TransformBroadcaster src/transform_broadcaster/transform_broadcaster.cpp)
target_link_libraries(PairsLib_TransformBroadcaster
  ${catkin_LIBRARIES}
  ${Eigen_LIBRARIES}
  )

add_executable(param_loader_example src/param_loader/example.cpp)
target_link_libraries(param_loader_example
  ${catkin_LIBRARIES}
  ${Eigen_LIBRARIES}
  PairsLib_ParamLoader
  )

add_executable(param_provider_example src/param_loader/param_provider_example.cpp)
target_link_libraries(param_provider_example
  ${catkin_LIBRARIES}
  ${Eigen_LIBRARIES}
  PairsLib_ParamProvider
  )

add_executable(subscribe_handler_example src/subscribe_handler/example.cpp)
target_link_libraries(subscribe_handler_example
  PairsLib_TimeoutManager
  ${catkin_LIBRARIES}
  ${Eigen_LIBRARIES}
  )

add_executable(subscribe_handler_simple_example src/subscribe_handler/simple_example.cpp)
target_link_libraries(subscribe_handler_simple_example
  PairsLib_TimeoutManager
  ${catkin_LIBRARIES}
  ${Eigen_LIBRARIES}
  )

add_executable(rheiv_example src/rheiv/example.cpp)
target_link_libraries(rheiv_example
  ${catkin_LIBRARIES}
  ${Eigen_LIBRARIES}
  )

add_library(PairsLib_BatchVisualizer src/batch_visualizer/batch_visualizer.cpp src/batch_visualizer/visual_object.cpp)
target_link_libraries(PairsLib_BatchVisualizer
  PairsLib_Geometry
  ${catkin_LIBRARIES}
  ${Eigen_LIBRARIES}
  ${GAZEBO_INCLUDE_DIRS}
  )

add_library(PairsLib_ImagePublisher src/image_publisher/image_publisher.cpp)
target_link_libraries(PairsLib_ImagePublisher
  ${catkin_LIBRARIES}
  ${Eigen_LIBRARIES}
  ${OpenCV_LIBRARIES}
  ${GAZEBO_INCLUDE_DIRS}
  )

add_executable(batch_visualizer_demo src/batch_visualizer/batch_visualizer_demo.cpp)
target_link_libraries(batch_visualizer_demo
  PairsLib_Geometry
  PairsLib_BatchVisualizer
  ${catkin_LIBRARIES}
  ${Eigen_LIBRARIES}
  ${GAZEBO_INCLUDE_DIRS}
  )

add_library(PairsLib_Math src/math/math.cpp)
target_link_libraries(PairsLib_Math
  ${catkin_LIBRARIES}
  )

add_library(PairsLib_Geometry src/geometry/misc.cpp src/geometry/cyclic.cpp src/geometry/shapes.cpp src/geometry/conversions.cpp)
target_link_libraries(PairsLib_Geometry
  ${catkin_LIBRARIES}
  ${Eigen_LIBRARIES}
  ${OpenCV_LIBRARIES}
  ${GAZEBO_INCLUDE_DIRS}
  )

add_library(PairsLib_Timer src/timer/timer.cpp)
target_link_libraries(PairsLib_Timer
  ${catkin_LIBRARIES}
  )

add_executable(geometry_tests src/geometry/tests.cpp)
target_link_libraries(geometry_tests
  PairsLib_Geometry
  ${catkin_LIBRARIES}
  ${Eigen_LIBRARIES}
  )

add_executable(cyclic_example src/geometry/cyclic_example.cpp)
target_link_libraries(cyclic_example
  PairsLib_Geometry
  ${catkin_LIBRARIES}
  ${Eigen_LIBRARIES}
  )

## --------------------------------------------------------------
## |                           Testing                          |
## --------------------------------------------------------------

if(CATKIN_ENABLE_TESTING AND PAIRS_ENABLE_TESTING)

  message(WARNING "Testing enabled.")

  add_subdirectory(test)

endif()

## --------------------------------------------------------------
## |                           Install                          |
## --------------------------------------------------------------

install(TARGETS ${LIBRARIES}
  ARCHIVE DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
  LIBRARY DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
  RUNTIME DESTINATION ${CATKIN_GLOBAL_BIN_DESTINATION}
  )

install(DIRECTORY include/pairs_lib/
  DESTINATION ${CATKIN_PACKAGE_INCLUDE_DESTINATION}
  )

install(DIRECTORY
  DESTINATION ${CATKIN_PACKAGE_SHARE_DESTINATION}
  FILES_MATCHING PATTERN "*.xml"
  )
