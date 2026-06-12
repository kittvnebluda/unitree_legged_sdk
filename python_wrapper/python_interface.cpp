/**********************************************************************
 Copyright (c) 2020-2023, Unitree Robotics.Co.Ltd. All rights reserved.
***********************************************************************/

#include "unitree_legged_sdk/unitree_legged_sdk.h"
#include <math.h>
#include <pybind11/operators.h>
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <unistd.h>

using namespace UNITREE_LEGGED_SDK;

namespace py = pybind11;

PYBIND11_MODULE(robot_interface, m) {
    py::enum_<LeggedType>(m, "LeggedType")
        .value("Aliengo", LeggedType::Aliengo)
        .value("A1", LeggedType::A1)
        .export_values();

    py::enum_<HighLevelType>(m, "HighLevelType")
        .value("Basic", HighLevelType::Basic)
        .value("Sport", HighLevelType::Sport)
        .export_values();

    py::class_<UDP>(m, "UDP")
        .def(py::init<uint8_t, HighLevelType>(), py::arg("level"), py::arg("highControl") = HighLevelType::Basic)
        .def(py::init<uint16_t, const char *, uint16_t, int, int, int>(), py::arg("localPort"), py::arg("targetIP"),
             py::arg("targetPort"), py::arg("sendLength"), py::arg("recvLength"), py::arg("useTimeOut") = -1)
        .def(py::init<uint16_t, int, int, bool>(), py::arg("localPort"), py::arg("sendLength"), py::arg("recvLength"),
             py::arg("isServer") = false)
        .def("Send", &UDP::Send)
        .def("Recv", &UDP::Recv)
        .def("InitCmdData", py::overload_cast<HighCmd &>(&UDP::InitCmdData))
        .def("InitCmdData", py::overload_cast<LowCmd &>(&UDP::InitCmdData))
        .def("SetSend", py::overload_cast<char *>(&UDP::SetSend))
        .def("SetSend", py::overload_cast<HighCmd &>(&UDP::SetSend))
        .def("SetSend", py::overload_cast<LowCmd &>(&UDP::SetSend))
        .def("GetRecv", py::overload_cast<char *>(&UDP::GetRecv))
        .def("GetRecv", py::overload_cast<HighState &>(&UDP::GetRecv))
        .def("GetRecv", py::overload_cast<LowState &>(&UDP::GetRecv));

    py::class_<Safety>(m, "Safety")
        .def(py::init<LeggedType>())
        .def("PositionLimit", &Safety::PositionLimit)
        .def("PowerProtect", &Safety::PowerProtect)
        .def("PositionProtect", &Safety::PositionProtect);

    py::class_<Cartesian>(m, "Cartesian")
        .def(py::init<>())
        .def_readwrite("x", &Cartesian::x)
        .def_readwrite("y", &Cartesian::y)
        .def_readwrite("z", &Cartesian::z);

    py::class_<IMU>(m, "IMU")
        .def(py::init<>())
        .def_readwrite("quaternion", &IMU::quaternion)
        .def_readwrite("gyroscope", &IMU::gyroscope)
        .def_readwrite("accelerometer", &IMU::accelerometer)
        .def_readwrite("rpy", &IMU::rpy)
        .def_readwrite("temperature", &IMU::temperature);

    py::class_<LED>(m, "LED")
        .def(py::init<>())
        .def_readwrite("r", &LED::r)
        .def_readwrite("g", &LED::g)
        .def_readwrite("b", &LED::b);

    py::class_<MotorState>(m, "MotorState")
        .def(py::init<>())
        .def_readwrite("mode", &MotorState::mode)
        .def_readwrite("q", &MotorState::q)
        .def_readwrite("dq", &MotorState::dq)
        .def_readwrite("ddq", &MotorState::ddq)
        .def_readwrite("tauEst", &MotorState::tauEst)
        .def_readwrite("q_raw", &MotorState::q_raw)
        .def_readwrite("dq_raw", &MotorState::dq_raw)
        .def_readwrite("ddq_raw", &MotorState::ddq_raw)
        .def_readwrite("temperature", &MotorState::temperature)
        .def_readwrite("reserve", &MotorState::reserve);

    py::class_<MotorCmd>(m, "MotorCmd")
        .def(py::init<>())
        .def_readwrite("mode", &MotorCmd::mode)
        .def_readwrite("q", &MotorCmd::q)
        .def_readwrite("dq", &MotorCmd::dq)
        .def_readwrite("tau", &MotorCmd::tau)
        .def_readwrite("Kp", &MotorCmd::Kp)
        .def_readwrite("Kd", &MotorCmd::Kd)
        .def_readwrite("reserve", &MotorCmd::reserve);

    py::class_<LowState>(m, "LowState")
        .def(py::init<>())
        .def_readwrite("levelFlag", &LowState::levelFlag)
        .def_readwrite("SN", &LowState::SN)
        .def_readwrite("bandWidth", &LowState::bandWidth)
        .def_readwrite("imu", &LowState::imu)
        .def_readwrite("motorState", &LowState::motorState)
        .def_readwrite("footForce", &LowState::footForce)
        .def_readwrite("footForceEst", &LowState::footForceEst)
        .def_readwrite("tick", &LowState::tick)
        .def_readwrite("wirelessRemote", &LowState::wirelessRemote)
        .def_readwrite("reserve", &LowState::reserve)
        .def_readwrite("crc", &LowState::crc);

    py::class_<LowCmd>(m, "LowCmd")
        .def(py::init<>())
        .def_readwrite("levelFlag", &LowCmd::levelFlag)
        .def_readwrite("SN", &LowCmd::SN)
        .def_readwrite("bandWidth", &LowCmd::bandWidth)
        .def_readwrite("motorCmd", &LowCmd::motorCmd)
        .def_readwrite("led", &LowCmd::led)
        .def_readwrite("wirelessRemote", &LowCmd::wirelessRemote)
        .def_readwrite("reserve", &LowCmd::reserve)
        .def_readwrite("crc", &LowCmd::crc);

    py::class_<HighState>(m, "HighState")
        .def(py::init<>())
        .def_readwrite("levelFlag", &HighState::levelFlag)
        .def_readwrite("SN", &HighState::SN)
        .def_readwrite("bandWidth", &HighState::bandWidth)
        .def_readwrite("mode", &HighState::mode)
        .def_readwrite("imu", &HighState::imu)
        .def_readwrite("position", &HighState::position)
        .def_readwrite("velocity", &HighState::velocity)
        .def_readwrite("yawSpeed", &HighState::yawSpeed)
        .def_readwrite("footPosition2Body", &HighState::footPosition2Body)
        .def_readwrite("footSpeed2Body", &HighState::footSpeed2Body)
        .def_readwrite("footForce", &HighState::footForce)
        .def_readwrite("wirelessRemote", &HighState::wirelessRemote)
        .def_readwrite("reserve", &HighState::reserve)
        .def_readwrite("crc", &HighState::crc);

    py::class_<HighCmd>(m, "HighCmd")
        .def(py::init<>())
        .def_readwrite("levelFlag", &HighCmd::levelFlag)
        .def_readwrite("SN", &HighCmd::SN)
        .def_readwrite("bandWidth", &HighCmd::bandWidth)
        .def_readwrite("mode", &HighCmd::mode)
        .def_readwrite("gaitType", &HighCmd::gaitType)
        .def_readwrite("speedLevel", &HighCmd::speedLevel)
        .def_readwrite("dFootRaiseHeight", &HighCmd::dFootRaiseHeight)
        .def_readwrite("dBodyHeight", &HighCmd::dBodyHeight)
        .def_readwrite("position", &HighCmd::position)
        .def_readwrite("rpy", &HighCmd::rpy)
        .def_readwrite("velocity", &HighCmd::velocity)
        .def_readwrite("yawSpeed", &HighCmd::yawSpeed)
        .def_readwrite("led", &HighCmd::led)
        .def_readwrite("wirelessRemote", &HighCmd::wirelessRemote)
        .def_readwrite("reserve", &HighCmd::reserve)
        .def_readwrite("crc", &HighCmd::crc);

    py::class_<UDPState>(m, "UDPState")
        .def(py::init<>())
        .def_readwrite("TotalCount", &UDPState::TotalCount)
        .def_readwrite("SendCount", &UDPState::SendCount)
        .def_readwrite("RecvCount", &UDPState::RecvCount)
        .def_readwrite("SendError", &UDPState::SendError)
        .def_readwrite("FlagError", &UDPState::FlagError)
        .def_readwrite("RecvCRCError", &UDPState::RecvCRCError)
        .def_readwrite("RecvLoseError", &UDPState::RecvLoseError);
}
