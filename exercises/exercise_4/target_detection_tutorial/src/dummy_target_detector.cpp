// Copyright (c) 2024 PAL Robotics S.L. All rights reserved.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//
// Author: Martina Annicelli

/**
 * @file dummy_target_detector.cpp
 * @brief Example implementation of a simple TargetDetector plugin for PAL Navigation2.
 *
 * This file defines the DummyTargetDetector class, which implements the
 * `pal_nav2_core::TargetDetector` interface. It is a minimal example used
 * for tutorials and testing, demonstrating how to write and register a
 * custom target detection plugin.
 *
 * ## Overview
 *
 * This class provides the following virtual methods that must be implemented
 * by any TargetDetector plugin:
 *
 * | Virtual Method | Description | Requires override? |
 * |-----------------|-------------|--------------------|
 * | **configure()** | Called when the TargetDetector plugin is initialized. It sets up the plugin name, parent node and TF buffer. | ✅ Yes |
 * | **cleanup()** | Cleans up all defined resources. | ✅ Yes |
 * | **activate()** | Activates the detector and any threads, publishers or subscribers. | ✅ Yes |
 * | **deactivate()** | Deactivates the detector and its components. | ✅ Yes |
 * | **detectTarget()** | Performs the target detection logic. Returns true if a target is found and localized. | ✅ Yes |
 * | **reset()** | Resets the internal state of the detector. Optional to override. | ❌ No |
 *
 * ## Implementation Notes
 *
 * - In `configure()`, you can set up the ROS 2 interface (Subscribers, Publishers, Services, etc.)
 *   using the `parent_` variable, which is a `rclcpp_lifecycle::LifecycleNode::WeakPtr`.
 *   Example:
 *   @code{.cpp}
 *   auto node = parent_.lock();
 *   if (!node) {
 *     throw std::runtime_error{"Failed to lock node in simple target detector plugin!"};
 *   }
 *   @endcode
 *
 * - The `detectTarget()` function implements the real logic of the plugin.
 *   It should generate a `geometry_msgs::msg::TransformStamped` message
 *   with the pose of the detected target and an accuracy score.
 *   In this tutorial example, the target is simply hardcoded to be
 *   2 meters in front of the robot.
 *
 * @ingroup target_detection_tutorial
 */

#include <memory>
#include <string>
#include <unordered_map>
#include <utility>

#include "rclcpp/rclcpp.hpp"
#include "rclcpp/clock.hpp"
#include "rclcpp_lifecycle/lifecycle_node.hpp"
#include "tf2_ros/buffer.h"
#include "pal_nav2_core/target_detector.hpp"
//#include "hri/hri.hpp"

namespace target_detection_tutorial
{

/**
* @class target_detection_tutorial::DummyTargetDetector
* @brief A minimal dummy implementation of a TargetDetector plugin.
*
* This detector always returns a single target with ID 0 located 2 meters
* in front of the robot's base frame. It demonstrates the structure of a
* `pal_nav2_core::TargetDetector` implementation.
*/
class DummyTargetDetector : public pal_nav2_core::TargetDetector
{
public:
  DummyTargetDetector() = default;
  ~DummyTargetDetector() = default;

  /**
  * @brief Configure the target detector.
  * @param parent Weak pointer to the lifecycle node that owns this plugin.
  * @param name The name of the plugin instance.
  * @param tf Shared pointer to the tf2 buffer.
  */
  void configure(
    const rclcpp_lifecycle::LifecycleNode::WeakPtr & parent, std::string name,
    std::shared_ptr<tf2_ros::Buffer>) override
  {
    parent_ = parent;
    auto node = parent_.lock();
    if (!node) {
      throw std::runtime_error{"Failed to lock node in simple target detector plugin!"};
    }
    plugin_name_ = name;
    logger_ = node->get_logger();
    clock_ = node->get_clock();

    //hri_listener_ = hri::HRIListener::create(node);
    //hri_listener_->setReferenceFrame("base_footprint");
    //RCLCPP_INFO(logger_, "HRI Listener initialized in %s", plugin_name_.c_str());
  }

  /**
  * @brief Clean up the plugin resources.
  */
  void cleanup() override
  {
    RCLCPP_INFO(logger_, "Cleaning up %s target detector", plugin_name_.c_str());
  }

  /**
  * @brief Activate the detector and any relevant ROS entities.
  */
  void activate() override
  {
    RCLCPP_INFO(logger_, "Activating %s target detector", plugin_name_.c_str());
  }

  /**
  * @brief Deactivate the detector.
  */
  void deactivate() override
  {
    RCLCPP_INFO(logger_, "Deactivating %s target detector", plugin_name_.c_str());
  }

  /**
  * @brief Perform target detection.
  * @param requested_ids List of target IDs to detect (only one ID is supported in this example).
  * @param detected_targets Output map of detected targets and their transforms with accuracy.
  * @return True if the target was found, false otherwise.
  */
  bool detectTarget(
    const std::vector<int> & requested_ids,
    std::unordered_map<int, std::pair<geometry_msgs::msg::TransformStamped,
    double>> & detected_targets) override
  {
    if (requested_ids.size() != 1) {
      RCLCPP_ERROR(logger_, "request precisely one id!");
      return false;
    }

    int id = requested_ids.at(0);
    if (id != 0) {
      RCLCPP_WARN(logger_, "%s: Target not detected", plugin_name_.c_str());
      return false;
    }

    geometry_msgs::msg::TransformStamped transform;
    double accuracy = 0.8;

    // auto bodies = hri_listener_->getBodies();
    // for (auto const & [body_id, body]: bodies)
    // {
    // RCLCPP_DEBUG(logger_, "Body detected = %s", body_id.c_str());


    //   if (auto bodyTransform = body->transform())
    //   {
    //     geometry_msgs::msg::TransformStamped transform_stamped;
    //     transform_stamped.header = bodyTransform->header;
    //     transform_stamped.child_frame_id = bodyTransform->child_frame_id;
    //     transform_stamped.transform = bodyTransform->transform;
    
    //     RCLCPP_DEBUG(logger_, "Body %s translation: [%.2f, %.2f, %.2f]",
    //                 body_id.c_str(),
    //                 transform_stamped.transform.translation.x,
    //                 transform_stamped.transform.translation.y,
    //                 transform_stamped.transform.translation.z);
    
    //     detected_targets[id] = std::make_pair(transform_stamped, accuracy);
    //     return true;
    //   }
    // }
    // RCLCPP_WARN(logger_, "%s: No body transform available", plugin_name_.c_str());
    // return false;

    transform.header.frame_id = "base_footprint";
    transform.child_frame_id = "target";
    transform.header.stamp = clock_->now();
    transform.transform.translation.x = 2.0;
    detected_targets[id] = std::make_pair(transform, accuracy);
    return true;
  }

  /**
  * @brief Check if the detection time is valid (always true in this example).
  */
  bool isValidTime(const rclcpp::Duration &) override
  {
    return true;
  }

private:
  rclcpp::Logger logger_{rclcpp::get_logger("dummy_target_detector")};
  rclcpp_lifecycle::LifecycleNode::WeakPtr parent_;
  rclcpp::Clock::SharedPtr clock_;
  std::string plugin_name_;

  //std::shared_ptr<hri::HRIListener> hri_listener_;
  //std::vector<hri::ID> bodies_facing_robot_;
};

}  // namespace target_detection_tutorial

#include "pluginlib/class_list_macros.hpp"
PLUGINLIB_EXPORT_CLASS(
  target_detection_tutorial::DummyTargetDetector,
  pal_nav2_core::TargetDetector)
 
