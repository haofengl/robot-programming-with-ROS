# 该文件夹存放消息内容
    * 自定义的消息编译后在devel/include文件夹下

### 在package.xml中添加功能包依赖
    * <build_depend>message_generation</build_depend>
    * <exec_depend>message_runtime</exec_depend>

### 在CMakeList.txt添加编译选项
    * find_package(.......message_generation)
    
    * add_message_files(FILES person.msg)
    * generate_messages(DEPENDENCIES std_msgs)

    * catkin_package(......message_runtime)