---
title: Enhanced Ray Tracer using Path Tracing (Group 21)
---
<video width="900px" src="../res/ICG-Final-Presentation-Video-Group21.mp4" loop autoplay muted></video>


# Abstract
The purpose of this project was to improve a ray tracer done in class by adding more complex effects. The basic one used the Phong lighting model to render objects with limited properties such as shininess or reflectance. We opted for the path tracing algorithm which allowed us to obtain more interesting effects including global illumination, soft shadows with surface lights, refraction with caustics, glossiness and mirror.

# Goal
## Core (4.0):
- Basic path tracing with explicit shadow rays at each surface interaction (implemented)
- Diffuse surfaces (implemented)
- Rectangular area lights (implemented)
- Mirrors (implemented)

## Extensions (+1 each):
- Fractals
- Depth of field
- Glossy/blurry reflections, multiple possible outgoing rays based on surface roughness (implemented)
- Refractions (implemented)
- Special light sources. E.g. spotlights (implemented)

# Build Project
- Go to `Improved-Ray-Tracer/`
- `mkdir build`
- `cd build`
- `cmake ..`
- `make -j`
- `cd ..`
- Ray trace `./build/raytrace ./scenes/{...}.sce ./results/{...}.png`

# Shapes

## Cuboid  
We implemented the class Cuboid, which is described by its center, {x, y, z}\_size, rotation\_angle around the y\_axis and material. The faces of this object are planes. We intersect the ray with the Plane associated with the corresponding face to compute intersections and we restrict them to be on the faces computing the the dot product of the face\_center\_to\_intersection\_vector with the {x, y, z}\_axis. In order to speed up the computations, we came up with the following tricks :

- We keep track of the number of possible intersections so that we do not necessarly need to iterate over all the faces if the already have computed two intersections.
- We evaluate the norm of face_center_to_intersection_vector and compare it with the norm of (x\_size/2,y\_size/2,z\_size/2), which is the biggest value face\_center\_to\_intersection\_vector could have when intersection\_point is on a face, before starting any heavy computations (circumscribed sphere).

## Closed cylinder
We also implemented a closed cylinder composed of a hollow cylinder, an upper plane and a lower plane. The planes were restricted to disks with the same radius as the hollow cylinder. When intersecting with rays, we computed the intersection points among the constrained planes and the hollow cylinder and kept the closest one (if there were several).

# Lights
The point lights of the basic ray tracer were replaced by area lights and spotlights. This allows us to produce soft shadows effects. These lights are intersected like objects by the ray tracer in order to appear as a surface on the result image. They act also as lights when checking for lighting. Each light adds a contribution of light proportional to its size in the scene.

## AreaLight
This kind of light has a rectangular shape and is composed of smaller light squares. Each square has a single point light inside whose position is randomly chosen during the lighting operation. This non deterministic technique is computationally more efficient and softens even more the shadows without using a lot of light square inside each light. It is intersected as a whole. When checking for lighting, we iterate over all the lights composing every Arealight and add a contribution for every light directly connected to the point.

## Spotlight
The spotlights are a special kind of lights which illuminate in a given direction and at a given aperture. They have a circular shape. When checking for lighting, we compute the dot product of the light direction vector with the vector V and check if it is bigger than an empirical determined value. Vector V is the vector going from the randomly chosen light point (inside the circular light) to the point, whose lighting is being computed.

# Path Tracing
## Path tracing with explicit shadow rays
As discussed with Tizian before really starting the project, we abandonned the Phong lighting model because it is incompatible with this algorithm replacing it by the Monte Carlo integration and BRDF.

We trace rays for each pixel (~1000 to 10000). Each of these rays is independent from others. Here is the procedure for one ray.

When the ray intersects a surface, first we retrieve the material properties of the intersected object, there are then 3 possibilities which will be detailed:

1. Mirror surfaces: for this one, we trace no shadow rays. The only color returned is the color returned by a recursive ray tracing in the reflected direction with respect to the object normal.

2. Transparent objects: first we assume that the ambient material is air whose refraction index is approximated by 1.0. To implement the refraction, we used the Fresnel coefficient which gives the proportion of light that is reflected on a transparent surface given the incident angle and the refraction index of both material. This is mandatory to obtain visually satisfying results.

3. Glossy (from perfectly reflecting to diffuse): we trace a shadow ray and a recursive new ray. What changes for each level of glossiness is the choice of the ray direction. We implemented a more or less glossy reflection. When the object is the least glossy, it is perfectly diffuse (the ray direction traced for the recursive call is perfectly random in the hemisphere with respect to the surface normal). When it is the most glossy, the vector chosen is the perfectly reflected one. The object can be in between these two extreme cases and is a bit reflective but not perfectly.

## Implementation
### Diffuse
We initially implemented diffuse with mirror and transparent but then we removed it as it is a limit case of glossy.

Initially an object was able to be mirror and diffuse at the same time, with a weight between 0 and 1. Then we chose randomly at each intersection the behavior for this particular ray using the weight as a probability. We abandonned this approach due to the poor result it produced and because of the presence of the glossiness which let an object be a bit reflective and a bit diffuse.

### Material
We changed the Material class to match our new effects. We first removed every Phong lighting model value to keep only the object *color* (vec3 for RGB color). Aside that we have a boolean value for mirrorness, another one for transparency and then the refraction index and the glossiness coefficient. There is an order of priority:

1. Transparency
2. Mirrorness
3. Glossiness

That means that if transparency is *true* then mirroness and glossiness values are simply ignored. If transparency is *false* and mirrorness is *true* then object is a mirror. If the object is not transparent, the refraction index is ignored.

### Transparency and refraction
At the intersection with a transparent object, we must compute the refracted vector with respect to the refraction index of the object and the reflected one. Then we trace both rays and then weighted the two obtained color by Fresnel coefficient (which gives the weight of the reflected ray) and multiply them by the object color. The refraction indexes used are the real ones.

Fresnel coefficient is computed using the Schlick's approximation which is computationally more efficient than the real formula and gives really good results in the computer graphics field.

### Mirror
For the perfect mirror the color returned is simply the trace of the reflected ray (we chose that a mirror has no color).

### Glossy
We implemented glossiness as an intermediate surface between mirrors and diffuse surfaces. The outgoing ray for mirrors is simply reflected while for diffuse surface it goes in any direction. We added a glossy index describing how diffuse a mirror surface is. According to this index the outgoing ray will be shoot either in an hemisphere for a diffuse surface or in a cone along the reflected ray whose aperture is larger or smaller for glossy surfaces.


### Shadow rays and caustics
At every intersection with an object that is not transparent or mirror, we compute a shadow ray to get the direct illumination for this point. To do so, we computed the vector from the intersection point to the light and check if an object intersects this ray. If there is an object in between, the point is not directly lit, if nothing intersects, the light contribution is computed by multiplying the object's color by the light's color and by the dot product between the vector to the light and the intersection normal.

To implement the caustics, we changed a bit this algorithm and the lighting method which has now a parameter saying if we are computing a "normal ray" or a shadow ray. If it is a shadow ray, if the object intersected is glossy, it returns vec3(0.0), if it is mirror or transparent, it returns a recursive call on the appropriate vector (reflected or refracted). If the shadow ray intersects a light, it returns the light's color.

As this a shadow ray returns a color contribution only if it eventually reaches the light.

The algorithm to compute shadow ray (direct illumination) is like before but if an object is in between, we trace a shadow ray using the lighting method with shadow ray = true following the point-to-light vector.

This makes possible for the light to lit a point behind a transparent object.

This is not the perfectly reallistic behavior but satisfyingly approximate the caustics effect.

# References
- ../res/references/Monte-Carlo-Ray-Tracing-Cornell-Lecture.pdf
- ../res/references/Global-Illumination-Path-Tracing-Taku-Komura-Lecture.pdf
- ../res/references/Path-Tracing-Matthias-Teschner-Lecture.pdf
- en.wikipedia.org/wiki/Path_tracing
- scratchapixel.com/lessons/3d-basic-rendering/global-illumination-path-tracing
- scratchapixel.com/lessons/3d-basic-rendering/introduction-to-shading/reflection-refraction-fresnel
- web.cs.wpi.edu/~emmanuel/courses/cs563/write_ups/zackw/realistic_raytracing.html
- www.kevinbeason.com/smallpt/#moreinfo
- en.wikipedia.org/wiki/Schlick%27s_approximation

# Difficulties
## Changing the whole model for the lighting procedure
When starting the project with the Phong Lighting model, some members of the group tried to implement some of the effects given as targets, based on the initial ray tracer. However, if the Phong lighting model is a simple model to implement and can approximate some basic effects quite well, it prevents the implementation of more complex effects. Indeed, even if it is possible to add refraction with this model, we could not have rendered realistic soft shadows and glossiness without changing the model, here to Path tracing.  

## RAND_MAX is not the same value on different systems
We used Windows to generate the final images. The result was different when running same code on Windows or MacOS/Linux. After a lot of debugging time, we found that RAND\_MAX (the maximum value returned by rand() method) is not the same on windows and Unix. Indeed it was only guaranteed to be greater or equal to 32767.

## Computation of the outgoing ray of glossy surfaces is not trivial
We ended up using Rodrigues' rotation formula and fancy cross products to compute the random outgoing rays in for glossy surfaces because the only informations we have are the incoming ray and the surface normal. The details can be found in reflect\_glossy function of *vec3.h* and *scene.cpp*.

## BRDF and light contribution
It was not trivial to understand well how light contributes to a point taking into account the Monte Carlo integration principle. It took some time to implement correctly the lighting method.

## Plane
!!! These modifications have been implemented but we discarded them !!!

We modified the provided Plane class in order to support two new functionalities :

- A plane can be cut, it can have a hole around center of a given hole\_radius
- A plane is not necessarily infinite, it can be bounded by a circle of a given outer\_radius. This implied the function intersect to be updated (circumscribed circle).


# Workload

## Daniel Filipe Nunes Silva  
First, I implemented the Cuboid class and designed the basic Cornell box. Then, I made research for and implemented the lights: AreaLight and Spotlight classes and how they are integrated in the lighting function. Finally, I worked on glossy surfaces (including the method that computes the outgoing vector) and described two Cornell boxes with 3 sphere and 3 cuboids of different surfaces.

## Samuel Chassot
I made research about how to do path tracing and then implemented the basic path tracing algorithm with diffuse (which was replaced by glossiness) and mirror objects. Then I made research and implemented transparency (with refraction and Fresnel including the two corresponding functions in *vec3.h* that computes them) and then caustics effect. Finally I designed and described the glass with straw scene and Cornell Box with a cuboid and a ball.

## Ghali Chraïbi
I implemented first the ClosedCylinder shape. Then I documented myself and tried an implementation of the refraction effect (before we decided to use path tracing). Afterwards I thought about how to implement the AreaLight and helped in the implementation of Light/AreaLight. Finally I designed and implemented various scenes.
