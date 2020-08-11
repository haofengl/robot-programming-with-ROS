#include "example_ros_class.h"

// 构造函数可以封装设置发布器 订阅器和服务的细节,初始化类变量(类变量包括发布者,订阅者等)
// 其中初始化订阅者时 就要考虑对象,this
ExampleRosClass::ExampleRosClass(ros::NodeHandle * nodehandle):nh_(*nodehandle)
{
    ROS_INFO("in class constructor of ExampleRosClass");
    initializeSubscribers();
    initializePublishers();
    initializeServices();

    val_to_remember_ = 0.0;
}

// 成员函数的实现
void ExampleRosClass::initializeSubscribers()
{
    ROS_INFO("Initializing Subscribers");
    minimal_subscriber_ = nh_.subscribe("example_class_input_topic", 1, &ExampleRosClass::subscriberCallback, this);
}

void ExampleRosClass::initializeServices()
{
    ROS_INFO("Initializing Services");
    minimal_service_ = nh_.advertiseService("example_minimal_service", &ExampleRosClass::serviceCallback, this);
}

void ExampleRosClass::initializePublishers()
{
    ROS_INFO("Initializing Publishers");
    minimal_publisher_ = nh_.advertise<std_msgs::Float32>("example_class_output_topic", 1, true);
}

//回调函数的实现
void ExampleRosClass::subscriberCallback(const std_msgs::Float32 & message_holder)
{
    val_from_subscriber_ = message_holder.data;
    ROS_INFO("mycallback activated: received value %f", val_from_subscriber_);
    std_msgs::Float32 output_msg;

    val_to_remember_ += val_from_subscriber_;
    output_msg.data   = val_to_remember_;
    minimal_publisher_.publish(output_msg);
}

bool ExampleRosClass::serviceCallback(std_srvs::TriggerRequest & request, std_srvs::TriggerResponse & response)
{
    ROS_INFO("service callback activated");
    response.success = true;
    response.message = "here is a response string";
    return true;
}

// main函数必须初始化节点句柄 并传给构造函数 构造函数负责初始化变量

int main(int argc, char ** argv)
{
    ros::init(argc, argv, "exampleRosClass");     // 节点名称
    ros::NodeHandle nh;

    ROS_INFO("main : instantiating an object of type ExampleRosClass");

    ExampleRosClass exampleRosClass(&nh);         // 创建一个对象 并初始化

    ROS_INFO("main: going into spin; let the callback do all the work");
    ros::spin();
    
    return 0;

}