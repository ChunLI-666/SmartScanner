#!/usr/bin/env python3

import os
from launch import LaunchDescription
from launch.actions import DeclareLaunchArgument
from launch.substitutions import LaunchConfiguration
from launch_ros.actions import Node
from ament_index_python.packages import get_package_share_directory


def generate_launch_description():
    # Get the launch directory
    pkg_share = get_package_share_directory('hikvision_camera_driver')
    
    # Declare launch arguments
    config_file_arg = DeclareLaunchArgument(
        'config_file',
        default_value=os.path.join(pkg_share, 'config', 'hikvision_camera.yaml'),
        description='Path to the camera configuration file'
    )
    
    camera_name_arg = DeclareLaunchArgument(
        'camera_name',
        default_value='hikvision_camera',
        description='Name of the camera'
    )
    
    frame_id_arg = DeclareLaunchArgument(
        'frame_id',
        default_value='hikvision_camera',
        description='Frame ID for the camera data'
    )
    
    # Get launch configuration
    config_file = LaunchConfiguration('config_file')
    camera_name = LaunchConfiguration('camera_name')
    frame_id = LaunchConfiguration('frame_id')
    
    # Hikvision camera driver node
    camera_node = Node(
        package='hikvision_camera_driver',
        executable='hikvision_camera_node',
        name='hikvision_camera',
        output='screen',
        parameters=[{
            'config_file': config_file,
            'camera_name': camera_name,
            'frame_id': frame_id,
        }],
        remappings=[
            ('/hikvision_camera/image_raw', '/hikvision_camera/image'),
            ('/hikvision_camera/camera_info', '/hikvision_camera/camera_info'),
        ]
    )
    
    # Static transform publisher for camera
    static_transform_publisher = Node(
        package='tf2_ros',
        executable='static_transform_publisher',
        name='hikvision_camera_static_transform',
        arguments=['0', '0', '0', '0', '0', '0', 'base_link', frame_id]
    )
    
    return LaunchDescription([
        config_file_arg,
        camera_name_arg,
        frame_id_arg,
        camera_node,
        static_transform_publisher,
    ])
