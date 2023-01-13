# DancingDataTable
 
Joah Robak
 
## Overview

This is a renderer written in C++ using OpenGL API. It was created for the EWU Student Research & Creative Works Symposium 2020. It was created to explore how 3D data representation could be combined with nature to produce a unique way of representing data. The project shows fields of grass presenting data from .csv files.


## Requirements
- Visual Studio 2022
- OpenGL 4.3+


## Installation
1. git clone https://github.com/CerealThread/DancingDataTable.git
2. Open Visual Studio project file using Visual Studio
3. Build and run using Visual Studio as Debug x64

## Usage
There are three data sets that can be cycled between by pressing the "a" key. Additionally, the right arrow key can be used to cycle through several camera angles of the same data set. The escape key will terminate the program.


## Included Libraries
This project contains the following libraries
- FastNoiseLite
- freeglut
- glew
- glfw3
- glm

## Attributions

Some sections of code are modified from Packt, as well as some from Joey de Vries (https://twitter.com/JoeyDeVriez) from https://learnopengl.com/

Mathmatical functions for determining signed distance functions for the object primitives were based on [Inigo Quilez's](https://iquilezles.org/) functions, found [here](https://iquilezles.org/articles/distfunctions/).
