# Fleet-RL ROS 2 Development Environment

## Quick Start with VS Code Dev Containers

1. **Open in VS Code**: Open this repository in VS Code
2. **Reopen in Container**: Press `Ctrl+Shift+P` → "Dev Containers: Reopen in Container"
3. **Wait for Build**: First time will take ~10-15 minutes to build the container
4. **Start Developing**: You're ready with full ROS 2 Humble environment!

## What's Included

### 🤖 ROS 2 Humble Desktop
- Full ROS 2 Humble installation
- Gazebo simulation environment
- Navigation2 stack
- TurtleBot3 packages
- RViz2 visualization

### 🐍 Python ML Stack
- PyTorch for deep learning
- Gymnasium for RL environments
- Stable-Baselines3 for RL algorithms
- NumPy, SciPy, Matplotlib

### 🛠️ Development Tools
- colcon build system
- rosdep dependency management
- VS Code C++ and Python extensions
- Git, CMake, and debugging tools

### 🔌 Pre-configured Ports
- `8080`: Web server
- `8888`: Jupyter notebooks
- `11311`: ROS Master
- `11345`: ROS Bridge

## Building Your ROS 2 Workspace

```bash
# Inside the container
cd /workspace
mkdir -p src

# Clone your ROS packages
cd src
git clone <your-ros-package>

# Install dependencies
cd /workspace
rosdep install --from-paths src --ignore-src -r -y

# Build with colcon
colcon build

# Source the workspace
source install/setup.bash
```

## Running Examples

```bash
# Test ROS 2 installation
ros2 run demo_nodes_cpp talker

# In another terminal
ros2 run demo_nodes_py listener

# Launch TurtleBot3 simulation
export TURTLEBOT3_MODEL=waffle
ros2 launch turtlebot3_gazebo empty_world.launch.py
```

## Fleet-RL Development

This environment is specifically configured for:
- Reinforcement Learning with ROS 2
- Multi-robot fleet coordination
- Simulation-to-real transfer
- Advanced robotics research

Start building your autonomous fleet! 🚀
