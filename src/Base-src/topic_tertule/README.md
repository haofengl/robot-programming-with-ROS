# 这个是一个话题功能包
	* 1、话题发布控制海龟
	* 2、话题订阅收集海龟位置信息
	* 3、自定义消息类型实现个人信息的发布和订阅

### 创建功能包
	* catkin_creat_pkg topic_turtle rospy roscpp std_msgs geometry_msgs turtlesim

### 编译规则
	* add_executable(publisher src/publisher.cpp)
	* target_link_libraries(publisher ${catkin_LIBRARIES})

	* add_executable(pose_subscriber src/pose_subscriber.cpp)
	* target_link_libraries(pose_subscriber ${catkin_LIBRARIES})

	* add_executable(person_publisher src/person_publisher.cpp)
	* target_link_libraries(person_publisher ${catkin_LIBRARIES})
	* add_dependencies(person_publisher ${PROJECT_NAME}_generate_messages_cpp)

	* add_executable(person_subscriber src/person_subscriber.cpp)
	* target_link_libraries(person_subscriber ${catkin_LIBRARIES})
	* add_dependencies(person_subscriber ${PROJECT_NAME}_generate_messages_cpp)

### 编译并运行
	* 对于Python文件可直接运行，但要给文件可执行权限
 
#### 1、运行海龟publisher
	* cd ~/catkin_ws
	* catkin_make
	* source devel/setup.bash
	* roscore
	* rosrun turtlesim turtlesin_node
	* rosrun topic_turtle publisher
#### 2、运行海龟subscriber
	* cd ~/catkin_ws
	* catkin_make
	* source devel/setup.bash
	* roscore
	* rosrun turtlesim turtlesin_node
	* rosrun topic_turtle pose_subscriber
#### 3、运行自定义消息类型的话题发布和订阅
	* roscore
	* rosrun topic_tertule person_subscriber
	* rosrun topic_tertule person_publisher