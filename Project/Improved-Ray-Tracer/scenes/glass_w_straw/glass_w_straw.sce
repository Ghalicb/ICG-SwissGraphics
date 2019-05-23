#The origin is at the center of the box

# maximum recursion depth and number of paths per pixel
max_depth 15
paths_per_pixel 5000

# camera: eye, center, up, fovy, width, height
camera   -150 200 600   0 1 -4   0 1 0   80   1000 1000

# background color
background   0 0 0

# AreaLights : center, color, block_side, x_parts, y_parts
areaLight   0 899 0   1.0 1.0 1.0   100   2   2


# planes: center, normal,  material
# ground, roof and back wall (white)
plane      0 -700    0    0  1  0   0.03 0.16 0.25   0.0  0.0  0.0
plane      0  900    0    0 -1  0   0.8 0.8 0.8      0.0  0.0  0.0
plane      0    0 -700    0  0  1   0.8 0.8 0.8      0.0  0.0  0.0
# left (red) and right (green) walls
plane   -700    0    0    1  0  0   0.8 0.8 0.8      0.0  0.0  0.0
plane    700    0    0   -1  0  0   0.8 0.8 0.8      0.0  0.0  0.0


# closed cylinders : center, radius, axis, height, material
# glass
closedCylinder    -30 -160 -10   200   0 1 0   300    1.0 1.0 1.0  0.0 1.33 1.0
#straw
cylinder    44 -74 -10   30   200 200 0   700    1.0 0.0 0.0  0.0 0.0 0.0
