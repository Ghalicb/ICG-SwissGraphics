## Assignment 2 : Lighting

### Description

The aim of this assignment was to implement the Phong Lighting model and add reflection to our scene.

- We first computed the three contributions of the Phong Lighting model : the ambient lighting, the diffuse lighting and the specular lighting.
- After that, we added shadows effect. For that, we had to consider that their can be many objects in the scene and that if an object eclipses another, it will have an impact on the diffuse and specular contribution of the second object.
- Finally, we implemented recursive ray tracing to compute reflections. We paid attention to ensure that the reflected rays are out of the intersected object, otherwise little black dot (shadows) may _randomly_ appear on the computed points.

In this assignment, the trickiest problem we faced was forgetting to check that the dot product of the light or the reflection vector with the normal was positive before adding respectively the diffuse and specular contributions.


#### Workload
Daniel Filipe NUNES SILVA : 1/3  
Ghali CHRAIBI : 1/3  
Samuel CHASSOT : 1/3
