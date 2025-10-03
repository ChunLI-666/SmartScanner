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
    bag_path_arg = DeclareLaunchArgument(
        'bag_path',
        default_value='/home/pi/navinet_locmap/data/rosbag2/navinet_data',
        description='Path to the bag file'
    )
    
    rate_arg = DeclareLaunchArgument(
        'rate',
        default_value='1.0',
        description='Playback rate multiplier'
    )
    
    loop_arg = DeclareLaunchArgument(
        'loop',
        default_value='false',
        description='Loop playback'
    )
    
    # Get launch configuration
    bag_path = LaunchConfiguration('bag_path')
    rate = LaunchConfiguration('rate')
    loop = LaunchConfiguration('loop')
    
    # Rosbag2 playback command
    playback_cmd = ExecuteProcess(
        cmd=[
            'ros2', 'bag', 'play',
            bag_path,
            '--rate', rate,
            '--loop' if loop == 'true' else ''
        ],
        output='screen'
    )
    
    # RViz for visualization
    rviz_node = Node(
        package='rviz2',
        executable='rviz2',
        name='rviz2',
        arguments=['-d', os.path.join(pkg_share, 'config', 'playback.rviz')],
        output='screen'
    )
    
    return LaunchDescription([
        bag_path_arg,
        rate_arg,
        loop_arg,
        playback_cmd,
        rviz_node,
    ])
