# 这是自定义消息类型的功能包

## 若要将.msg编译成.h头文件  
    * 需要在xml中取消掉 message_generation message_runtime 两项
    * 需要在cmake文件中 添加四项内容
      ```find_package(catkin REQUIRED COMPONENTS
            roscpp
            std_msgs
            message_generation
            )```  
      ```add_message_files(
            FILES
            ExampleMessage.msg
            )```
      ```generate_messages(
            DEPENDENCIES
            std_msgs
        )```
      ```catkin_package(

            CATKIN_DEPENDS roscpp std_msgs message_runtime

            )```
        
## 若要调用自定义的消息包     
    * 需要在xml中添加消息包的包名  已添加依赖
