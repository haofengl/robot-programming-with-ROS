/**
 * 该例程将发布/person_info话题，消息类型topic_tertule
 */

 #include <ros/ros.h>
 #include <topic_tertule/person.h>


 int main(int argc, char **argv)
 {
     // ROS节点初始化,前两个参数不变，最后为发布者名称
     ros::init(argc, argv, "person_publisher");

     // 创建节点句柄
     ros::NodeHandle n;
     
     // 创建一个publisher，发布/person_info的topic，消息类型为geometry::Twist,队列长度为10
     ros::Publisher person_info_pub = n.advertise<topic_tertule::person>("/person_info", 10);

     // 设置循环的频率
     ros::Rate loop_rate(1);

     int count = 0;
     while(ros::ok())
     {
         // 初始化topic/tertle类型的消息
         topic_tertule::person person_msg;
         person_msg.name = "WuKong";
         person_msg.age  = 1;
         person_msg.sex  = topic_tertule::person::male;

         // 发布消息
         person_info_pub.publish(person_msg);
         
         //ROS输出日志
         ROS_INFO("publish person Info: name:%s age:%d sex:%d",
                    person_msg.name.c_str(), person_msg.age, person_msg.sex);
         
         // 按照循环频率延时
         loop_rate.sleep();
     }

     return 0;

 }