#include <ros/ros.h>
#include <actionlib/server/simple_action_server.h>
#include "example_action_server/demoAction.h"

int  g_count = 0;
bool g_count_failure = false;

class ExampleActionServer
{
    private:
        ros::NodeHandle nh_;
        actionlib::SimpleActionServer<example_action_server::demoAction> as_;  // 声明SimpleActionServer类的对象 用于创建动作服务器

        example_action_server::demoGoal     goal_;
        example_action_server::demoResult   result_;
        example_action_server::demoFeedback feedback_;

    public:
        ExampleActionServer();
       ~ExampleActionServer(void){}
        
        // 回调函数
        void excuteCB(const actionlib::SimpleActionServer<example_action_server::demoAction>::GoalConstPtr & goal);
};


// 默认构造函数 创建动作服务器并启动, 故需要在类里面定义节点句柄 服务器对象
// boost::bind初始化对象as_, 创建新的动作服务器example_action, 并将回调函数和动作服务器相关联
ExampleActionServer::ExampleActionServer(): 
    as_(nh_, "example_action", boost::bind(&ExampleActionServer::excuteCB, this, _1), false)
    {                                       // excuteCB为回调函数 有一个参数, false告诉构造函数目前不启动新的动作服务器
        ROS_INFO("In constructor of exampleActionServer...");
        as_.start();                        // 启动动作服务器
    }


// 回调函数  客户端发送一次请求 回调函数执行一次
void ExampleActionServer::excuteCB(const actionlib::SimpleActionServer<example_action_server::demoAction>::GoalConstPtr& goal)
{
    g_count ++;                        // 服务目标的次数
    result_.output     = g_count;      // 设置传给客户端的值
    result_.goal_stamp = goal->input;  // 设置传给客户端的值

    // 如果服务次数和传来的目标值不一样 则证明传输出现错误
    if(g_count != goal->input)
    {
        ROS_WARN("Hey--mismatch!");
        ROS_INFO("g_count = %d; g_stamp = %d", g_count, result_.goal_stamp);
        g_count_failure   = true;      // 结束主程序
        ROS_WARN("Informing client of aborted goal");
        as_.setAborted(result_);       // 中断动作服务器 告诉客户端异常退出
    }
    else
    {
        as_.setSucceeded(result_);     // 结束动作服务器 告诉客户端成功结束
    }
}

int main(int argc, char ** argv)
{
    ros::init(argc, argv, "demo_action_server_node");
    ROS_INFO("Instantiating the demo action server: ");

    ExampleActionServer as_object;

    ROS_INFO("Going into spin");
    while(!g_count_failure)
    {
        ros::spinOnce();
    }
    return 0;
}