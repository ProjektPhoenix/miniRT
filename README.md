# The "miniRT" Project
miniRT is a simple raytracer project which we implemented as a group projects within the 42 core curriculum. At the most general level, the program reads configuration information from a file and displays a corresponding image using raytracing techniques. The program is written in C.

The current implementation allows for the rendering of planes, spheres and cylinders, camera position and angle, one light source, different color configurations (light source, ambient light, object colors, specular lighting). These simple elements already allow for the rendering of complex scenes.

![Preview](rendered_previews/pillars.rt.png)

## What is Raytracing?
Raytracing is a specific form of rendering 3D objects on a 2D display. In contrast to more traditional and common graphics technologies, such as raterization, raytracings is based on physical modelling of light rays and their interaction with objects and colors. Raytracer scenes often look more realistic, albeit being more computationally intensive. However, with modern processors and graphics processing units available, raytracing is more widely employed.

## Core Tasks
The project required us to:
- employ our knowledge of C programming
- organise the project through GitHub and other collaboration tools in a hybrid remote / onsite setting, while working towards a functional product on a defined timeline
- implement a robust parsing logic
- revisit linear algebra and 3D vector math and apply it in a coherent product 
- understanding and using the interface to the systems windows management to go beyond command line implementation that are the focus of many of the other 42 projects so far
- abstract math and underlying technologies to model and visualize 3D scenes
- rigorously test, debug and refine program code to cover all possible configuration files and their inherent characteristics
- define interfaces between the different program components to be able to work on them individually, while ensuring a functional and coherent program overall

## Restrictions
As in most 42 projects we were restricted in the functions and libraries we were allowed to use for the project. Allowed functions for this project were:

- The following basic POSIX system calls and C library functions: `open()`, `close()`, `read()`, `write()`, `printf()`, `malloc()`, `free()`, `perror()`, `strerror()`, `exit()`
- All functions of the math library (-lm man man 3 math)
- All functions of the minilibX-library, which is a simple library interfacing with system window management and supplied by 42
- Additionally we were allowed to use all previous functions that we had written for previous projects (our "libft"). These functions are mainly built on the basic functions listed above.

## Usage
The program should run on most linux and Mac OS systems (though only tested on a few).
After cloning or downloading the repo, the program can be compiled by calling 'make' on the command line in the main directory of the project.
After successful compilation the program can be run by executing './miniRT <configuration_file.rt>' providing a properly formatted scene as 'configuration_file.rt".
Example scenes are included in the 'scenes' directory. You can call them directly through, e.g.:<br>
./miniRT scenes/pillars.rt<br>
./miniRT scenes/marbles.rt<br>
./miniRT scenes/light_behind_plane.rt

## Defining a Proper Configuration File
The configuration of the scene is provided in a simple text file, which contains key information on the objects to be displayed, lighting conditions, etc.

Specifically, each text file can or must contain:
- description of ambient lighting, which is indicated by an "A" in the text file. It essentially describes the share / ratio of ambient lighting and its RGB color in the following format: `A 0.2 255,255,255`
- description of the camera / viewpoint, which is indiated by a "C" and contains information on its location in space, the direction it is pointed in (a normalized orientation vector) and the angle visible from that viewpoint: `C -50.0,0,20 0,0,1 70`
- description of a direct light source, which is indicated by an "L" and contains information on its location in space and an indicator for the "light brightness ratio". For the bonus part of the project the light source may optionally have a specific RGB color. The format is hence defined as `L -40.0,50.0,0.0 0.6` in the basic implementation and `L -40.0,50.0,0.0 0.6 10,0,255` for the bonus implementation.
- description of objects, which can all appear multiple times in a scene (unlike the previous elements)
	- sphere
	- plane
	- cylinder

![Preview](rendered_previews/marbles.rt.png)
