/*
 * 该节点为最小控制器实例  订阅velocity vel_cmd话题  发布到force_cmd话题
 */

#include <ros/ros.h>
#include <std_msgs/Float64.h>

std_msgs::Float64 g_velocity;
std_msgs::Float64 g_vel_cmd;
std_msgs::Float64 g_force;

void myCallbackVelocity(const std_msgs::Float64 & message_holder)
{
    ROS_INFO("recived velocity value is : %f", message_holder.data);
    g_velocity.data = message_holder.data;
}

void myCallbackVelcmd(const std_msgs::Float64 & message_holder)
{
    ROS_INFO("recived velocity command value is : %f", message_holder.data);
    g_vel_cmd.data = message_holder.data;
}

int main(int argc, char ** argv)
{
    ros::init(argc, argv, "minimal_controller");
    ros::NodeHandle nh;

    ros::Subscriber my_subscriber_object1 = nh.subscribe("velocity", 1, myCallbackVelocity);
    ros::Subscriber my_subscriber_object2 = nh.subscribe("vel_cmd", 1, myCallbackVelcmd);
    ros::Publisher  my_publisher_object   = nh.advertise<std_msgs::Float64>("force_cmd", 1);

    double Kv = 1.0;
    double dt_controller = 0.1;
    double sample_rate   = 1.0/dt_controller;

    ros::Rate naptime(sample_rate);               // 控制频率 声明Rate类的一个对象 并实例化  

    g_velocity.data = 0.0;
    g_force.data    = 0.0;
    g_vel_cmd.data  = 0.0;
    double vel_err  = 0.0;

    while(ros::ok())
    {
        vel_err = g_vel_cmd.data - g_velocity.data;
        g_force.data = Kv * vel_err;

        my_publisher_object.publish(g_force);

        ROS_INFO("force command = %f", g_force.data);

        ros::spinOnce();
        naptime.sleep();                            // 调用成员函数达到
    }

    return 0;
}
