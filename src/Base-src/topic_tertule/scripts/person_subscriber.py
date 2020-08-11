#!/usr/bin/env python
# -*- coding:utf-8  -*-
# 该例程将订阅/person_info话题，消息类型topic_tertule::person

import rospy
from topic_tertule.msg import person

def posecallback(msg):
    rospy.loginfo("Subscriber person Info: name:%s age:%d sex:%d",
                    msg.name, msg.age, msg.sex)

def person_subscriber():
    rospy.init_node('person_subscriber', anonymous=True)

    # 创建一个Subscriber，订阅话题/person_info, 注册回调函数posecallback
    rospy.Subscriber("/person_info", person, posecallback)

    # 循环等待回调函数
    rospy.spin()

if __name__ == '__main__':
    person_subscriber()