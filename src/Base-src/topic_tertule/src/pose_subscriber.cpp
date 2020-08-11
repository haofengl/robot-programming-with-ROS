/**
 * 该例程将订阅/turtle1/pose的话题,消息类型为turtlesim::Pose
 */

 #include<ros/ros.h>
 #include<turtlesim/Pose.h>

 // 接收到订阅的消息后，会进入消息回调函数
 void posecallback(const turtlesim::Pose::ConstPtr& msg)
 {
     // 接收到的消息打印出来
     ROS_INFO("Turtle pose: x:%0.6f, y:%0.6f", msg->x, msg->y);
 }

 int main(int argc, char **argv)
 {
     // 初始化ＲＯＳ节点
     ros::init(argc, argv, "pose_subscriber");

     // 创建节点句柄
     ros::NodeHandle n;
     
     // 创建一个subscriber，订阅话题/turtle1/pose,注册回调函数posecallback
     ros::Subscriber pose_sub = n.subscribe("/turtle1/pose", 10, posecallback);

     // 循环等待回调函数
     ros::spin();
          
     return 0;
 }