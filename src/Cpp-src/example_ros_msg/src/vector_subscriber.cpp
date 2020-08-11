#include <ros/ros.h>
#include <custom_msgs/VecofDoubles.h>

void myCallback(const custom_msgs::VecofDoubles & message_holder)
{
    std::vector <double> vec_of_doubles = message_holder.dbl_vec;
    int nvals = vec_of_doubles.size();
    for(int i=0; i<nvals; i++)
    {
        ROS_INFO("vec[%d] = %f", i, vec_of_doubles[i]);
    }
    ROS_INFO("\n");
}

int main(int argc, char ** argv)
{
    ros::init(argc, argv, "vector_subscriber");
    ros::NodeHandle nh;

    ros::Subscriber my_subscriber_object = nh.subscribe("vec_topic", 1, myCallback);

    ros::spin();

    return 0;
}