// clang: MatousFormat
/**  \file
     \brief Example file for the DynamicPublisher convenience class
     \author Matouš Vrba - vrbamato@fel.cvut.cz

     This example may be run after building *pairs_lib* by executing `rosrun pairs_lib dynamic_publisher_example`.

     See \ref dynamic_publisher/example.cpp.
 */

/**  \example "dynamic_publisher/example.cpp"

     This example may be run after building *pairs_lib* by executing `rosrun pairs_lib dynamic_publisher_example`.
 */

#include <pairs_lib/dynamic_publisher.h>
#include <std_msgs/Float32.h>
#include <geometry_msgs/Point.h>

int main(int argc, char **argv)
{
  /* Set up ROS. */
  const std::string node_name("dynamic_publisher_example");
  ros::init(argc, argv, node_name);
  ros::NodeHandle nh;

  // the class can be copied or initialized without a parameter (but then it won't use your node's namespacing, remapping etc.)
  pairs_lib::DynamicPublisher dynpub, dynpub2;
  dynpub = pairs_lib::DynamicPublisher(nh);

  ros::Duration slp(0.5);

  std_msgs::Float32 float_msg;
  geometry_msgs::Point pt_msg;

  ROS_INFO("Publishing topics! Use `rostopic list` and `rostopic echo <topic_name>` to see them.");
  while (ros::ok())
  {
    float_msg.data += 666.0f;
    dynpub.publish("float_topic", float_msg);
    /* Avoid publishing a message of different type on the same topic! */
    /* dynpub.publish("float_topic", pt_msg); */

    pt_msg.x = float_msg.data/1;
    pt_msg.y = float_msg.data/2;
    pt_msg.z = float_msg.data/3;
    dynpub.publish("point_topic", pt_msg);
    /* Avoid publishing a message of different type on the same topic! They will be ignored and will spam you with errors. */
    dynpub.publish("point_topic", float_msg);

    ros::spinOnce();
    slp.sleep();
  }

  return 0;
}
