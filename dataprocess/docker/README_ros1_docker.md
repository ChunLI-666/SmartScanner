<!-- TOC tocDepth:2..3 chapterDepth:2..6 -->

- [1. On host](#1-on-host)
  - [1.1. Install docker](#11-install-docker)
  - [1.2. Enable CUDA in docker](#12-enable-cuda-in-docker)
  - [1.3. get ROS2 images](#13-get-ros2-images)
  - [1.4. run ROS2 images](#14-run-ros2-images)
- [2. Inside docker image](#2-inside-docker-image)
  - [2.1. basic setup](#21-basic-setup)
  - [2.2. CUDA & pytorch setup](#22-cuda-pytorch-setup)
  - [2.3. Intel RealSense Driver setup](#23-intel-realsense-driver-setup)
  - [2.4. mmdetection & mmpose setup](#24-mmdetection-mmpose-setup)

<!-- /TOC -->
# Docker Setup

## 1. On host

### 1.1. Install docker

In BOSCH, follow: https://inside-docupedia.bosch.com/confluence/pages/viewpage.action?pageId=2055829490#Howtousedocker@BOSCH-Linux(Ubuntu)

Outside BOSCH, follow: https://docs.docker.com/engine/install/


### 1.2. Enable CUDA in docker

Follow: https://docs.nvidia.com/datacenter/cloud-native/container-toolkit/latest/install-guide.html

```bash
# on host, install
curl -fsSL https://nvidia.github.io/libnvidia-container/gpgkey | sudo gpg --dearmor -o /usr/share/keyrings/nvidia-container-toolkit-keyring.gpg \
  && curl -s -L https://nvidia.github.io/libnvidia-container/stable/deb/nvidia-container-toolkit.list | \
    sed 's#deb https://#deb [signed-by=/usr/share/keyrings/nvidia-container-toolkit-keyring.gpg] https://#g' | \
    sudo tee /etc/apt/sources.list.d/nvidia-container-toolkit.list \
  && \
    sudo apt-get update
sudo apt-get install -y nvidia-container-toolkit

# configure
sudo nvidia-ctk runtime configure --runtime=docker
cat /etc/docker/daemon.json # double check
sudo systemctl restart docker
```

### 1.3. get ROS1 images

```bash
docker pull osrf/ros:noetic-desktop-full
```

### 1.4. run ROS1 images

```bash
# needed for X11 forward
xhost +local:docker

# start ros2 container
docker run -it \
    --workdir=/sandbox/ \
    -v $HOME:/sandbox/ \
    -e HOME=/root/ \
    -e "QT_X11_NO_MITSHM=1" \
    -e GDK_SCALE \
    -e GDK_DPI_SCALE \
    -e DISPLAY=unix$DISPLAY \
    --env="DISPLAY" \
    -v /tmp/.X11-unix:/tmp/.X11-unix \
    --name=ros1-fastlio \
    --privileged \
    --network host \
    -v /etc/timezone:/etc/timezone:ro \
    -v /etc/localtime:/etc/localtime:ro \
    -d ros1:slam

# attach to ros2 container
docker attach ros1
```

## 2. Inside docker image


### 2.1. basic setup
```bash
# (for bosch PC only) setup proxy (put them in .bashrc or .zshrc)
export http_proxy=http://localhost:3128
export https_proxy=http://localhost:3128
export ftp_proxy=http://localhost:3128

# test X11 forwarding
rviz


# install some tools, `-E` for proxy envs
sudo -E apt update
sudo -E apt install -y tmux zsh git vim make cmake tree aptitude \
                       htop curl rsync software-properties-common \
                       locales mlocate aria2 python3-pip
```

### 2.2. CUDA & pytorch setup

```bash
# Download
aria2c https://developer.download.nvidia.com/compute/cuda/11.8.0/local_installers/cuda_11.8.0_520.61.05_linux.run
aria2c https://download.pytorch.org/whl/cu118/torch-2.1.0%2Bcu118-cp310-cp310-linux_x86_64.whl
aria2c https://download.pytorch.org/whl/cu118/torchvision-0.16.0%2Bcu118-cp310-cp310-linux_x86_64.whl

# install CUDA to /usr/local/cuda-11.8
# !!! don't install driver, only select the cuda lib
bash cuda_11.8.0_520.61.05_linux.run

# add the following lines to .bashrc or .zshrc
export CUDA_ROOT=/usr/local/cuda-11.8
export PATH=/usr/local/cuda-11.8/bin:$PATH
export LD_LIBRARY_PATH=/usr/local/cuda-11.8/lib64:$LD_LIBRARY_PATH
export CUDA_INSTALL_DIR=/usr/local/cuda-11.8
export LD_LIBRARY_PATH=/opt/cudnn-linux-x86_64-8.9.3.28_cuda11-archive/lib:$LD_LIBRARY_PATH
export CUDNN_INSTALL_DIR=/opt/cudnn-linux-x86_64-8.9.3.28_cuda11-archive
export CUDNN_ROOT_DIR=$CUDNN_INSTALL_DIR


# install torch
pip3 install torch-2.1.0+cu118-cp310-cp310-linux_x86_64.whl
pip3 install torchvision-0.16.0+cu118-cp310-cp310-linux_x86_64.whl
```


### 2.3. Intel RealSense Driver setup

Please follow [github/realsense-ros](https://github.com/IntelRealSense/realsense-ros#installation)

```bash
# install
sudo apt install ros-humble-librealsense2*
sudo apt install ros-humble-realsense2-*

# launch
ros2 launch realsense2_camera rs_launch.py
ros2 launch realsense2_camera rs_launch.py depth_module.profile:=1280x720x30 pointcloud.enable:=true
```


### 2.4. mmdetection & mmpose setup

```bash
pip3 install matplotlib numpy scipy ipdb opencv ipython
pip3 install -U openmim
mim install mmengine
mim install mmcv
mim install mmpose
mim install mmdet
```