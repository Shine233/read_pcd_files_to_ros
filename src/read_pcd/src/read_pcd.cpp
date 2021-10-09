//
// Created by yao on 9/23/21.
//

#include<ros/ros.h>
#include<pcl/point_cloud.h>
#include<pcl_conversions/pcl_conversions.h>
#include<sensor_msgs/PointCloud2.h>
#include<pcl/io/pcd_io.h> //which contains the required definitions to load and store point clouds to PCD and other file formats.

int main(int argc,char **argv){

    ros::init(argc,argv,"pcd_to_ros");
    ros::NodeHandle nh;
    ros::Publisher pcl_pub=nh.advertise<sensor_msgs::PointCloud2> ("/map_result", 1);


    pcl::PointCloud<pcl::PointXYZ> cloud;
    sensor_msgs::PointCloud2 output;
    pcl::io::loadPCDFile("/home/yao/Workspace/hdl_graph_slam_ws/src/hdl_graph_slam/map.pcd",cloud);//修改自己pcd文件所在路径

    //Convert the cloud to ROS message

    pcl::toROSMsg(cloud, output);
    output.header.frame_id="map";//this has been done in order to be able to visualize our PointCloud2 message on the RViz visualizer
    std::cout<<"point cloud size: "<<output.data.size() <<std::endl;

    //！！！这一步需要注意，是后面rviz的 fixed_frame  !!!敲黑板，画重点。
//    std::cout<<"pub";
    ros::Rate loop_rate(10);
    while(ros::ok())
    {
        /* code for loop body */
        pcl_pub.publish(output);
        ros::spinOnce();
        loop_rate.sleep();
    }
    return 0;
}
