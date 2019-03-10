# Assignment 2 : Lighting

## Description
In this assignment, we implemented the Phong lighting model and add shadows as well as reflections to our scenes.

- First, we computed the ambient, diffuse and specular contributions of the Phong lighting model.
- Then, we added shadows : the diffuse and specular contributions of a given point change if there is an object between it and the source light. We build a _ray_ from this point (+offset, to avoid self-shadowing) directed to the source light and checked if it intersected any object at a distance smaller than the distance between the point and the source light.
- Finally, we implemented recursive ray tracing to produce reflections. We paid attention to ensure that the reflected rays are out of the intersected object, to avoid again self-shadowing.

The trickiest problem we faced was forgetting to check that the dot product of the light or the reflection vector with the normal was positive before adding respectively the diffuse and specular contributions.

## Workload
Daniel Filipe NUNES SILVA : 1/3  
Ghali CHRAIBI : 1/3  
Samuel CHASSOT : 1/3
