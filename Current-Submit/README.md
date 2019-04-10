# Assignment 6 : Texturing and Lighting

## Description

In this assignment, we used the billboarding technique to mimic the sun's glow. We had first difficulties to figure out how to make the billboard always facing the eye (we tried to find the angles of the billboard using trigonometric functions), but after some time we saw that these angles were already computed and corresponded to the given x\_angle_ and y\_angle_.  
For the rendering of this sun's glow, we tried many functions to make it realistic and we finally decided to use an exponential as its curvature correspond well to the wanted phenomena.

Then we implemented the Phong lighting model to illuminate the planets. For that we needed to pass the modelview, modelview_projection and normal matrixes throw the phong vertex shader to compute the n,l,v vectors that we used in the fragment shader to apply the formula of the phong model derived in class. 

Finaly, we focused our work on the earth and we combined multiple textures to visualize day/night, clouds and specularity of the water according to the state of the earth.

Bonus : We added gradual disturbance of the geometry of the sphere representing the sun in the sun vertex shader. For that, we tried many different trigonometric formulas so that the fluid effect on the sun is visible, but still realistic.

## Workload
Daniel Filipe NUNES SILVA : 1/3  
Ghali CHRAIBI : 1/3  
Samuel CHASSOT : 1/3
