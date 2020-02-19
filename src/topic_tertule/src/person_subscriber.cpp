/**
 * 该例程将订阅/person_info的话题,消息类型为topic_tertule::person
 */

 #include<ros/ros.h>
 #include<topic_tertule/person.h>

 // 接收到订阅的消息后，会进入消息回调函数
 void posecallback(const topic_tertule::person::ConstPtr& msg)
 {
     // 接收到的消息打印出来
     ROS_INFO("Subscriber person Info: name:%s age:%d sex:%d",
                 msg->name.c_str(), msg->age, msg->sex);
 }

 int main(int argc, char **argv)
 {
     // 初始化ＲＯＳ节点
     ros::init(argc, argv, "person_subscriber");

     // 创建节点句柄
     ros::NodeHandle n;
     
     // 创建一个subscriber，订阅话题/person_info,注册回调函数posecallback
     ros::Subscriber person_sub = n.subscribe("/person_info", 10, posecallback);

     // 循环等待回调函数
     ros::spin();
          
     return 0;
 }