# Assignment 3 : Raytracing Meshes

## Description
In this assignment, we implemented ray tracing for triangle meshes.

- First, we implemented a method to compute vertex normals as an average of incident triangles' normal weighted by the opening angle of the triangle. To make it efficient, we traversed each triangle once and add the contribution of their normal to the three vertices composing them. At the end, we normalized the all the vertex normals.
- Then, we implemented the method for triangle intersection using the explicit equation of the triangle (with the help of barycentric coordinates representation) and Cramer's rule to solve the equation. Depending on whether we  want a flat shaded or Phong shaded object, we computed the normal accordingly. For Phong lightning, the normal is an interpolation of the normals of each vertex weighted by the barycentric coordinates coefficients. For flat lightning, the normal is simply the triangle's normal.
For this part, we added a method compute_determinant in the Mesh.h/Mesh.cpp files to help us when using the Cramer's rule.
- Finally, to make our raytracer more efficient, we computed the bounding box test for triangle meshes, which avoid to test for many useless ray intersections. To help us with this function, we add an operator overload for the component-wise division of vectors in vec3.h.  
Note that if one of the component of the vector at the denominator is exactly 0.0, it will return infinity in C++, which is in concordance with our implementation.


## Workload
Daniel Filipe NUNES SILVA : 1/3  
Ghali CHRAIBI : 1/3  
Samuel CHASSOT : 1/3
