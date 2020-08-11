#include <ros/ros.h>
#include "example_ros_service/ExampleServiceMsg.h"
#include <iostream>
#include <string>

using namespace std;

int main(int argc, char ** argv)
{
    ros::init(argc, argv, "example_ros_client");
    ros::NodeHandle n;

    ros::ServiceClient client = n.serviceClient<example_ros_service::ExampleServiceMsg>("lookup_by_name");
    
    example_ros_service::ExampleServiceMsg srv;
    bool found_on_list = false;
    string in_name;

    while(ros::ok())
    {
        cout << endl;
        cout << "Enter a name (x to quiet):";
        cin  >> in_name;
        
        if(in_name.compare("x") == 0)
            return 0;

        srv.request.name = in_name;

        if(client.call(srv))        // call会返回一个bool值 来首先判断是否请求成功  之后再做请求成功后对传回来数据的处理
        {
            if(srv.response.on_the_list)
            {
                cout << srv.request.name << " is konw as " << srv.response.nickname << endl;
                cout << "He is " << srv.response.age << " year old" << endl;

                if(srv.response.good_guy)
                    cout << "He is a good_guy" << endl;
                else
                    cout << "He not is a good_guy" << endl;
            }
            else
            {
                cout << srv.request.name << " is not in my database" << endl;
            }
           
        }
        else
        {
            ROS_INFO("Failed to call service lookup_by_name");
            return 1;
        }
    }

    return 0;
}