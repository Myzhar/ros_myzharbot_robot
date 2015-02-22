#include <ros/ros.h>
#include <tf/transform_broadcaster.h>
#include <sensor_msgs/JointState.h>

// >>>>> Global variables
const std::string default_base_link_string = "base_link";
std::string base_link_string = default_base_link_string;

const std::string default_body_chassis_link_string = "body_chassis_link";
std::string body_chassis_link_string = default_body_chassis_link_string;

const std::string default_sprocket_prefix_link_string = "spr_";
std::string sprocket_prefix_link_string = default_sprocket_prefix_link_string;
// <<<<< Global variables

// >>>>> Functions declarations
void load_params(ros::NodeHandle& nh);
void broadcast_body_chassis(tf::TransformBroadcaster& broadcaster);
void broadcast_sprockets(tf::TransformBroadcaster& broadcaster);
// <<<<< Functions declarations


int main(int argc, char** argv){
    ros::init(argc, argv, "myzharbot_tf_node");
    ros::NodeHandle nh;

    load_params( nh );

    ros::Rate r(30);

    tf::TransformBroadcaster broadcaster;

    ROS_INFO("myzharbot_tf_node node loaded!");

    while(nh.ok())
    {
        // TODO publish passive sprocket joint state using the joint state of the active ones

        ros::spinOnce();
        r.sleep();
    }
}

void load_params(ros::NodeHandle& nh)
{
    if (nh.hasParam("/tf/" + default_base_link_string))
    {
        nh.getParam("/tf/" + default_base_link_string, base_link_string);
    }
    else
    {
        nh.setParam("/tf/" + default_base_link_string, default_base_link_string);
    }

}



