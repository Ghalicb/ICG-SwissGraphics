//=============================================================================
//
//   Exercise code for the lecture "Introduction to Computer Graphics"
//     by Prof. Mario Botsch, Bielefeld University
//
//   Copyright (C) by Computer Graphics Group, Bielefeld University
//
//=============================================================================

#version 140

in vec3 v2f_normal;
in vec2 v2f_texcoord;
in vec3 v2f_light;
in vec3 v2f_view;

out vec4 f_color;

uniform sampler2D day_texture;
uniform sampler2D night_texture;
uniform sampler2D cloud_texture;
uniform sampler2D gloss_texture;
uniform bool greyscale;

const float shininess = 20.0;
const vec3  sunlight = vec3(1.0, 0.941, 0.898);

void main()
{
    /** \todo
    * - Copy your working code from the fragment shader of your Phong shader use it as
    * starting point
    * - instead of using a single texture, use the four texures `day_texture`, `night_texture`,
    * `cloud_texture` and `gloss_texture` and mix them for enhanced effects
    * Hints:
    * - cloud and gloss textures are just greyscales. So you'll just need one color-
    * component.
    * - The texture(texture, 2d_position) returns a 4-vector (rgba). You can use
    * `texture(...).r` to get just the red component or `texture(...).rgb` to get a vec3 color
    * value
    * - use mix(vec3 a,vec3 b, s) = a*(1-s) + b*s for linear interpolation of two colors
     */

    vec3 color = vec3(0.0,0.0,0.0);
    vec3 color_day = vec3(0.0,0.0,0.0);
    vec3 color_night = vec3(0.0,0.0,0.0);
    vec3 color_clouds = vec3(0.0,0.0,0.0);

    vec3 Ia = 0.2*sunlight;
    vec3 Il = sunlight;
    vec3 day_texRGB = texture(day_texture, v2f_texcoord).rgb;
    vec3 night_texRGB = texture(night_texture, v2f_texcoord).rgb;
    vec3 cloud_texRGB = texture(cloud_texture, v2f_texcoord).rgb;
    float gloss_texBin = texture(gloss_texture, v2f_texcoord).r;

    vec3 r_vector = reflect(v2f_light, v2f_normal);

    //combine gloss and cloudiness to get specular weight [0;1]
    float specularity_factor = 0.0;
    if (gloss_texBin == 1.0) {
        specularity_factor = 1-cloud_texRGB.r;
    }
    vec3 m_s = specularity_factor * vec3(1,1,1);

    //add the ambient component to the color_day vector
    color_day += Ia * day_texRGB;
    color_clouds += Ia * cloud_texRGB;

    if (dot(v2f_normal, v2f_light) > 0) {
        // add the diffuse component to day color
        color_day += Il * day_texRGB * dot(v2f_normal, v2f_light);
        color_clouds += Il * cloud_texRGB * dot(v2f_normal, v2f_light);

        if (dot(r_vector, v2f_view) > 0) {
            // add the specular component
            color_day += Il * m_s * pow(dot(r_vector, v2f_view), shininess);
        }
    }

    // compute final color_day by interpolating day color and cloud color
    color_day = mix(color_day, color_clouds, cloud_texRGB.r);

    // compute color_night by interpolating night texture and pure black
    color_night = mix(night_texRGB, vec3(0.0, 0.0, 0.0), cloud_texRGB.r);

    // compute final color by interpolating night and day components
    color = mix(color_night, color_day, dot(v2f_normal, v2f_light));

    // convert RGB color to YUV color and use only the luminance
    if (greyscale) color = vec3(0.299*color.r+0.587*color.g+0.114*color.b);

    // add required alpha value
    f_color = vec4(color, 1.0);

}
