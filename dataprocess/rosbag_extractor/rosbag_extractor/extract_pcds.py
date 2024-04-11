#!/usr/bin/env python

import os
import numpy as np
import open3d as o3d
import rosbag
import sensor_msgs.point_cloud2 as pc2
from sensor_msgs.msg import PointCloud2
import json
import logging
from tqdm import tqdm
import argparse

# Setup logging
logging.basicConfig(level=logging.INFO)
logger = logging.getLogger('point_cloud_extractor')

def extract_and_save_point_clouds(bag_file, output_folder, topic):
    """
    Extracts point cloud data and additional fields from a ROS bag file and saves them as PCD files along with JSON files for additional fields.
    
    :param bag_file: Path to the ROS bag file.
    :param output_folder: Directory where PCD and JSON files will be saved.
    :param topic: The point cloud topic to extract from.
    """
    if not os.path.exists(output_folder):
        os.makedirs(output_folder)

    try:
        bag = rosbag.Bag(bag_file, 'r')
        logger.info("Successfully opened ROS bag.")
    except Exception as e:
        logger.error(f"Failed to open ROS bag: {e}")
        return

    try:
        total_points = bag.get_message_count(topic_filters=[topic])
        with tqdm(total=total_points, desc=f"Extracting point clouds from {topic}", unit="msg") as pbar:
            for _, msg, t in bag.read_messages(topics=[topic]):
                # if isinstance(msg, PointCloud2):
                # Extract all fields and convert to numpy array
                fields = [field.name for field in msg.fields]
                gen = pc2.read_points(msg, skip_nans=True, field_names=fields)
                all_data = np.array(list(gen))

                # Save point cloud data
                timestamp = t.to_nsec()
                process_and_save_point_cloud(all_data, fields, output_folder, timestamp)
                pbar.update(1)
    except Exception as e:
        logger.error(f"Error during point cloud extraction: {e}")
    finally:
        bag.close()
        logger.info("ROS bag closed.")

# def save_point_cloud(all_data, fields, output_folder, timestamp):
#     """
#     Saves point cloud data to PCD and additional fields to JSON.
#     :param all_data: All extracted data as numpy array.
#     :param fields: Field names of the data.
#     :param output_folder: Output directory for files.
#     :param timestamp: Timestamp for naming files.
#     """
#     try:
#         # Assuming 'x', 'y', 'z' are the first three fields
#         pcd = o3d.geometry.PointCloud()
#         pcd.points = o3d.utility.Vector3dVector(all_data[:, :3])

#         pcd_filename = os.path.join(output_folder, f"{timestamp}.pcd")
#         o3d.io.write_point_cloud(pcd_filename, pcd)

#         # Save additional fields
#         additional_fields = all_data[:, 3:]
#         additional_data_filename = os.path.join(output_folder, f"{timestamp}_additional_fields.json")
#         additional_data = {fields[i+3]: additional_fields[:, i].tolist() for i in range(additional_fields.shape[1])}
        
#         with open(additional_data_filename, 'w') as f:
#             json.dump(additional_data, f)

#         logger.info(f"Saved {pcd_filename} and {additional_data_filename}")
#     except Exception as e:
#         logger.error(f"Failed to save point cloud for timestamp {timestamp}: {e}")

def process_and_save_point_cloud(all_data, fields, output_folder, timestamp):
    """
    Processes point cloud data, embedding intensity and ring information into the rgb field, and saves as PCD.
    
    :param all_data: All extracted data as numpy array.
    :param fields: Field names of the data.
    :param output_folder: Output directory for files.
    :param timestamp: Timestamp for naming files.
    """
    try:
        # Assuming 'x', 'y', 'z' are the first three fields and followed by 'intensity', 'ring'
        # pcd = o3d.geometry.PointCloud()
        # pcd.points = o3d.utility.Vector3dVector(all_data[:, :3])

        # # Map 'intensity' and 'ring' to RGB
        # # Normalize and convert to uint8 if necessary
        # intensity = np.clip(all_data[:, fields.index('intensity')] / np.max(all_data[:, fields.index('intensity')]), 0, 1) * 255
        # # ring = np.clip(all_data[:, fields.index('ring')] / np.max(all_data[:, fields.index('ring')]), 0, 1) * 255
        # # rgb = np.vstack((intensity, ring, np.zeros_like(intensity))).astype(np.uint8).T
        # rgb = np.vstack((intensity, np.zeros_like(intensity))).astype(np.uint8).T
        # pcd.colors = o3d.utility.Vector3dVector(rgb / 255.0)  # Open3D expects colors in [0, 1]

        pcd = o3d.geometry.PointCloud()
        pcd.points = o3d.utility.Vector3dVector(all_data[:, :3])

        # Normalize intensity and map to RGB
        intensity = all_data[:, fields.index('intensity')]
        # Normalize intensity values to [0, 255]
        intensity_normalized = np.clip(intensity / np.max(intensity), 0, 1) * 255
        rgb = np.vstack((intensity_normalized, intensity_normalized, intensity_normalized)).astype(np.uint8).T
        pcd.colors = o3d.utility.Vector3dVector(rgb / 255.0)  # Open3D expects colors in [0, 1]

        # Save to PCD file
        pcd_filename = os.path.join(output_folder, f"{timestamp}.pcd")
        o3d.io.write_point_cloud(pcd_filename, pcd)
        
        logger.info(f"Saved {pcd_filename}")
    except Exception as e:
        logger.error(f"Failed to save point cloud for timestamp {timestamp}: {e}")

if __name__ == "__main__":
    parser = argparse.ArgumentParser(description="Extract point clouds and additional fields from a ROS bag.")
    parser.add_argument("bag_file", help="Input ROS bag file")
    parser.add_argument("output_folder", help="Output folder for the point clouds and additional fields")
    parser.add_argument("--topic", default="/Pandar/XT32_M2X/pandar", help="Point cloud topic to extract (default: /your_point_cloud_topic)")
    args = parser.parse_args()
    
    extract_and_save_point_clouds(args.bag_file, args.output_folder, args.topic)
