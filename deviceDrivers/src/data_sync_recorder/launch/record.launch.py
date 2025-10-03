#!/usr/bin/env python3

import os
from launch import LaunchDescription
from launch.actions import DeclareLaunchArgument, ExecuteProcess
from launch.substitutions import LaunchConfiguration
from launch_ros.actions import Node
from ament_index_python.packages import get_package_share_directory


def generate_launch_description():
    # Get the launch directory
    pkg_share = get_package_share_directory('data_sync_recorder')
    
    # Declare launch arguments
    bag_name_arg = DeclareLaunchArgument(
        'bag_name',
        default_value='navinet_data',
        description='Name of the bag file'
    )
    
    output_dir_arg = DeclareLaunchArgument(
        'output_dir',
        default_value='/home/pi/navinet_locmap/data/rosbag2',
        description='Output directory for bag files'
    )
    
    duration_arg = DeclareLaunchArgument(
        'duration',
        default_value='0',
        description='Recording duration in seconds (0 for unlimited)'
    )
    
    # Get launch configuration
    bag_name = LaunchConfiguration('bag_name')
    output_dir = LaunchConfiguration('output_dir')
    duration = LaunchConfiguration('duration')
    
    # Create output directory if it doesn't exist
    create_dir_cmd = ExecuteProcess(
        cmd=['mkdir', '-p', output_dir],
        output='screen'
    )
    
    # Rosbag2 recording command
    record_cmd = ExecuteProcess(
        cmd=[
            'ros2', 'bag', 'record',
            '/mid360/pointcloud',
            '/mid360/imu',
            '/hikvision_camera/image',
            '/hikvision_camera/camera_info',
            '/third_party_camera/image',
            '/third_party_camera/camera_info',
            '/imu/data',
            '/sync/trigger',
            '/sync/status',
            '/tf',
            '/tf_static',
            '-o', [output_dir, '/', bag_name],
            '--duration', duration
        ],
        output='screen'
    )
    
    return LaunchDescription([
        bag_name_arg,
        output_dir_arg,
        duration_arg,
        create_dir_cmd,
        record_cmd,
    ])
