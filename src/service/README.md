# 这是一个服务功能包
     * client请求一个/spawn

## 生成功能包
    * cd ~/catkin_ws/src
    * catkin_create_pkg service roscpp rospy std_msgs geometry_msgs turtlesim

## 编译规则
    * add_executable(turtle_spawn src/turtle_spawn.cpp)
    * target_link_libraries(turtle_spawn ${catkin_LIBRARIES})

    * add_executable(turtle_server src/turtle_server.cpp)
    * target_link_libraries(turtle_server ${catkin_LIBRARIES})

    * add_executable(person_server src/person_server.cpp)
    * target_link_libraries(person_server ${catkin_LIBRARIES})
    * add_dependencies(person_server ${PROJECT_NAME}_gencpp)

    * add_executable(person_client src/person_client.cpp)
    * target_link_libraries(person_client ${catkin_LIBRARIES})
    * add_dependencies(person_client ${PROJECT_NAME}_gencpp)

## 运行
    * roscore
    * rosrun turtlesim turtlesim_node
    * rosrun service turtle_spawn

    * roscore
    * rosrun turtlesim turtlesim_node
    * rosrun service turtle_server
    * rosservice call /turtle_command "{}"

    * roscore
    * rosrun service person_server
    * rosrun service person_client