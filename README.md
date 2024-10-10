# CoralMicroStuff

Custom libraries for using onnx on the Coral Micro


## Installing

#### Coral Micro Docs

[Getting Started](https://coral.ai/docs/dev-board-micro/arduino/)

[Arduino API](https://coral.ai/docs/reference/micro/arduino/)


#### Requirements

- Python 3.9.x
- Python Environment (`conda`, `venv`, etc.)

#### Installation

Run `bash setup.sh`

TODO:



## Issues

#### When Coral Micro cannot be found on `lsusb`

https://coral.ai/docs/dev-board-micro/arduino/#troubleshooting


## To Do

- [X] Setup script
- [ ] Build script
    - [ ] Pull relevant coral libs
    - [ ] Pull relevant third party libraries
    - [ ] Modify CMake scripts
    - [ ] Attempt to avoid using FreeRTOS (we want direct upload to usage pipeline)
- [ ] Create test cases with pre build models and test data
- [ ] Docker container?



