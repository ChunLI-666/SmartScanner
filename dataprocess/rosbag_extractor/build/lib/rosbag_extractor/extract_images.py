#!/usr/bin/env python

import os
import cv2
import rosbag
from cv_bridge import CvBridge
from sensor_msgs.msg import Image

def extract_and_save_images(bag_file, output_folder):
    """
    Extracts images from a ROS bag file and saves them to the specified folder.
    
    :param bag_file: Path to the ROS bag file.
    :param output_folder: Directory where images will be saved.
    """
    if not os.path.exists(output_folder):
        os.makedirs(output_folder)

    bag = rosbag.Bag(bag_file, 'r')
    bridge = CvBridge()
    
    for topic, msg, t in bag.read_messages(topics=['/hikrobot_camera/rgb']):
        if isinstance(msg, Image):
            cv_image = bridge.imgmsg_to_cv2(msg, desired_encoding='passthrough')
            timestamp = t.to_nsec()
            image_filename = os.path.join(output_folder, f"{timestamp}.png")
            cv2.imwrite(image_filename, cv_image)
            print(f"Saved {image_filename}")
    
    bag.close()

if __name__ == "__main__":
    import argparse
    
    parser = argparse.ArgumentParser(description="Extract images from a ROS bag.")
    parser.add_argument("bag_file", help="Input ROS bag file")
    parser.add_argument("output_folder", help="Output folder for the images")
    args = parser.parse_args()
    
    extract_and_save_images(args.bag_file, args.output_folder)
