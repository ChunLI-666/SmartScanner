#!/usr/bin/env python

import os
import cv2
import rosbag
import argparse
import logging
from cv_bridge import CvBridge
from sensor_msgs.msg import Image
from tqdm import tqdm
import subprocess

# Set up logging
logging.basicConfig(level=logging.INFO)
logger = logging.getLogger("rosbag_extractor")

def extract_and_save_images(bag_file, output_folder, topic, img_format):
    """
    Extracts images from a ROS bag file and saves them to the specified folder.
    
    :param bag_file: Path to the ROS bag file.
    :param output_folder: Directory where images will be saved.
    :param topic: The ROS topic to extract images from.
    :param img_format: The format to save images in.
    """
    try:
        bag = rosbag.Bag(bag_file, 'r')
        logger.info("Successfully opened ROS bag.")
    except Exception as e:
        logger.error(f"Failed to open ROS bag: {e}")
        return
    
    bridge = CvBridge()

    # If no output folder given, create one based on the bag file's name
    if not output_folder:
        bag_name = os.path.splitext(os.path.basename(bag_file))[0]
        folder_name = bag_name + '-images'
        output_folder = os.path.join(os.path.dirname(bag_file), folder_name)

    if os.path.exists(output_folder):
        try:
            os.rmdir(output_folder)
            print("Directory '% s' has been removed successfully" % output_folder)
        except OSError as error:
            print(error)
            print("Directory '% s' can not be removed" % output_folder)
    if not os.path.exists(output_folder):
        try:
            os.makedirs(output_folder)
            print("Directory '% s' has been created successfully" % output_folder)
        except OSError as error:
            print(error)
            print("Directory '% s' can not be created" % output_folder)
    

    try:
        total_images = bag.get_message_count(topic_filters=[topic])
        with tqdm(total=total_images, desc=f"Extracting images from {topic}", unit="image",  leave=True, position=0) as pbar:
            for topic, msg, t in bag.read_messages(topics=[topic]):
                try:
                    # cv_image = bridge.imgmsg_to_cv2(msg, desired_encoding='passthrough')
                    cv_image = bridge.imgmsg_to_cv2(msg, desired_encoding='bgr8')
                    # timestamp = t.to_sec()
                    timestamp = msg.header.stamp.to_sec()
                    image_filename = os.path.join(output_folder, f"{timestamp:.6f}.{img_format}")
                    cv2.imwrite(image_filename, cv_image)
                    # logger.info(f"Successfully saved {image_filename}")
                except Exception as e:
                    logger.error(f"Failed to extract image: {e}")
                finally:
                    pbar.update(1)
    except Exception as e:
        logger.error(f"Error during image extraction: {e}")
    finally:
        bag.close()
        logger.info("ROS bag closed.")
    
    video_path =  f'{output_folder}/overview.mp4'

    images_to_video(output_folder,video_path, img_format)

def images_to_video(img_folder, output_vid_file,img_format):
    """Creates a video from images in a specified folder.
    Args:
        img_folder (str): Path to the folder containing the images
        output_vid_file (str): Path for the output video file.
    """
    # Ensure the image folder exists
    if not os.path.exists(img_folder):
        logger.debug(f"The specified image folder '{img_folder}' does not exist.")
        return
    
    # Ensure output directory exists
    output_dir = os.path.dirname(output_vid_file)
    if not os.path.exists(output_dir):
        os.makedirs(output_dir, exist_ok=False)
    
    # Construct the ffmpeg command
    # command = [
    #     'ffmpeg', 
    #     '-y', 
    #     '-threads', '16', 
    #     '-framerate', '30'
    #     '-pattern_type', 'glob',
    #     '-i', f'{img_folder}/*.png', 
    #     # '-profile:v', 'baseline',
    #     '-level', '3.0', 
    #     '-c:v', 'libx264', 
    #     '-pix_fmt', 'yuv420p', 
    #         '-r', '30'
    #     # '-an', 
    #     '-v', 'error', output_vid_file
    # ]
        
    # ## high quality mp4
    # command = [
    #     'ffmpeg', '-y', 
    #     '-threads', '16', 
    #     '-framerate', '5', 
    #     '-pattern_type', 'glob', 
    #     '-i', f'{img_folder}/*.{img_format}', 
    #     '-c:v', 'libx264', 
    #     '-pix_fmt', 'yuv420p', 
    #     '-r', '5', 
    #     '-v', 'error', output_vid_file
    # ]

    ## low quality mp4 for overview
    command = [
        'ffmpeg', '-y',
        '-threads', '16',
        '-framerate', '5',
        '-pattern_type', 'glob',
        '-i', f'{img_folder}/*.{img_format}',
        '-c:v', 'libx264',
        '-preset', 'ultrafast',  # Use a faster preset to reduce encoding time and file size
        '-b:v', '500k',  # Lower bitrate to reduce quality and file size
        '-pix_fmt', 'yuv420p',
        '-r', '5',
        '-v', 'error', output_vid_file
    ]


    logger.info(f'Running \"{" ".join(command)}\"')
    subprocess.call(command)
    logger.info("Generate video success!")


if __name__ == "__main__":
    parser = argparse.ArgumentParser(description="Extract images from a ROS bag.")
    parser.add_argument("bag_file", help="Input ROS bag file")
    parser.add_argument("--output_folder", help="Output folder for the images")
    parser.add_argument("--topic", default="/hikrobot_camera/rgb", help="Image topic to extract (default: /camera/image_raw)")
    parser.add_argument("--format", default="jpg", help="Format to save images in (default: jpg)")
    # parser.add_argument("video_file", default="")
    args = parser.parse_args()
    
    extract_and_save_images(args.bag_file, args.output_folder, args.topic, args.format)
