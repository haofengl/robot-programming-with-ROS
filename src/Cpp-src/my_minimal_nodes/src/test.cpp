// 话题的抽象概念
// 通过实例化发布器对象,调用成员函数advertise,指定消息类型 话题名 来初始化话题  
// 通过实例化订阅器对象,订阅指定话题也可以初始化话题
// 订阅器接收消息 并在callback中进行消息处理  只有在新消息进来时回调函数才运行
// NodeHandle来建立节点间的通信网络,用于初始化通信对象

/*
 * 在话题抽象中 发布器初始化一个话题 需要用advertise 并确定消息类型
 * spin() 使主程序为回调函数提供响应时间 且让主程序挂起的同时保持回调函数的工作
 * spinOnce()让主程序和回调函数都能运行
 */ 


/*
 *  这是仿真器实例 该节点通过 订阅force_cmd话题 接收控制器的发布的力 
 *  再转化为速度   将速度    发布到velocoty_cmd话题 上
 */

#include <ros/ros.h>
#include <std_msgs/Float64.h>

std_msgs::Float64 g_velocity;                       // 声明为全局变量 使发布器和订阅器都可以使用
std_msgs::Float64 g_force;

void myCallback(const std_msgs::Float64 & message_holder)
{
    ROS_INFO("recived force value is : %f", message_holder.data);
    g_force.data = message_holder.data;
}

int main(int argc, char ** argv)
{
    ros::init(argc, argv, "minimal_simulator");      // 节点名称
    ros::NodeHandle nh;

    ros::Subscriber my_subscriber_ogject = nh.subscribe("force_cmd", 1, myCallback);
    ros::Publisher  my_publisher_object  = nh.advertise<std_msgs::Float64>("velocity", 1);

    double mass = 1.0;
    double dt   = 0.01;
    double sample_rate = 0.01 / dt;

    ros::Rate naptime(sample_rate);                   // 1HZ

    g_velocity.data = 0.0;
    g_force.data    = 0.0;

    while(ros::ok())
    {
        g_velocity.data = g_velocity.data + (g_force.data/mass)*dt;
        my_publisher_object.publish(g_velocity);
        ROS_INFO("velocity = %f", g_velocity.data);

        ros::spinOnce();
        naptime.sleep();
    }

    return 0;
}