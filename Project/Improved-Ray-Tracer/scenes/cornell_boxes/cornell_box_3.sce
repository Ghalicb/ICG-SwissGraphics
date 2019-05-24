#The origin is at the center of the box

# maximum recursion depth and number of paths per pixel
max_depth 7
paths_per_pixel 20

# camera: eye, center, up, fovy, width, height
camera   0 0 800   0 0 0   0 1 0   75   1000 1000

# background color
background   0 0 0

# AreaLights : center, color, block_side, x_parts, y_parts
areaLight   0 399.999 0   1.0 1.0 1.0   30   2   2

# Spotlight : center, color, direction, radius
light    280  320 -280   1.0 1.0 1.0   -380 -570 130   120
light   -280  320 -280   1.0 1.0 1.0    180 -570 130  120


# planes: center, normal,  material
# ground, roof and back wall (white)
plane      0 -400    0    0  1  0   0.37 0.81 1.0   0 0 0.0 1.0
plane      0  400    0    0 -1  0   1.0 1.0 1.0   0 0 0.0 1.0
plane      0    0 -400    0  0  1   0.7 0.7 0.7   0 0 0.0 1.0
# left (red) and right (green) walls
plane   -400    0    0    1  0  0   0.93 0.48 1.0   0 0 0.0 1.0
plane    400    0    0   -1  0  0   0.0 1.0 0.0   0 0 0.0 1.0


# spheres: center, radius, material
sphere    200 -300   50   100   1.0 1.0 1.0   0 0 0.0  0.3
sphere   -100 -250 -150   150   1.0 0.0 1.0   0 0 0.0  0.6
#sphere    -200 -250  70    100   1.0 1.0 1.0   0 1 1.52 0.3

# cuboids: center, x_size, y_size, z_size, rotation_anglem material
cuboid   -150 -150 100   200   500   150   20   1.0 1.0 1.0   0 1 1.52 1.0
