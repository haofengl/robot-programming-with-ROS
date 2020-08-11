#include <ros/ros.h>
#include <actionlib/client/simple_action_client.h>

#include "example_action_server/demoAction.h"

using namespace std;

bool g_goal_active   = false;
int  g_result_output = -1;
int  g_fdbk          = -1;

// 当服务器端调用结束返回result数据时才调用该回调函数 一般是最后响应
void doneCb(const actionlib::SimpleClientGoalState& state, 
            const example_action_server::demoResultConstPtr& result)
{
    ROS_INFO("DoneCb: server responded with state [%s]", state.toString().c_str());  // 查看连接状态
    ROS_INFO("get result output = %d", result->output);
    g_result_output = result->output;
    g_goal_active   = false;
}

// 从动作服务器接受反馈信息 服务器发送状态反馈信息 实时调用该函数接收
void feedbackCb(const example_action_server::demoFeedbackConstPtr& fdbk_msg)
{
    ROS_INFO("feedback status = %d", fdbk_msg->fdbk);
    g_fdbk = fdbk_msg->fdbk;               // 将结果复制到全局变量 从而让main函数可对其进行访问
}

// 一旦服务器有数据发送过来 则将首先调用该回调函数 因为其不接受参数 执行速度较快
void active()
{
    ROS_INFO("Goal just went active");
    g_goal_active = true;
}

int main(int argc, char ** argv)
{
    ros::init(argc, argv, "timer_client_node2");
    ros::NodeHandle n;
    ros::Rate main_time(1.0);

    example_action_server::demoGoal goal;

    // 创建动作客户端 并指定要连接的服务器
    actionlib::SimpleActionClient<example_action_server::demoAction> action_client1("timer_action", true);


    ROS_INFO("attemping to connect to server: ");
    bool server_exists = action_client1.waitForServer(ros::Duration(1.0));

    // 试图每秒一次连接到服务器上 直到连接成功
    while(!server_exists)
    {
        ROS_WARN("could not connect to server; retrying...");
        server_exists = action_client1.waitForServer(ros::Duration(1.0));
        //main_time.sleep();
    }
    ROS_INFO("connect to action server");


    int countdown_goal = 1;

    while(countdown_goal >= 0)
    {
        cout << "enter a desired timer value, in seconed(0 to abort, <0 to quiet): ";
        cin  >> countdown_goal;
        if(countdown_goal == 0)
        {
            ROS_INFO("cannelling goal");
            action_client1.cancelGoal();
        }
        if(countdown_goal < 0)
        {
            ROS_INFO("this client is quietting");
            return 0;
        }
        ROS_INFO("sending timer goal = %d seconeds to timer action server", countdown_goal);
        goal.input = countdown_goal;
        action_client1.sendGoal(goal, &doneCb, &active, &feedbackCb);
    }
    return 0;



}