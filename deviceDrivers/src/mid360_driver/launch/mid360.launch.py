#!/usr/bin/env python3

import os
from launch import LaunchDescription
from launch.actions import DeclareLaunchArgument
from launch.substitutions import LaunchConfiguration
from launch_ros.actions import Node
from ament_index_python.packages import get_package_share_directory


def generate_launch_description():
    # Get the launch directory
    pkg_share = get_package_share_directory('mid360_driver')
    
    # Declare launch arguments
    config_file_arg = DeclareLaunchArgument(
        'config_file',
        default_value=os.path.join(pkg_share, 'config', 'mid360_config.json'),
        description='Path to the Mid360 configuration file'
    )
    
    frame_id_arg = DeclareLaunchArgument(
        'frame_id',
        default_value='livox_frame',
        description='Frame ID for the LiDAR data'
    )
    
    # Get launch configuration
    config_file = LaunchConfiguration('config_file')
    frame_id = LaunchConfiguration('frame_id')
    
    # Mid360 driver node with Livox SDK2
    mid360_driver_node = Node(
        package='mid360_driver',
        executable='mid360_driver_node',
        name='mid360_driver',
        output='screen',
        parameters=[{
            'lidar_ip': '192.168.1.100',
            'host_ip': '192.168.1.5',
            'frame_id': frame_id,
            'publish_freq': 10.0,
        }],
        remappings=[
            ('/mid360/pointcloud', '/mid360/pointcloud'),
            ('/mid360/imu', '/mid360/imu'),
        ]
    )
    
    # Static transform publisher for Mid360
    static_transform_publisher = Node(
        package='tf2_ros',
        executable='static_transform_publisher',
        name='mid360_static_transform',
        arguments=['0', '0', '0', '0', '0', '0', 'base_link', frame_id]
    )
    
    return LaunchDescription([
        config_file_arg,
        frame_id_arg,
        mid360_driver_node,
        static_transform_publisher,
    ])
