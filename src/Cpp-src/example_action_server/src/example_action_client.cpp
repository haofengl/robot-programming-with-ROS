#include <ros/ros.h>
#include <actionlib/client/simple_action_client.h>

#include "example_action_server/demoAction.h"


void doneCb(const actionlib::SimpleClientGoalState& state, 
            const example_action_server::demoResultConstPtr& result)
{
    ROS_INFO("DoneCb: server responded with state [%s]", state.toString().c_str());
    int dff = result->output - result->goal_stamp;
    ROS_INFO("goal result output = %d, goal_stamp = %d, diff=%d", result->output, result->goal_stamp, dff);
}


int main(int argc, char ** argv)
{
    ros::init(argc, argv, "demo_action_client_node");

    int g_count = 0;
    example_action_server::demoGoal goal;                                 // 该对象用于将目标传达给动作服务器


    // 创建对象action_client动作客户端 连接example_action动作服务器
    actionlib::SimpleActionClient<example_action_server::demoAction> action_client("example_action", true);


    // 与服务器连接
    ROS_INFO("waiting for server: ");
    bool server_exits = action_client.waitForServer(ros::Duration(2.0));   // 等待2秒连接到服务器 
    if(!server_exits)
    {
        ROS_WARN("could not connect to server; halting");
        return 0;
    }
    ROS_INFO("connect to action server");


    ros::Rate waittime(1.0);
    while(true)
    {
        g_count ++;
        goal.input = g_count;

        // 请求服务器按照目标消息中所指定的执行其服务 指明回调函数
        action_client.sendGoal(goal, &doneCb);

        bool finished_before_timeout = action_client.waitForResult(ros::Duration(1.0));  // 等待服务器发来的结果 触发doneCb函数
        if(!finished_before_timeout)
        {
            ROS_WARN("giving up waiting on result for goal number %d", g_count);
            return 0;
        }
        else{}

        waittime.sleep();

    }
    return 0;

}