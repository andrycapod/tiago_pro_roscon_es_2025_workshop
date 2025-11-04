# 🧍 Using ROS4HRI Tools to Detect and Visualize Bodies

In this exercise, we will learn how to **detect human bodies using ROS4HRI tools** and **visualize them in RViz**.

---

## 1. Setup Inside the Docker Container

We’ll begin by setting up the required packages and configurations inside the provided Docker environment.

### Clone Required Repositories

We need two repositories:

* [`hri_body_detect`](https://github.com/ros4hri/hri_body_detect/tree/humble-devel): provides a MediaPipe-based ROS 2 node performing 2D and 3D body detection.
* [`human_description`](https://github.com/ros4hri/human_description): provides the standard ROS4HRI kinematic model for humans.

```bash
$ cd $HOME/exchange/src
$ git clone https://github.com/ros4hri/hri_body_detect.git --branch 3.1.5
$ git clone https://github.com/ros4hri/human_description.git
```

---

### Copy the Camera Configuration File

Inside the exercise folder, you will find a mock-up configuration file for a camera.
This file is required for **3D body pose detection**, as the node estimates the distance of each body from the camera using its intrinsics.

```bash
$ cp <this_file_folder>/config/camera_info.yaml $HOME/exchange/config
```

---

### Access the Docker Container

If you already have a running instance of the Docker container for this workshop, access it in interactive mode:

```bash
$ docker exec -itu user:user <container_name> bash
```

Otherwise, launch and access a new instance using the [`pal_docker_utils`](https://github.com/pal-robotics/pal_docker_utils) script:

```bash
$ ./pal_docker.sh -it gitlab.pal-robotics.com:4567/ci/repo/roscon-es-2025/humble-public:aca-roscon-es-25-humble
```

---

### Install Required Python Packages

While it’s generally best to install ROS dependencies via `apt`, in this case we’ll use `pip`, since some dependencies are only available there.

```bash
$ pip install mediapipe==0.10.9
$ pip install ikpy==3.3.4
$ pip install lap
$ pip uninstall numpy
```

> The last command removes the pip-installed `numpy` version to avoid conflicts with the system-level installation.

---

### Install the RViz Plugin

We’ll use a dedicated plugin to visualize ROS4HRI information in RViz.

```bash
$ sudo apt install ros-humble-hri-rviz
```

---

## 2. Build the Workspace

Once everything is installed, build your ROS workspace:

```bash
$ cd $HOME/exchange
$ colcon build
```

---

## 3. Launch the Body Detector

Source the workspace and start the body detector node:

```bash
$ source $HOME/exchange/install/setup.bash
$ ros2 launch hri_body_detect hri_body_detect.launch.py
```

---

## 4. Start the Camera Stream

Open another terminal, access the container in interactive mode, and launch `gscam` to publish the camera stream and info topics:

```bash
ros2 run gscam gscam_node --ros-args \
  -p gscam_config:='v4l2src device=/dev/video0 ! video/x-raw,framerate=30/1 ! videoconvert' \
  -p use_sensor_data_qos:=True \
  -p camera_name:=camera \
  -p frame_id:=camera \
  -p camera_info_url:=file:///home/user/exchange/config/camera_info.yaml \
  -r /camera/image_raw:=/image \
  -r /camera/camera_info:=/camera_info
```

---

## 5. Visualize in RViz

Open another terminal, access the container in interactive mode, and start RViz.

Among the available display plugins, you will find **three `hri_rviz` plugins**:

### 🧍 `Humans`

* Visualizes **2D information**, such as 2D skeletons and facial keypoints, overlaid on the camera stream.
* Set the topic to `/image` to display the 2D pose detections from the `hri_body_detect` node.

### 🦴 `Skeletons3D`

* Visualizes **3D pose estimations** for the detected bodies.
* Set the reference frame to `camera` for correct visualization.

### 🌐 `TF (HRI)`

* Displays **human-related TF frames** while filtering out all other frames.

---

✅ **You’re now ready to detect, track, and visualize human bodies with ROS4HRI!**