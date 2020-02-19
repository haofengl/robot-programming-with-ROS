/**
 * 该例程将执行/show_person服务，服务数据类型service::person
 */

 # include<ros/ros.h>
 # include<service/person.h>

// service回调函数，输入参数req,输出参数ers
bool personCallback(service::person::Request &req,
                        service::person::Response &res)
{
    // 显示请求数据
    ROS_INFO("Person:name:%s age:%d sex:%d", req.name.c_str(), req.age, req.sex);

    // 设置反馈数据
    res.result = "All Reight";

    return true;
}

int main(int argc, char **argv)
{
    // ROS节点初始化
    ros::init(argc, argv, "person_server");

    // 创建节点句柄
    ros::NodeHandle n;

    // 创建一个名为/show_person的server，注册回调函数perCallback
    ros::ServiceServer person_service = n.advertiseService("/show_person", personCallback);

    // 循环等待回调函数
    ROS_INFO("Ready to show person informtion.");
    ros::spin();

    return 0;
}