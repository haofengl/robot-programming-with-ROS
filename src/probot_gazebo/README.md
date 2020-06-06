# 这是将anno机械臂gazebo仿真与rviz上位机联系控制的功能包
 * gazebo物理仿真和真实机器人一样，要让其在gazebo中动起来必须添加一些物理属性
    ** <inertial>  --惯性属性
    ** <collision>  --碰撞、摩擦参数
    ** <transmission>  --传动装置（舵机、马达等）
    ** <controls>  --控制器（控制舵机运动）