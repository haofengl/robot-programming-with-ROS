#!/usr/bin/env python
# -*- coding: utf-8 -*-
# 该例程将发布/person_info话题，消息类型为topic_tertule::person

import rospy
from topic_tertule.msg import person

def publisher():
    # ROS节点初始化
    rospy.init_node('person_publisher', anonymous=True)

    # 创建一个publisher,发布/turtle1/cmd_vel的topic，消息类型为geometry_msgs::Twist,队列长为10
    person_info_pub = rospy.Publisher('/person_info', person, queue_size=10)

    # 设置循环频率
    rate = rospy.Rate(1)

    while not rospy.is_shutdown():
        # 初始化topic_tertle::person类型的消息
        person_msg = person()
        person_msg.name = "WuKong"
        person_msg.age  = 1
        person_msg.sex  = person.male

        # 发布消息
        person_info_pub.publish(person_msg)
        rospy.loginfo("Publish person message[%s, %d, %d]",
                        person_msg.name, person_msg.age, person_msg.sex)

        
        # 按照循环频率延时
        rate.sleep()

if __name__ == '__main__':
    try:
        publisher()
    except rospy.ROSInterruptException:
        pass
