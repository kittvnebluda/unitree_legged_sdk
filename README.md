# Unitree SDK v3.8.4 --- Aliengo

This SDK is mainly used for communication between PC and aliengo control board.
It also can be used in other PCs with UDP.

## Notice

Supported robot: Aliengo.

For other robots check other branches.

## Sport Mode

  | Component       | Min version |
  |-----------------|-------------|
  | Legged_sport    | v1.0.20     |
  | firmware H0.1.7 | v0.1.35     |
  | firmware H0.1.9 | v0.1.35     |

## Dependencies

* [Boost](http://www.boost.org) (version 1.5.4 or higher)
* [CMake](http://www.cmake.org) (version 2.8.3 or higher)
* [LCM](https://lcm-proj.github.io) (version 1.4.0 or higher)
* [pybind11](https://pybind11.readthedocs.io/en/stable/)

LCM must be built from source (apt version is too old): see LCM build
instructions (<https://lcm-proj.github.io/lcm/content/build-instructions.html>)

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
