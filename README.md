# ICG-SwissGraphics

## Assignment 0 : "Hello World"

### Description
We solve this exercice by changing the color of the background in the solid_color scene from black to red.

### Workload
Daniel Filipe NUNES SILVA : 1/3  
Ghali CHRAIBI : 1/3  
Samuel CHASSOT : 1/3  

## Assignment 1 : Planes and Cylinders

### Description
- In the first part of the assignment, we implemented ray intersections with planes using mainly the implicit equation of a plane, derived in class.
- Then, we derived the implicit equation of a cylinder (cf. TheoryExercise.pdf), which was for us the most difficult part of the week.
- Finally, having the implicit equation of the cylinder, we implemented ray intersections with cylinders without many difficulties.

### Workload
Daniel Filipe NUNES SILVA : 1/3  
Ghali CHRAIBI : 1/3  
Samuel CHASSOT : 1/3

## Assignment 2 : Lighting

### Description
#### Todo
- We implemented recursive ray tracing to compute reflections. We paid attention to ensure that the reflected rays are out of the intersected object, otherwise little black dot (shadows) may _randomly_ appear on the computed points.
- We computed the Phong lighting. Ambient contribution is trivial while diffuse and specular need more work. Ensuring that we are dealing with normalized vector is always a challenge.
- The trickiest problem we faced was forgetting to check that the dot product of the light or the reflection vector and the normal was positive before adding the diffuse and specular (respectivly) contributions.

### Workload
Daniel Filipe NUNES SILVA : 1/3  
Ghali CHRAIBI : 1/3  
Samuel CHASSOT : 1/3
