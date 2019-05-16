#The origin is at the center of the box

# camera: eye, center, up, fovy, width, height
camera   0 0 600   0 0 0   0 1 0  90  1500 1500

# background color
background   0 0 0

# lights: position and color
light       0   0.999    0   1.0 1.0 1.0

# AreaLights : center, color, x_parts, y_parts
areaLight   0 399.999    0   1.0 1.0 1.0   5   5

# planes: center, normal,  material
# ground, roof and back wall
plane      0 -400    0    0  1  0   1.0 1.0 1.0   0.0  0.0  0.0
plane      0  400    0    0 -1  0   1.0 1.0 1.0   0.0  0.0  0.0
plane      0    0 -400    0  0  1   1.0 1.0 1.0   0.0  0.0  0.0
# left and right walls
plane   -400    0    0    1  0  0   1.0 0.0 0.0   0.0  0.0  0.0
plane    400    0    0   -1  0  0   0.0 1.0 0.0   0.0  0.0  0.0

# cuboids: center, x_size, y_size, z_size, rotation_anglem material
cuboid   -100 -150 -150   300   500   200  -30    0.0 0.0 1.0   0.3  0.0  0.0

# closed cylinders : center, radius, axis, height, material
closedCylinder    150 100 200   50   1 0 1   200    0.2 0 0

# spheres: center, radius, material
sphere    200 -300   50   100   1.0 1.0 0.0    0.0    0.0  0.0
