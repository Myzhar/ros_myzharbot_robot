#myzharbot_robot_ros

This repository contains the configuration for the robot MyzharBot.
MyzharBot uses RoboController board to drive the motors using "serial_bridge" ROS package.

##Environment setup

###On the remote PC
```bash
$ export ROS_HOSTNAME=myzharbot.local
$ export ROS_MASTER_URI="http://myzharbot.local:11311"
```

verify correct change with:
```bash
$ export | grep ROS
```

Execute the control GUI:
```bash
$ roslaunch myzharbot_robot_ros gui_sensor.launch
```

On a different terminal (Ctrl+Alt+t) run the keyboard teleoperation node:
```bash
$ rosrun serial_bridge keybrd_teleop_node
```

###On the Robot
```bash
$ export ROS_HOSTNAME=myzharbot.local
$ export ROS_MASTER_URI="http://myzharbot.local:11311"
```

verify correct change with:
```bash
$ export | grep ROS
```

Execute the robot nodes:
```bash
$ roslaunch myzharbot_robot_ros robot.launch
```
