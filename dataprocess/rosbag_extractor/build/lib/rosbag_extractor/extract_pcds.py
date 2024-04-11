#!/usr/bin/env python

import os
import open3d as o3d
import rosbag
import sensor_msgs.point_cloud2 as pc2
from sensor_msgs.msg import PointCloud2

def extract_and_save_point_clouds(bag_file, output_folder):
    """
    Extracts point cloud data from a ROS bag file and saves them as PCD files.
    
    :param bag_file: Path to the ROS bag file.
    :param output_folder: Directory where PCD files will be saved.
    """
    if not os.path.exists(output_folder):
        os.makedirs(output_folder)

    bag = rosbag.Bag(bag_file, 'r')
    
    for topic, msg, t in bag.read_messages(topics=['/your_point_cloud_topic']):
        if isinstance(msg, PointCloud2):
            # Convert to PCL data
            gen = pc2.read_points(msg, skip_nans=True, field_names=("x", "y", "z"))
            points = list(gen)
            
            # Create Open3D point cloud
            pcd = o3d.geometry.PointCloud()
            pcd.points = o3d.utility.Vector3dVector(points)
            
            # Save to PCD file
            timestamp = t.to_nsec()
            pcd_filename = os.path.join(output_folder, f"{timestamp}.pcd")
            o3d.io.write_point_cloud(pcd_filename, pcd)
            print(f"Saved {pcd_filename}")
    
    bag.close()

if __name__ == "__main__":
    import argparse
    
    parser = argparse.ArgumentParser(description="Extract point clouds from a ROS bag.")
    parser.add_argument("bag_file", help="Input ROS bag file")
    parser.add_argument("output_folder", help="Output folder for the point clouds")
    args = parser.parse_args()
    
    extract_and_save_point_clouds(args.bag_file, args.output_folder)
