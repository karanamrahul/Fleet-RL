# Fleet-RL ROS 2 Humble Development Container
FROM ubuntu:22.04

# Prevent interactive prompts during package installation
ENV DEBIAN_FRONTEND=noninteractive
ENV TZ=UTC

# Set locale
RUN apt-get update && apt-get install -y locales && \
    locale-gen en_US en_US.UTF-8 && \
    update-locale LC_ALL=en_US.UTF-8 LANG=en_US.UTF-8
ENV LANG=en_US.UTF-8

# Install system dependencies
RUN apt-get update && apt-get install -y \
    curl \
    gnupg2 \
    lsb-release \
    software-properties-common \
    build-essential \
    cmake \
    git \
    python3-pip \
    python3-dev \
    python3-setuptools \
    python3-wheel \
    python3-colcon-common-extensions \
    python3-rosdep \
    python3-vcstool \
    wget \
    && rm -rf /var/lib/apt/lists/*

# Add ROS 2 apt repository
RUN curl -sSL https://raw.githubusercontent.com/ros/rosdistro/master/ros.key -o /usr/share/keyrings/ros-archive-keyring.gpg && \
    echo "deb [arch=$(dpkg --print-architecture) signed-by=/usr/share/keyrings/ros-archive-keyring.gpg] http://packages.ros.org/ros2/ubuntu $(. /etc/os-release && echo $UBUNTU_CODENAME) main" | tee /etc/apt/sources.list.d/ros2.list > /dev/null

# Install ROS 2 Humble
RUN apt-get update && apt-get install -y \
    ros-humble-desktop \
    ros-humble-rmw-fastrtps-cpp \
    ros-humble-rmw-cyclonedx-cpp \
    && rm -rf /var/lib/apt/lists/*

# Install additional ROS 2 development tools
RUN apt-get update && apt-get install -y \
    ros-humble-gazebo-* \
    ros-humble-navigation2 \
    ros-humble-nav2-bringup \
    ros-humble-turtlebot3* \
    ros-humble-robot-localization \
    ros-humble-plotjuggler-ros \
    && rm -rf /var/lib/apt/lists/*

# Install Python packages for RL and robotics
RUN pip3 install \
    numpy \
    matplotlib \
    scipy \
    torch \
    torchvision \
    torchaudio \
    gymnasium \
    stable-baselines3 \
    rospkg \
    catkin_pkg

# Initialize rosdep
RUN rosdep init || true
RUN rosdep update

# Create workspace directory
RUN mkdir -p /workspace/src

# Set up environment
RUN echo "source /opt/ros/humble/setup.bash" >> /root/.bashrc
RUN echo "source /workspace/install/setup.bash || true" >> /root/.bashrc
RUN echo "export ROS_DOMAIN_ID=30" >> /root/.bashrc

# Set working directory
WORKDIR /workspace

# Default command
CMD ["/bin/bash"]
