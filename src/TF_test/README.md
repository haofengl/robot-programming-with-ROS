# 这是一个坐标系广播和监听机制实现的功能包

## 创建功能包
* cd ~/catkin_ws/src
* catkin_create_pkg TF_test roscpp rospy tf turtlesim

## 编译
* add_executable(turtle_tf_broadcaster src/turtle_tf_broadcaster.cpp)
* target_link_libraries(turtle_tf_broadcaster ${catkin_LIBRARIES})

* add_executable(turtle_tf_listener src/turtle_tf_listener.cpp)
* target_link_libraries(turtle_tf_listener  ${catkin_LIBRARIES})

## 运行
* roscore
* rosrun turtlesim turtlesim_node
* rosrun TF_test turtle_tf_broadcaster __name=:turtle1_tf_broadcaster /turtle1
* rosrun TF_test turtle_tf_broadcaster __name=:turtle2_tf_broadcaster /turtle2
* rosrun TF_test turtle_tf_listener
* rosrun turtlesim turtle_teleop_key