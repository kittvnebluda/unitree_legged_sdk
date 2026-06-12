# Unitree SDK v3.8.6 --- Go1

This SDK is mainly used for communication between PC and Go1 controller board.
It also can be used in other PCs with UDP.

## Notice

Supported robot: Go1.

For other robots check other branches.

## Sport Mode

| Component       | Min version |
|-----------------|-------------|
| Legged_sport    | v1.36.0     |
| firmware H0.1.7 | v0.1.35     |
| firmware H0.1.9 | v0.1.35     |

Firmware is available at [Unitree](https://www.unitree.com/download).

## Dependencies

* [Boost](http://www.boost.org) (version 1.5.4 or higher)
* [CMake](http://www.cmake.org) (version 2.8.3 or higher)
* [g++](https://gcc.gnu.org/) (version 8.3.0 or higher)
* [pybind11](https://pybind11.readthedocs.io/en/stable/)

If can not find msgpack.hpp, then

```bash
sudo apt install libmsgpack*
```

## Build

```bash
mkdir build && cd build
cmake ../
make
```

## Run

### Cpp

Run examples with 'sudo' for memory locking.

### Python

#### ARM

Change `sys.path.append('../lib/python/amd64')` to `sys.path.append('../lib/python/arm64')`
