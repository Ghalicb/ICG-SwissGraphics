---
title: Enhanced Ray Tracer using Path Tracing (Group 21)
---
<video width="900px" src="../res/ICG-Final-Presentation-Video-Group21.mp4" loop autoplay muted></video>

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

# Build Project
- Go to `Improved-Ray-Tracer/`
- `mkdir build`
- `cd build`
- `cmake ..`
- `make -j`
- `cd ..`
- Ray trace our Cornell Box : `./build/raytrace ./scenes/cornell_boxes/cornell_box_{1, 2, 3}.sce ./results/cornell_box_{1, 2, 3}.png`

# Cuboid
We implemented the class Cuboid, which is described by its center, {x, y, z}_size, rotation_angle around the y_axis and material. The faces of this object are planes. We intersect the ray with the Plane associated with the corresponding face to compute intersections and we restrict them to be on the faces computing the the dot product of the face_center_to_intersection_vector with the {x, y, z}_axis. In order to speed up the computations, we came up with the following tricks :

- We keep track of the number of possible intersections so that we do not necessarly need to iterate over all the faces if the already have computed two intersections.
- We evaluate the norm of face_center_to_intersection_vector and compare it with the norm of (x_size/2,y_size/2,z_size/2), which is the biggest value face_center_to_intersection_vector could have when intersection_point is on a face, before starting any heavy computations (circumscribed sphere).

# Path Tracing
## Path tracing with explicit shadow rays (Fig. 1)
We trace rays for each pixel (~1000 to 10000). Each of these rays is independent from others. Here is the procedure for one ray.

When the ray intersects a surface, first we retrieve the material properties of the intersected object, there are then 3 possibilities which will be detailed:
1. Mirror surface: for this one, we trace no shadow rays. The only color returned is the color returned by a recursive ray tracing in the reflected direction with respect the object normal.
2. Transparent objects: first we assume that the ambient material is air whose refraction index is approximated by 1.0. To implement the refraction, we used the Fresnel coefficient which gives the proportion of light that is reflected on a transparent surface given the incident angle and the refraction index of both material. This is mandatory to obtain visually satisfying results. So we trace a reflected ray and a refracted ray and weight the two obtained color by the Fresnel coefficient for the reflected one and (1-Fresnel coefficient) for the refracted one.
3. Glossy (from perfectly reflecting to diffuse): we trace a shadow ray and a recursive new ray. What changes for each level of glossyness is the choose of the ray direction. We implemented a more or less glossy reflection. When the object is the least glossy, it is perfectly diffuse (the ray direction traced for the recursive call is perfectly random in the hemisphere with respect to the surface normal). When it is the most glossy, the vector chosen is the perfectly reflected one. The object can be in between these two extreme cases and is a bit reflective but not perfectly.

## Implementation
### Material
We changed the Material class to match our new effects. We first removed every Phong lightning model value to keep only the object *color* (vec3 for RGB color). Aside that we have a boolean value for mirrorness, another one for transparency and then the refraction index and the glossyness coefficient. There is an order of priority:

1. Transparency
2. Mirrornes
3. Glossyness

That means that if transparency is *true* then mirroness and glossyness values are simply ignored. If transparency is *false* and mirrorness is *true* then object is a mirror. If the object is not transparent, the refraction index is ignored.

### Transparency and refraction
At the intersection with a transparent object, we must compute the refracted vector with respect to the refraction index of the object (we assume that ambient coefficient is 1.0 which is a resonably correct approximation of the air's coefficient) and the reflected one. Then we trace both rays and then weighted the two obtained color by Fresnel coefficient (which gives the weight of the reflected ray) and multiply them by the object color. The refraction indexes used are the real ones.

### Mirror
For the perfect mirror the color returned is simply the trace of the reflected ray (we chose that a mirror has no color).

## References
http://www.kevinbeason.com/smallpt/#moreinfo

http://www.scratchapixel.com/lessons/3d-basic-rendering/introduction-to-shading/reflection-refraction-fresnel


## Difficulties
RAND_MAX not same value on windows and linux (guaranteed only >32767)
# Plane
!!! These modifications have been implemented but we discarded them !!!

We modified the provided Plane class in order to support two new functionalities :

- A plane can be cut, it can have a hole around center of a given hole_radius
- A plane is not necessarly infinite, it can be bounded by a circle of a given outer_radius. This implied the function intersect to be updated (circumscribed circle).
