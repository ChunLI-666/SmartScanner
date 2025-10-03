#!/usr/bin/env python3

import os
from launch import LaunchDescription
from launch.actions import DeclareLaunchArgument
from launch.substitutions import LaunchConfiguration
from launch_ros.actions import Node
from ament_index_python.packages import get_package_share_directory


def generate_launch_description():
    # Get the launch directory
    pkg_share = get_package_share_directory('stm32_sync_driver')
    
    # Declare launch arguments
    config_file_arg = DeclareLaunchArgument(
        'config_file',
        default_value=os.path.join(pkg_share, 'config', 'stm32_sync.yaml'),
        description='Path to the STM32 sync configuration file'
    )
    
    device_port_arg = DeclareLaunchArgument(
        'device_port',
        default_value='/dev/ttyUSB0',
        description='Serial port for STM32 communication'
    )
    
    baud_rate_arg = DeclareLaunchArgument(
        'baud_rate',
        default_value='115200',
        description='Baud rate for serial communication'
    )
    
    # Get launch configuration
    config_file = LaunchConfiguration('config_file')
    device_port = LaunchConfiguration('device_port')
    baud_rate = LaunchConfiguration('baud_rate')
    
    # STM32 sync driver node
    stm32_sync_node = Node(
        package='stm32_sync_driver',
        executable='stm32_sync_node',
        name='stm32_sync',
        output='screen',
        parameters=[{
            'config_file': config_file,
            'device_port': device_port,
            'baud_rate': baud_rate,
        }],
        remappings=[
            ('/stm32_sync/imu', '/imu/data'),
            ('/stm32_sync/sync_trigger', '/sync/trigger'),
            ('/stm32_sync/status', '/sync/status'),
        ]
    )
    
    # Static transform publisher for IMU
    static_transform_publisher = Node(
        package='tf2_ros',
        executable='static_transform_publisher',
        name='imu_static_transform',
        arguments=['0', '0', '0', '0', '0', '0', 'base_link', 'imu_link']
    )
    
    return LaunchDescription([
        config_file_arg,
        device_port_arg,
        baud_rate_arg,
        stm32_sync_node,
        static_transform_publisher,
    ])
