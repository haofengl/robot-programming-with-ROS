/*
 *  服务的抽象概念  服务一般都需要自定义消息类型
 *  服务的目的是快速响应,当客户端发送请求时,客户端将被暂停直至应答返回   
 *  服务通信中 服务器需要初始化来确定消息类型 并用advertiseServic来初始化
 *
 *  服务做的也只是个数据传输而已 和话题一样
 */

#include <ros/ros.h>
#include <iostream>
#include <string>
#include "example_ros_service/ExampleServiceMsg.h"  //消息编译之后存放在catkin_ws/devel/include中,不是存放在本功能包include中

using namespace std;

bool callback(example_ros_service::ExampleServiceMsgRequest & request,
                example_ros_service::ExampleServiceMsgResponse & response)
{
    ROS_INFO("Callback activated");

    string in_name(request.name);                  // 将request的输入值赋给in_name
    cout << "in_name: " << in_name << endl;

    response.on_the_list = false;

    if(in_name.compare("Bob") == 0)
    {
        ROS_INFO("Asked about Bob");
        response.age         = 18;
        response.good_guy    = false;
        response.on_the_list = true;
        response.nickname    = "Bob the Terribe";
    }
    if(in_name.compare("Ted") == 0)
    {
        ROS_INFO("Asked about Ted");
        response.age         = 20;
        response.good_guy    = true;
        response.on_the_list = true;
        response.nickname    = "Ted the Berribe";
    }

    return true;                            // 将响应消息传回到客户端, 隐藏了该机制 不用调用publish(response)
}

int main(int argc, char ** argv)
{
    ros::init(argc, argv, "example_ros_Service");
    ros::NodeHandle n;

    ros::ServiceServer service = n.advertiseService("lookup_by_name", callback);     

    ROS_INFO("Ready to look up names");

    ros::spin();

    return 0;
}