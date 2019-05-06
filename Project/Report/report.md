# Improved Ray Tracer : Group21

## Build Project
- Go to `Improved-Ray-Tracer/`
- `mkdir build`
- `cd build`
- `cmake ..`
- `make -j`
- Ray trace all the scenes with : `./raytrace 0`

## Cuboid
We implemented the class Cuboid, which is described by its center, {x, y, z}_size, rotation_angle and material. The faces of this object are planes. We intersect the ray with the Plane associated with the corresponding face to compute intersections and we restrict them to be on the faces computing the the dot product of the face_center_to_intersection_vector with the {x, y, z}_axis. In order to speed up the computations, we came up with the following tricks :
- We keep track of the number of possible intersections so that we do not necessarly need to iterate over all the faces if the already have computed two intersections.
- We evaluate the norm of face_center_to_intersection_vector and compare it with the norm of (x_size/2,y_size/2,z_size/2), which is the biggest value face_center_to_intersection_vector could have when intersection_point is on a face, before starting any heavy computations.

## Cornell Box
We described a Cornell Box scene (/Improved-Ray-Tracer/scenes/cornell_box/). The origin (0,0,0) is at the center of the box. It is composed of five walls, one light, one cuboid and one sphere. For now, we do not consider specular, shininess nor mirror, which are all set to 0.
Go to `Improved-Ray-Tracer/` and ray trace it with : `./build/raytrace ./scenes/cornell_box/cornell_box.sce ./results/cornell_box.png`

## PlaneLight
#todo
