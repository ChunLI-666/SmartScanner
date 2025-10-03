# SmartScanner Device Drivers

This directory contains all hardware drivers for the NaviNet LocMap system.

## Directory Structure

```
deviceDrivers/
├── src/                          # ROS2 drivers (active)
│   ├── mid360_driver/           # Mid360 LiDAR driver
│   ├── hikvision_camera_driver/ # Hikvision camera driver
│   ├── third_party_camera_driver/ # Third-party camera driver
│   ├── stm32_sync_driver/       # STM32 sync board driver
│   ├── data_sync_recorder/      # Data recording and playback
│   ├── navinet_locmap_launch/   # Main launch files
│   └── hikrobot-mvs-camera-ros/ # ROS1 Hikrobot driver (reference)
└── ros1_archive/                # Archived ROS1 drivers
    └── MV-CH120-10GC/          # Archived MV camera driver
```

## ROS2 Drivers (src/)

All ROS2 drivers are located in the `src/` directory and are symlinked to the main workspace `src/` directory for building.

### Active Drivers
- **mid360_driver**: Livox Mid360 LiDAR sensor driver
- **hikvision_camera_driver**: Hikvision industrial camera driver
- **third_party_camera_driver**: Third-party camera driver (model TBD)
- **stm32_sync_driver**: STM32-based hardware synchronization board
- **data_sync_recorder**: Data recording and playback functionality
- **navinet_locmap_launch**: Main launch files and system integration

### Reference Driver
- **hikrobot-mvs-camera-ros**: Original ROS1 Hikrobot camera driver (kept for reference)

## ROS1 Archive (ros1_archive/)

Legacy ROS1 drivers are archived in the `ros1_archive/` directory for reference purposes.

### Archived Drivers
- **MV-CH120-10GC**: Archived MV camera driver and SDK

## Usage

### Building
The ROS2 workspace is built from the main repository root:
```bash
cd /home/pi/navinet_locmap
colcon build
```

### Launching
Launch individual drivers or the complete system:
```bash
# Individual driver
ros2 launch mid360_driver mid360.launch.py

# Complete system
ros2 launch navinet_locmap_launch all_sensors.launch.py
```

## Migration Notes

### From ROS1 to ROS2
- Hesai32M2X → Mid360 LiDAR
- WIT IMU → STM32 sync board
- Hikrobot camera → New Hikvision camera
- MV-CH120-10GC → Third-party camera

### Preserved for Reference
- Original Hikrobot camera driver (may be useful for new Hikvision driver development)
- MV camera SDK and documentation
- Calibration results and tools

## Development

When developing new drivers or modifying existing ones:

1. **Edit files in**: `SmartScanner/deviceDrivers/src/[driver_name]/`
2. **Build from**: `/home/pi/navinet_locmap/` (main workspace root)
3. **Test with**: Individual launch files or complete system launch

The symlink structure allows for:
- Clean separation of device drivers from core algorithms
- Easy building with standard ROS2 colcon workflow
- Preservation of legacy drivers for reference
- Modular development and testing
