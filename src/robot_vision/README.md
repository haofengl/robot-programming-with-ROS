# 机器视觉应用案例功能包

* 打开USB摄像头，并将ROS图像格式OpenCv图像格式相互转换
    ** roslaunch robot_vision usb_cam.launch  --启动摄像头，ROS和OpnCv图像格式转换并发布

* 物体追踪案例
    ** roslaunch robot_vision usb_cam.launch  --启动摄像头，ROS和OpnCv图像格式转换并发布
    ** roslaunch robot_vision motion_detector.launch  --启动物体识别功能，摄像头自动捕获第一幅图像，并和之后图像作比较起到识别作用
    ** rqt_image_view  --查看图像

* 人脸识别案例
    ** roslaunch robot_vision usb_cam.launch  --启动摄像头，ROS和OpnCv图像格式转换并发布
    ** roslaunch robot_vision face_detector.launch --启动人脸识别功能
    ** rqt_image_view  -- 查看图像

* 二维码识别案例  --（导航中二维码定位、引导机器人跟随运动）
    ** rosrun ar_track_alvar createMarker ID --生成值ID二维码图片（０－65535之间）
    ** roslaunch robot_vision usb_cam_with_calibration.launch   --启动USB摄像头，并加载标定文件
    ** roslaunch robot_vision ar_track_camera.launch   --启动二维码识别节点