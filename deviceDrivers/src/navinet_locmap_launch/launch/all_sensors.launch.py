#!/usr/bin/env python3

import os
from launch import LaunchDescription
from launch.actions import DeclareLaunchArgument, IncludeLaunchDescription
from launch.substitutions import LaunchConfiguration
from launch_ros.actions import Node
from launch.launch_description_sources import PythonLaunchDescriptionSource
from ament_index_python.packages import get_package_share_directory


def generate_launch_description():
    # Get package directories
    mid360_pkg = get_package_share_directory('mid360_driver')
    hikvision_pkg = get_package_share_directory('hikvision_camera_driver')
    third_party_pkg = get_package_share_directory('third_party_camera_driver')
    stm32_pkg = get_package_share_directory('stm32_sync_driver')
    launch_pkg = get_package_share_directory('navinet_locmap_launch')
    
    # Declare launch arguments
    use_rviz_arg = DeclareLaunchArgument(
        'use_rviz',
        default_value='true',
        description='Launch RViz for visualization'
    )
    
    # Get launch configuration
    use_rviz = LaunchConfiguration('use_rviz')
    
    # Include individual sensor launch files
    mid360_launch = IncludeLaunchDescription(
        PythonLaunchDescriptionSource(
            os.path.join(mid360_pkg, 'launch', 'mid360.launch.py')
        )
    )
    
    hikvision_launch = IncludeLaunchDescription(
        PythonLaunchDescriptionSource(
            os.path.join(hikvision_pkg, 'launch', 'hikvision_camera.launch.py')
        )
    )
    
    third_party_launch = IncludeLaunchDescription(
        PythonLaunchDescriptionSource(
            os.path.join(third_party_pkg, 'launch', 'third_party_camera.launch.py')
        )
    )
    
    stm32_launch = IncludeLaunchDescription(
        PythonLaunchDescriptionSource(
            os.path.join(stm32_pkg, 'launch', 'stm32_sync.launch.py')
        )
    )
    
    # RViz for visualization
    rviz_node = Node(
        package='rviz2',
        executable='rviz2',
        name='rviz2',
        arguments=['-d', os.path.join(launch_pkg, 'config', 'navinet_locmap.rviz')],
        output='screen',
        condition=launch.conditions.IfCondition(use_rviz)
    )
    
    return LaunchDescription([
        use_rviz_arg,
        mid360_launch,
        hikvision_launch,
        third_party_launch,
        stm32_launch,
        rviz_node,
    ])
