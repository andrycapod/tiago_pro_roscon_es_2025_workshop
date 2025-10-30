#!/usr/bin/env python3

# Copyright (c) 2025 PAL Robotics S.L. All rights reserved.
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#     http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

import os
from launch import LaunchDescription
from launch.actions import EmitEvent, RegisterEventHandler
from launch.events import matches_action
from launch_ros.actions import LifecycleNode
from launch_ros.events.lifecycle import ChangeState
from launch_ros.event_handlers import OnStateTransition
from lifecycle_msgs.msg import Transition
from ament_index_python.packages import get_package_share_directory


def generate_launch_description():
    # Nodes
    ld = LaunchDescription()
    pkg = 'pal_nav2_target_detector'
    name = 'target_detector_server'
    
    pkg_share_dir = get_package_share_directory("target_detection_tutorial")
    params_file = os.path.join(pkg_share_dir, 'params', 'default.yaml')

    target_detector_server_node = LifecycleNode(
        package=pkg,
        executable='target_detector_server',
        name=name,
        namespace='',
        output='screen',
        emulate_tty=True,
        parameters=[params_file],
    )

    # Configure and Activate
    configure_event = EmitEvent(event=ChangeState(
        lifecycle_node_matcher=matches_action(target_detector_server_node),
        transition_id=Transition.TRANSITION_CONFIGURE))

    activate_event = RegisterEventHandler(OnStateTransition(
        target_lifecycle_node=target_detector_server_node, goal_state='inactive',
        entities=[EmitEvent(event=ChangeState(
            lifecycle_node_matcher=matches_action(target_detector_server_node),
            transition_id=Transition.TRANSITION_ACTIVATE))], handle_once=True))

    ld.add_action(target_detector_server_node)
    ld.add_action(configure_event)
    ld.add_action(activate_event)

    return ld
