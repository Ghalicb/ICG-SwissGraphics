#The origin is at the center of the box

# maximum recursion depth and number of paths per pixel
max_depth 3
paths_per_pixel 3

# camera: eye, center, up, fovy, width, height
camera   0 0 800   0 0 0   0 1 0   75   1000 1000

# background color
background   0 0 0

# AreaLights : center, color, block_side, x_parts, y_parts
areaLight   0 399.999 0   1.0 1.0 1.0   150   2   2


# planes: center, normal,  material
# ground, roof and back wall (white)
plane      0 -400    0    0  1  0   0.07 0.82 1.00   0 0 0.0 1.0
plane      0  400    0    0 -1  0   1.00 1.00 1.00   0 0 0.0 1.0
plane      0    0 -400    0  0  1   1.00 0.20 0.00   0 0 0.0 1.0
# left (red) and right (green) walls
plane   -400    0    0    1  0  0   0.43 0.07 0.90   0 0 0.0 1.0
plane    400    0    0   -1  0  0   0.92 0.81 0.16   0 0 0.0 1.0


# spheres: center, radius, material
sphere   -250 -150 100   100   1.0 1.0 1.0   0 0 0.0  0.50
sphere      0 -150 100   100   1.0 0.0 1.0   1 0 0.00 0.00
sphere    250 -150 100   100   1.0 1.0 1.0   0 1 1.80 0.00
