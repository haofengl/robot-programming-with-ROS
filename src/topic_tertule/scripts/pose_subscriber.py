#!/usr/bin/env python
# -*- coding:utf-8  -*-
# 该例程将订阅/turtle1/pose话题，消息类型turtlesim::Pose

import rospy
from topic_tertle.msg import Pose

def posecallback(msg):
    rospy.loginfo("Turtle pose: x:%0.6f, y:%0.6f", msg.x, msg.y)

def pose_subscriber():
    rospy.init_node('pose_subscriber', anonymous=True)

    # 创建一个Subscriber，订阅话题/turtle1/pose, 注册回调函数posecallback
    rospy.Subscriber("/turtle1/pose", Pose, posecallback)

    # 循环等待回调函数
    rospy.spin()

if __name__ == '__main__':
    pose_subscriber()