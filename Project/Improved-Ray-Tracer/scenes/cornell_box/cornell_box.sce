#The origin is at the center of the box

# camera: eye, center, up, fovy, width, height
camera   0 0 600   0 0 0   0 1 0   90   1000 1000

# background color
background   0 0 0

# AreaLights : center, color, block_side, x_parts, y_parts
#areaLight   0 399.999 0   1.0 1.0 1.0   100   2   2

# Spotlight : center, color, direction, radius, angle
light   0 399.999 0   1.0 1.0 1.0   0 -1 0   100   0

# planes: center, normal,  material
# ground, roof and back wall (white)
plane      0 -400    0    0  1  0   1.0 1.0 1.0   0.0  0.0  0.0
plane      0  400    0    0 -1  0   1.0 1.0 1.0   0.0  0.0  0.0
plane      0    0 -400    0  0  1   1.0 1.0 1.0   0.0  0.0  0.0
# left (red) and right (green) walls
plane   -400    0    0    1  0  0   1.0 0.0 0.0   0.0  0.0  0.0
plane    400    0    0   -1  0  0   0.0 1.0 0.0   0.0  0.0  0.0

# cuboids: center, x_size, y_size, z_size, rotation_anglem material
cuboid   -100 -150 -150   300   500   200   -30   0.0 0.0 1.0   0.3 0.0 0.0

# spheres: center, radius, material
sphere   200 -300 50   100   1.0 1.0 0.0   0.05 1.52 0.95
