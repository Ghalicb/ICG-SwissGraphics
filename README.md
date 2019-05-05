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

## Assignment 3 : Raytracing meshes

### Description
In this assignment, we implemented ray tracing for triangle meshes.

- First, we implemented a method to compute vertex normals as an average of incident triangles' normal weighted by the opening angle of the triangle. To make it efficient, we traversed each triangle once and add the contribution of their normal to the three vertices composing them. At the end, we normalized the all the vertex normals.
- Then, we implemented the method for triangle intersection using the explicit equation of the triangle (with the help of barycentric coordinates representation) and Cramer's rule to solve the equation. Depending on whether we  want a flat shaded or Phong shaded object, we computed the normal accordingly. For Phong lightning, the normal is an interpolation of the normals of each vertex weighted by the barycentric coordinates coefficients. For flat lightning, the normal is simply the triangle's normal.
For this part, we added a method compute_determinant in the Mesh.h/Mesh.cpp files to help us when using the Cramer's rule.
- Finally, to make our raytracer more efficient, we computed the bounding box test for triangle meshes, which avoid to test for many useless ray intersections. To help us with this function, we add an operator overload for the component-wise division of vectors in vec3.h.
Note that if one of the component of the vector at the denominator is exactly 0.0, it will return infinity in C++, which is in concordance with our implementation.

### Workload
Daniel Filipe NUNES SILVA : 1/3  
Ghali CHRAIBI : 1/3  
Samuel CHASSOT : 1/3  

## Assignment 4 : OpenGL "Hello World"

### Description
Basic setup for OpenGL

### Workload
Daniel Filipe NUNES SILVA : 1/3  
Ghali CHRAIBI : 1/3  
Samuel CHASSOT : 1/3  

## Assignment 5 : Transformations and Viewing

### Description
In this assignment, we built a scene containing several objects (planets from the solar system, a moon and a spaceship), as well as an eye to observe this scene. We also implemented the basic rendering pipeline to render each object with its corresponding texture. We finally added keyboard events to interract with the eye.

- We spent most of the time understanding how matrices modify objects positions and how they should be combined.
- Our first approach was to update planets' positions step by step. But we finally decided to make use of the stored angle of orbit to compute the rotation from the initial position.

### Workload
Daniel Filipe NUNES SILVA : 1/3  
Ghali CHRAIBI : 1/3  
Samuel CHASSOT : 1/3  

## Assignment 6 : Texturing and Lighting

### Description

In this assignment, we used the billboarding technique to mimic the sun's glow. We had first difficulties to figure out how to make the billboard always facing the eye (we tried to find the angles of the billboard using trigonometric functions), but after some time we saw that these angles were already computed and corresponded to the given x\_angle_ and y\_angle_.
For the rendering of this sun's glow, we tried many functions to make it realistic and we finally decided to use an exponential as its curvature correspond well to the wanted phenomena.

Then we implemented the Phong lighting model to illuminate the planets. For that we needed to pass the modelview, modelview_projection and normal matrixes throw the phong vertex shader to compute the n,l,v vectors that we used in the fragment shader to apply the formula of the phong model derived in class.

Finaly, we focused our work on the earth and we combined multiple textures to visualize day/night, clouds and specularity of the water according to the state of the earth.

Bonus : We added gradual disturbance of the geometry of the sphere representing the sun in the sun vertex shader. For that, we tried many different trigonometric formulas so that the fluid effect on the sun is visible, but still realistic.

### Workload
Daniel Filipe NUNES SILVA : 1/3  
Ghali CHRAIBI : 1/3  
Samuel CHASSOT : 1/3  

## Assignment 7 : Shadows and Cube Mapping

### Description
In this assignment, we implemented a real-time shadowing technique for multiple omni-directional point lights.

First, we implemented the view and projection matrices for a cube face. For the view matrix, we struggled a bit figuring out which matrices to use in order to switch between the coordinates systems.

Then, we worked on the fragment shader and implemented Phong lighting in it. Shadows were handled using shadow map. Signs of vectors and coordinates systems were also a challenging part. 

### Workload
Daniel Filipe NUNES SILVA : 1/3  
Ghali CHRAIBI : 1/3  
Samuel CHASSOT : 1/3  

## Assignment 8 : Lindenmayer Systems

### Description  

The main part of this assignment was to implement a Lindenmayer system's generator.   
First, we implemented functions for the expansion of such L-systems. Then we built a finite state machine to register all the lines that need to be drawn for a certain level of expansion of an L-systems. And as a more advanced topic, we implemented stochastic L-systems.

On the second part, we had to understand how L-systems worked, by reverse-engineered them.    
Even if we could quickly find the rules for "basic" cases, we saw that it becomes much harder when we needed to use several variables.

### Workload  
Daniel Filipe NUNES SILVA : 1/3  
Ghali CHRAIBI : 1/3  
Samuel CHASSOT : 1/3  

## Assignment 9 : Perlin Noise, Procedural Terrain

### Description

### Workload
Daniel Filipe NUNES SILVA : 1/3  
Ghali CHRAIBI : 1/3  
Samuel CHASSOT : 1/3  
