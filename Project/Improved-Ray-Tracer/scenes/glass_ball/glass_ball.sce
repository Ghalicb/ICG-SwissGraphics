#The origin is at the center of the box

# maximum recursion depth and number of paths per pixel
max_depth 10
paths_per_pixel 1500

# camera: eye, center, up, fovy, width, height
camera   0 0 600   0 0 0   0 1 0   90   1000 1000

# background color
background   0 0 0

# AreaLights : center, color, block_side, x_parts, y_parts
areaLight   100 399.999 100   1.0 1.0 1.0   20   2   2
areaLight   -100 399.999 -100   1.0 1.0 1.0   20   2   2


# Spotlight : center, color, direction, radius
light   0 399.999 0   1.0 1.0 1.0   0 -1 0   50

# planes: center, normal,  material
# ground, roof and back wall (white)
plane      0 -400    0    0  1  0   0.93 0.42 1.0   0 0 0 1
plane      0  400    0    0 -1  0   1.0 1.0 1.0   0 0 0 1
plane      0    0 -400    0  0  1   1.0 1.0 1.0   0 0 0 1
# left (red) and right (green) walls
plane   -400    0    0    1  0  0   1.0 0.0 0.0   0 0 0 1
plane    400    0    0   -1  0  0   0.0 1.0 0.0   0 0 0 1

# spheres: center, radius, material
sphere   0 0 0   100   1.0 1.0 1.0   0 1 1.52 1.0
