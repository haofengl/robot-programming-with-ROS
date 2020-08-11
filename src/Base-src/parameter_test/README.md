# 这算是一个参数服务器测试功能包

### 创建功能包
* cd ~/catkin_ws/src
* catkin_create_pkg parameter rospy roscpp std_srvs

## 编译
* add_executable(parameter_config src/parameter_config.cpp)
* target_link_libraries(parameter_config ${catkin_LIBRARIES})

## 运行
* cd ~/catkin_ws
* catkin_make
* source devel/setup.bash
* roscore
* rosrun turtlesim turtlesim_node
* rosrun parameter_test parameter_config