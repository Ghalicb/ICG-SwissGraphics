#The origin is at the center of the box

# maximum recursion depth and number of paths per pixel
max_depth 2
paths_per_pixel 2

# camera: eye, center, up, fovy, width, height
camera   0 0 600   0 0 0   0 1 0   90   1000 1000

# background color
background   0 0 0

# AreaLights : center, color, block_side, x_parts, y_parts
areaLight   -200 399.999 -250   1.0 1.0 1.0   50   4   3

# planes: center, normal,  material
# ground, roof and back wall (white)
plane      0 -400    0    0  1  0   1.0 1.0 1.0   0.0  0.0  0.0
plane      0  400    0    0 -1  0   1.0 1.0 1.0   0.0  0.0  0.0
plane      0    0 -400    0  0  1   1.0 1.0 1.0   0.0  0.0  0.0
# left (white) and right (white) walls
plane   -400    0    0    1  0  0   1.0 1.0 1.0   0.0  0.0  0.0
plane    400    0    0   -1  0  0   1.0 1.0 1.0   0.0  0.0  0.0

# cuboids: center, x_size, y_size, z_size, rotation_angle material
cuboid   250 -300 -250   120   200   120   0   1.0 0.0 0.1   0.2 0.0 0.0

# cylinder: center, radius, axis, height, material
cylinder  -325 0 0   12    0 1 0   800    0.5 0.5 0.5   0.5 1.0 0.5
cylinder  -250 0 0   12    0 1 0   800    0.5 0.5 0.5   0.5 1.0 0.5
cylinder  -175 0 0   12    0 1 0   800    0.5 0.5 0.5   0.5 1.0 0.5
cylinder  -100 0 0   12    0 1 0   800    0.5 0.5 0.5   0.5 1.0 0.5
cylinder  -25 0 0   12    0 1 0   800    0.5 0.5 0.5   0.5 1.0 0.5
cylinder  50 0 0   12    0 1 0   800    0.5 0.5 0.5   0.5 1.0 0.5
cylinder  125 0 0   12    0 1 0   800    0.5 0.5 0.5   0.5 1.0 0.5
cylinder  200 0 0   12    0 1 0   800    0.5 0.5 0.5   0.5 1.0 0.5
cylinder  275 0 0   12    0 1 0   800    0.5 0.5 0.5   0.5 1.0 0.5
cylinder  350 0 0   12    0 1 0   800    0.5 0.5 0.5   0.5 1.0 0.5

# closed cylinders : center, radius, axis, height, material
#closedCylinder    150 100 200   50   1 0 1   200    0.2 0 0
