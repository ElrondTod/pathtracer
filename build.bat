@echo off

cls

g++ -Wall -Wextra -I header src\vector.cpp src\material.cpp src\object.cpp src\camera.cpp src\math.cpp src\writer.cpp src\triangle.cpp src\renderer.cpp src\scene.cpp src\main.cpp