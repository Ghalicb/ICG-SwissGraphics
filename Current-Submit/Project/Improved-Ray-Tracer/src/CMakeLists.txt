file(GLOB SRCS_COMMON Cylinder.cpp Mesh.cpp Plane.cpp Scene.cpp Sphere.cpp vec3.cpp Image.cpp Cuboid.cpp AreaLight.cpp Spotlight.cpp ClosedCylinder.cpp)
file(GLOB SRCS raytrace.cpp ${SRCS_COMMON})
file(GLOB HDRS ./*.h)

add_executable(raytrace raytrace.cpp ${SRCS_COMMON} ${HDRS})

target_link_libraries(raytrace lodePNG)
