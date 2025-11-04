#!/bin/bash

# Copyright (c) 2025 PAL Robotics S.L. All rights reserved.
#
#  Redistribution and use in source and binary forms, with or without
#  modification, are permitted provided that the following conditions are met:
#
#  1. Redistributions of source code must retain the above copyright notice,
#     this list of conditions and the following disclaimer.
#  2. Redistributions in binary form must reproduce the above copyright notice,
#     this list of conditions and the following disclaimer in the documentation
#     and/or other materials provided with the distribution.
#  3. Neither the name of the copyright holder nor the names of its
#     contributors may be used to endorse or promote products derived from this
#     software without specific prior written permission.
#
#  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS
#  IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED
#  TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A
#  PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
#  HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
#  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
#  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
#  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
#  THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
#  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
#  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

# Destination folder
WORKSPACE_DIR="$HOME/exchange/ws_tiago_pro_workshop/src"

# Create folder if it doesn't exist
mkdir -p "$WORKSPACE_DIR"
cd "$WORKSPACE_DIR" || exit

# List of repositories to clone from PAL Robotics
REPOS=(
    "pal_docker_utils"
    "pal_gazebo_worlds"
    "omni_base_navigation"
)

# Base GitHub URL for PAL Robotics
BASE_URL="https://github.com/pal-robotics"

# Clone repositories from PAL Robotics
for repo in "${REPOS[@]}"; do
    if [ -d "$repo" ]; then
        echo "Repository $repo already exists, skipping."
    else
        echo "Cloning repository $repo..."
        git clone "$BASE_URL/$repo.git"
    fi
done

# Clone additional package from different repo
EXTRA_REPO_URL="https://github.com/LorenzoFerriniCodes/pal_gazebo_plugins.git"
EXTRA_REPO_NAME="pal_gazebo_plugins"

if [ -d "$EXTRA_REPO_NAME" ]; then
    echo "Repository $EXTRA_REPO_NAME already exists, skipping."
else
    echo "Cloning extra repository $EXTRA_REPO_NAME from $EXTRA_REPO_URL..."
    git clone "$EXTRA_REPO_URL"
fi

echo
echo "Installing at $WORKSPACE_DIR"
echo
echo "============================================================"
echo "  All repositories for TIAGo PRO Navigation and HRI workshop"
echo "  have been successfully cloned!"
echo "============================================================"
echo
