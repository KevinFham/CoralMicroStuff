#!/bin/bash

# Install the required packages for the Coral Micro

set -e

readonly SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
readonly OS="$(uname -s)"

function error {
  echo -e "\033[0;31m${1}\033[0m"  # red
}

if [[ "${OS}" == "Linux" ]]; then
  sudo apt-get update && sudo apt-get -y install \
    make \
    cmake \
    libhidapi-hidraw0 \
    libusb-1.0-0-dev \
    libudev-dev \
    python3-dev \
    python3-pip

  if [[ -x "$(command -v udevadm)" ]]; then
    sudo cp "${SCRIPT_DIR}/scripts/99-coral-micro.rules" /etc/udev/rules.d/
    sudo udevadm control --reload-rules
    sudo udevadm trigger
  fi
else
  error "Your operating system is not supported."
  exit 1
fi

python3 -m pip install pip --upgrade
python3 -m pip install -r "${SCRIPT_DIR}/scripts/requirements.txt"
