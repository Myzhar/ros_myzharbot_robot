#include <ros/ros.h>
#include <tf/transform_broadcaster.h>

// >>>>> Global variables
const std::string default_base_link_string = "base_link";
std::string base_link_string = default_base_link_string;

const std::string default_body_chassis_link_string = "body_chassis_link";
std::string body_chassis_link_string = default_body_chassis_link_string;

const std::string default_sprocket_prefix_link_string = "spr_";
std::string sprocket_prefix_link_string = default_sprocket_prefix_link_string;

double default_sprocket_x_offset = 0.135;
double sprocket_x_offset = default_sprocket_x_offset;

double default_sprocket_y_offset = 0.170;
double sprocket_y_offset = default_sprocket_y_offset;

double default_sprocket_z_offset = 0.047625;
double sprocket_z_offset = default_sprocket_z_offset;

double default_body_chassis_height = 0.0775; // The center of the central body is 7.75 height above ground
double body_chassis_height = default_body_chassis_height;
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

    while(nh.ok()){

        // tf: /body_chassis_link -> /base_link
        broadcast_body_chassis( broadcaster );

        broadcast_sprockets( broadcaster );

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

    // >>>>> Body Chassis
    if (nh.hasParam("/tf/" + default_body_chassis_link_string))
    {
        nh.getParam("/tf/" + default_body_chassis_link_string, body_chassis_link_string);
    }
    else
    {
        nh.setParam("/tf/" + default_body_chassis_link_string, default_body_chassis_link_string);
    }

    if (nh.hasParam("/myzharbot/body_chassis_height"))
    {
        nh.getParam("/myzharbot/body_chassis_height", body_chassis_height);
    }
    else
    {
        nh.setParam("/myzharbot/body_chassis_height", default_body_chassis_height);
    }
    // <<<<< Body Chassis

    // >>>>> Sprockets
    if (nh.hasParam("/tf/" + default_sprocket_prefix_link_string))
    {
        nh.getParam("/tf/" + default_sprocket_prefix_link_string, sprocket_prefix_link_string);
    }
    else
    {
        nh.setParam("/tf/" + default_sprocket_prefix_link_string, default_sprocket_prefix_link_string);
    }

    if (nh.hasParam("/myzharbot/sprocket_x_offset"))
    {
        nh.getParam("/myzharbot/sprocket_x_offset", sprocket_x_offset);
    }
    else
    {
        nh.setParam("/myzharbot/sprocket_x_offset", default_sprocket_x_offset);
    }

    if (nh.hasParam("/myzharbot/sprocket_y_offset"))
    {
        nh.getParam("/myzharbot/sprocket_y_offset", sprocket_y_offset);
    }
    else
    {
        nh.setParam("/myzharbot/sprocket_y_offset", default_sprocket_y_offset);
    }

    if (nh.hasParam("/myzharbot/sprocket_z_offset"))
    {
        nh.getParam("/myzharbot/sprocket_z_offset", sprocket_z_offset);
    }
    else
    {
        nh.setParam("/myzharbot/sprocket_z_offset", default_sprocket_z_offset);
    }
    // <<<<< Sprockets
}

void broadcast_body_chassis(tf::TransformBroadcaster& broadcaster)
{

    // body_chassis_link->base_link transform should thus give the height above ground as the z-component
    broadcaster.sendTransform( tf::StampedTransform(tf::Transform(tf::Quaternion(0, 0, 0, 1), tf::Vector3(0.0,0.0,body_chassis_height)),
                                                    ros::Time::now(),
                                                    base_link_string,
                                                    body_chassis_link_string ) );
}

void broadcast_sprockets(tf::TransformBroadcaster& broadcaster)
{
    tf::Quaternion quat = tf::createQuaternionFromRPY(1.57075, 0, 0 );

    broadcaster.sendTransform( tf::StampedTransform(tf::Transform(quat, tf::Vector3(sprocket_x_offset,sprocket_y_offset,sprocket_z_offset)),
            ros::Time::now(),
            base_link_string,
            sprocket_prefix_link_string + "bfl" ) );

    broadcaster.sendTransform( tf::StampedTransform(tf::Transform(quat, tf::Vector3(sprocket_x_offset,-sprocket_y_offset,sprocket_z_offset)),
            ros::Time::now(),
            base_link_string,
            sprocket_prefix_link_string + "brl" ) );

    broadcaster.sendTransform( tf::StampedTransform(tf::Transform(quat, tf::Vector3(-sprocket_x_offset,sprocket_y_offset,sprocket_z_offset)),
            ros::Time::now(),
            base_link_string,
            sprocket_prefix_link_string + "bfr" ) );

    broadcaster.sendTransform( tf::StampedTransform(tf::Transform(quat, tf::Vector3(-sprocket_x_offset,-sprocket_y_offset,sprocket_z_offset)),
            ros::Time::now(),
            base_link_string,
            sprocket_prefix_link_string + "brr" ) );
}

