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
In this assignment, we implemented the Phong lighting model and add shadows as well as reflections to our scenes.

- First, we computed the ambient, diffuse and specular contributions of the Phong lighting model.
- Then, we added shadows : the diffuse and specular contributions of a given point change if there is an object between it and the source light. We build a _ray_ from this point (+offset, to avoid self-shadowing) directed to the source light and checked if it intersected any object at a distance smaller than the distance between the point and the source light.
- Finally, we implemented recursive ray tracing to produce reflections. We paid attention to ensure that the reflected rays are out of the intersected object, to avoid again self-shadowing.
- The trickiest diffulty we overcame was forgetting to check that the dot product of the light or the reflection vector with the normal was positive before adding respectively the diffuse and specular contributions.

### Workload
Daniel Filipe NUNES SILVA : 1/3  
Ghali CHRAIBI : 1/3  
Samuel CHASSOT : 1/3
