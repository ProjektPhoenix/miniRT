# The "miniRT" project
miniRT is a simple raytracer project which we implemented as part of the 42 core curriculum. The program reads configuration information from a file and displays a corresponding image using raytracing techniques. The program is written in C.

## Background: raytracing

## Project objectives

## Allowed functions
As in most 42 projects we were restricted in the functions and libraries we were allowed to use for the project. Allowed functions for this project were:

- The basic system functions `open()`, `close()`, `read()`, `write()`, `printf()`, `malloc()`, `free()`, `perror()`, `strerror()`, `exit()`
- All functions of the math library (-lm man man 3 math)
- All functions of the minilibX-library, which is a simple window management library supplied by 42
- Additionally we were allowed to use all previous functions that we had written for previous projects (our "libft"). These functions are mainly built on the basic functions listed above.

## Configuration file / scene description
The configuration of the scene is provided in a simple text file, which contains key information on the objects to be displayed, lighting conditions, etc.

Specifically, each text file can or must contain:
- description of ambient lighting, which is indicated by an "A" in the text file. It essentially describes the share / ratio of ambient lighting and its RGB color in the following format: `A 0.2 255,255,255`
- description of the camera / viewpoint, which is indiated by a "C" and contains information on its location in space, the direction it is pointed in (a normalized orientation vector) and the angle visible from that viewpoint: `C -50.0,0,20 0,0,1 70`
- description of a direct light source, which is indicated by an "L" and contains information on its location in space and an indicator for the "light brightness ratio". For the bonus part of the project the light source may optionally have a specific RGB color. The format is hence defined as `L -40.0,50.0,0.0 0.6` in the basic implementation and `L -40.0,50.0,0.0 0.6 10,0,255` for the bonus implementation.
- description of objects, which can all appear multiple times in a scene (unlike the previous elements)
	- sphere
	- plane
	- cylinder

## Our architecture

## Issues encountered in implementation
