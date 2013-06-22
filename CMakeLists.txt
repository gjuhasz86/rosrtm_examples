cmake_minimum_required(VERSION 2.8.3)
project(rosrtm_examples)

find_package(catkin REQUIRED COMPONENTS ros_rtm_gateway roscpp std_msgs)

catkin_package(
  CATKIN_DEPENDS ros_rtm_gateway message_runtime roscpp std_msgs
)

include_directories(
  ${catkin_INCLUDE_DIRS}
  /usr/include/openrtm-1.1
  /usr/include/openrtm-1.1/rtm/idl
  /usr/include/coil-1.1
)

add_executable(ExampleGwComp src/ExampleGwComp.cpp)
target_link_libraries(ExampleGwComp ${catkin_LIBRARIES}
  RTC coil uuid dl pthread omniORB4 omnithread omniDynamic4)
