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

        int countdown_val_;

    public:
        ExampleActionServer();
       ~ExampleActionServer(void){}
        
        // 回调函数
        void excuteCB(const actionlib::SimpleActionServer<example_action_server::demoAction>::GoalConstPtr & goal);
};


// 默认构造函数 
// 创建动作服务器timer_action 指明回调函数excuteCB
ExampleActionServer::ExampleActionServer(): 
    as_(nh_, "timer_action", boost::bind(&ExampleActionServer::excuteCB, this, _1), false)
{                                       
    ROS_INFO("In constructor of exampleActionServer...");
    as_.start();                        
}


// 回调函数
void ExampleActionServer::excuteCB(const actionlib::SimpleActionServer<example_action_server::demoAction>::GoalConstPtr& goal)
{
    ROS_INFO("IN excuteCB");
    ROS_INFO("Goal input is %d", goal->input);
    ros::Rate timer(1.0);
    countdown_val_ = goal->input;

    while(countdown_val_ > 0)
    {
        ROS_INFO("countdown = %d", countdown_val_);
        // 中断服务执行
        if(as_.isPreemptRequested())
        {
            ROS_WARN("goal cancelled!");
            result_.output = countdown_val_;
            as_.setAborted(result_);
            return ;
        }

        feedback_.fdbk = countdown_val_;
        as_.publishFeedback(feedback_);
        countdown_val_ --;
        timer.sleep();
    }

    result_.output = countdown_val_;
    as_.setSucceeded(result_);
}

int main(int argc, char ** argv)
{
    ros::init(argc, argv, "timer_action_server_node");
    ROS_INFO("Instantiating the demo action server: ");

    ExampleActionServer as_object;
    ROS_INFO("Going into spin");
    ros::spin();
    return 0;
}