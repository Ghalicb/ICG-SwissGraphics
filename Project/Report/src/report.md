---
title: Improved Ray Tracer with Path Tracing (Group 21)
---

![Fig. 1](../res/images/test.png){width="300px"}
![Fig. 2](../res/images/test.png){width="300px"}
![Fig. 3](../res/images/test.png){width="300px"}

# Request
We would like to know if you could give us a few points for the implementation of the Cuboid class as well as for the Cornell Box description as these were not mentionned in the proposal.

# Goal
## Core (4.0):
- Basic path tracing with explicit shadow rays at each surface interaction (implemented)
- Diffuse surfaces (implemented)
- Rectangular area lights (implemented)
- Mirrors (implemented)

## Extensions (+1 each):
- Fractals
- Depth of field
- Glossy/blurry reflections, multiple possible outgoing rays based on surface roughness
- Refractions (implemented)
- Special light sources. E.g. spotlights

# Schedule for the next weeks
- Debug
- Improve Cuboid, AreaLight and overall path tracing stuff
- implement one more extension

# Build Project
- Go to `Improved-Ray-Tracer/`
- `mkdir build`
- `cd build`
- `cmake ..`
- `make -j`
- `cd ..`
- Ray trace our Cornell Box : `./build/raytrace ./scenes/cornell_box/cornell_box.sce ./results/cornell_box.png`

# Cuboid
We implemented the class Cuboid, which is described by its center, {x, y, z}_size, rotation_angle around the y_axis and material. The faces of this object are planes. We intersect the ray with the Plane associated with the corresponding face to compute intersections and we restrict them to be on the faces computing the the dot product of the face_center_to_intersection_vector with the {x, y, z}_axis. In order to speed up the computations, we came up with the following tricks :

- We keep track of the number of possible intersections so that we do not necessarly need to iterate over all the faces if the already have computed two intersections.
- We evaluate the norm of face_center_to_intersection_vector and compare it with the norm of (x_size/2,y_size/2,z_size/2), which is the biggest value face_center_to_intersection_vector could have when intersection_point is on a face, before starting any heavy computations (circumscribed sphere).

# Cornell Box
We described a Cornell Box scene (/Improved-Ray-Tracer/scenes/cornell_box/). It is composed of five walls, one light, one cuboid and one sphere. It has 800x800x800 dimensions, the origin (0,0,0) is at the center of the box and the camera located at (0, 0, 600) is looking at the origin with a field of view of 90 degrees. The x-axis is pointing the the right-hand side of the image, the y-axis is pointing up and the z-axis is pointing to the camera.

# AreaLight
This describes a rectangular light, which is discretized into blocks of a a given side length. When checking the lighting during the ray tracing, we iterate over all the contained lights of each AreaLight. This will be improved so that we can give an orientation, a direction and an aperture to it. Moreover, we will take a probabilistic approach to check the lighting at a random point inside a block instead of always checking at the center of the blocks. These improvements will allow us to use AreaLight as a simple light as well as for more specific lights like spotlights.

# Path Tracing
## Path tracing with explicit shadow rays
To do this, we trace a ray for each pixel and when it intersects an object, we choose randomly (according to material properties : mirror, transparency) between diffuse, mirror or refractive behavior. If the surface is
1. diffuse, we compute direct lightning by tracing a ray to each light source, if the light source is visible, we add to the color contribution the material color times the light color times the dot product between object's normal and point-to-light vector (Monte-Carlo integration). Then we randomly choose a vector and trace a ray in this direction and add the obtained color to the color contribution.
2. mirror, we compute the reflect vector and trace it, the color obtained is the color contribution.
3. refractive, we compute the refracted vector (that goes inside the object using the refractive index described in material) and trace it. The contribution is the obtained color. The refractive index is the real one.
The trace method is recursive and we defined a maximum bounces number to not infinitly loop.

We trace a certain number (~1000 to ~10000) of this path per pixel and its final color is the average of every results.

## Path tracing without shadow rays
We began to implement the second technique to have caustics. This technique is the same as the first one but without the explicit shadow rays. That produces beautiful images but is extremly costly to compute because only rays that finally hit the light source are contributing to the final color. We will see if we keep this implementation or not. We will probably keep both.

# Plane
!!! These modifications have been implemented but we discarded them !!!

We modified the provided Plane class in order to support two new functionalities :

- A plane cat be cut, it can have a hole around center of a given hole_radius
- A plane is not necessarly infinite, it can be bounded by a circle of a given outer_radius. This implied the function intersect to be updated (circumscribed circle).
