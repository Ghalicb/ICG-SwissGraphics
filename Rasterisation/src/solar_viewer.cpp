//=============================================================================
//
//   Exercise code for the lecture "Introduction to Computer Graphics"
//     by Prof. Mario Botsch, Bielefeld University
//
//   Copyright (C) by Computer Graphics Group, Bielefeld University
//
//=============================================================================

#include "solar_viewer.h"
#include "glmath.h"
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include <array>

//=============================================================================


Solar_viewer::Solar_viewer(const char* _title, int _width, int _height)
    : GLFW_window(_title, _width, _height),
      unit_sphere_(50), //level of tesselation

      /** Use the following for better planet distances/sizes (but still not realistic)
      * To get a true-to-scale solar system, planets would be 20x smaller, and their distance to the sun would be ~11x larger
      * For example r_mercury/r_sun = 0.0034 and distance_mercury_to_sun/r_sun = 33.3
      **/
      //  sun_    (0.0f,              2.0f*(float)(M_PI)/26.0f,   1.0f,    0.0f),
      //  mercury_(2.0f*(float)(M_PI)/116.0f,  2.0f*(float)(M_PI)/58.5f,   0.068f, -3.1f),
      //  venus_  (2.0f*(float)(M_PI)/225.0f,  2.0f*(float)(M_PI)/243.0f,  0.174f,   -7.2f),
      //  earth_  (2.0f*(float)(M_PI)/365.0f,  2.0f*(float)(M_PI),        0.182f,   -9.8f),
      //  moon_   (2.0f*(float)(M_PI)/27.0f,   0.0f,  0.048f,   -0.5f),
      //  mars_   (2.0f*(float)(M_PI)/687.0f,  2.0f*(float)(M_PI)*24.0f/25.0f, 0.098f,-13.8f),
      //  stars_  (0.0f, 0.0f, 30.0f, 0.0f)

      // Even more unrealistic placement/sizing for nicer visualization.
      sun_    (0.0,              2.0*M_PI/26.0,   1.0f,    0.0f),
      mercury_(2.0*M_PI/116.0f,  2.0*M_PI/58.5,   0.075f, -1.4f),
      venus_  (2.0*M_PI/225.0f,  2.0*M_PI/243.0,  0.2f,   -2.2f),
      earth_  (2.0*M_PI/365.0f,  2.0*M_PI,        0.25,   -3.3f),
      moon_   (2.0*M_PI/27.0f,   0.0,  0.04,   -0.4f),
      mars_   (2.0*M_PI/687.0f,  2.0*M_PI*24.0/25.0, 0.15,-5.0f),
      stars_  (0.0, 0.0, 21.0, 0.0)
{
    // start animation
    timer_active_ = true;
    time_step_ = 1.0f/24.0f; // one hour

    // rendering parameters
    greyscale_     = false;
    fovy_ = 45;
    near_ = 0.01f;
    far_  = 20;

    // initial viewing setup
    planet_to_look_at_ = &earth_;
    x_angle_ = 0.0f;
    y_angle_ = 0.0f;
    dist_factor_ = 4.5f;

    ship_.pos_ = planet_to_look_at_->pos_ - vec4(0.0f, 0.0f, dist_factor_*planet_to_look_at_->radius_, 0.0f);
    ship_.direction_ = vec4(0.0f, 0.0f, 1.0f,0.0f);
    in_ship_ = false;

    srand((unsigned int)time(NULL));
}

//-----------------------------------------------------------------------------

void
Solar_viewer::
keyboard(int key, int scancode, int action, int mods)
{
    if (action == GLFW_PRESS || action == GLFW_REPEAT)
    {
        // Change view between the various bodies with keys 1..6
        if ((key >= GLFW_KEY_1) && (key <= GLFW_KEY_6)) {
            std::array<const Planet *, 6> bodies = { &sun_, &mercury_, &venus_, &earth_, &moon_, &mars_};
            in_ship_ = false;
            planet_to_look_at_ = bodies.at(key - GLFW_KEY_1);
        }
        switch (key)
        {
            // Key 7 switches to viewing the ship.
            case GLFW_KEY_7:
            {
                planet_to_look_at_ = NULL;
                in_ship_ = true;
                break;
            }

            case GLFW_KEY_8:
            {
                if (dist_factor_ - DELTA_DIST_FACTOR >= 2.5)
                    dist_factor_ -= DELTA_DIST_FACTOR;
                break;
            }

            case GLFW_KEY_9:
            {
                if (dist_factor_ + DELTA_DIST_FACTOR <= 20.0)
                    dist_factor_ += DELTA_DIST_FACTOR;
                break;
            }

            case GLFW_KEY_R:
            {
                randomize_planets();
                break;
            }

            case GLFW_KEY_G:
            {
                greyscale_ = !greyscale_;
                break;
            }

            case GLFW_KEY_W:
            {
                if (in_ship_)
                    ship_.accelerate(0.001f);
                break;
            }
            case GLFW_KEY_S:
            {
                if (in_ship_)
                    ship_.accelerate(-0.001f);
                break;
            }
            case GLFW_KEY_A:
            {
                if (in_ship_)
                    ship_.accelerate_angular(0.02f);
                break;
            }
            case GLFW_KEY_D:
            {
                if (in_ship_)
                    ship_.accelerate_angular(-0.02f);
                break;
            }

            case GLFW_KEY_C:
                curve_display_mode_ = CurveDisplayMode((int(curve_display_mode_) + 1) % int(CURVE_SHOW_NUM_MODES));
                break;
            case GLFW_KEY_T:
                ship_path_frame_.toggleParallelTransport();
                std::cout << (ship_path_frame_.usingParallelTransport() ? "enabled" : "diabled") << " parallel transport" << std::endl;
                break;

            case GLFW_KEY_LEFT:
            {
                y_angle_ -= 10.0;
                break;
            }

            case GLFW_KEY_RIGHT:
            {
                y_angle_ += 10.0;
                break;
            }

            case GLFW_KEY_DOWN:
            {
                x_angle_ += 10.0;
                break;
            }

            case GLFW_KEY_UP:
            {
                x_angle_ -= 10.0;
                break;
            }

            case GLFW_KEY_SPACE:
            {
                timer_active_ = !timer_active_;
                break;
            }

            case GLFW_KEY_P:
            case GLFW_KEY_KP_ADD:
            case GLFW_KEY_EQUAL:
            {
                time_step_ *= 2.0f;
                std::cout << "Time step: " << time_step_ << " days\n";
                break;
            }

            case GLFW_KEY_M:
            case GLFW_KEY_KP_SUBTRACT:
            case GLFW_KEY_MINUS:
            {
                time_step_ *= 0.5f;
                std::cout << "Time step: " << time_step_ << " days\n";
                break;
            }

            case GLFW_KEY_ESCAPE:
            {
                glfwSetWindowShouldClose(window_, GL_TRUE);
                break;
            }
        }
    }
}

// Update the current positions of the celestial bodies based their angular distance
// around their orbits. This position is needed to set up the camera in the scene
// (see Solar_viewer::paint)
void Solar_viewer::update_body_positions() {

    // New planet angle orbit are incremented, then, planet are rotated around y
    // as if they were rotated of angle_orbit_ from the initial position

    // Update earth position
    earth_.angle_orbit_ += earth_.angle_step_orbit_;
    earth_.pos_ = mat4::rotate_y(earth_.angle_orbit_) * vec4(earth_.distance_, 0, 0, 1);

    // Update mercury position
    mercury_.angle_orbit_ += mercury_.angle_step_orbit_;
    mercury_.pos_ = mat4::rotate_y(mercury_.angle_orbit_) * vec4(mercury_.distance_, 0, 0, 1);

    // Update mars position
    mars_.angle_orbit_ += mars_.angle_step_orbit_;
    mars_.pos_ = mat4::rotate_y(mars_.angle_orbit_) * vec4(mars_.distance_, 0, 0, 1);

    // Update venus position
    venus_.angle_orbit_ += venus_.angle_step_orbit_;
    venus_.pos_ = mat4::rotate_y(venus_.angle_orbit_) * vec4(venus_.distance_, 0, 0, 1);

    // Update moon position
    moon_.angle_orbit_ += moon_.angle_step_orbit_;
    moon_.pos_ = mat4::rotate_y(moon_.angle_orbit_) * vec4(moon_.distance_, 0, 0, 1);

    // Moon is a special case : it is translated to rotate around the earth
    mat4 translation_to_earth_orbit = mat4::translate(vec3(earth_.pos_));
    moon_.pos_ = translation_to_earth_orbit * moon_.pos_;
}

//-----------------------------------------------------------------------------


void Solar_viewer::timer()
{
    if (timer_active_) {
            sun_.time_step(time_step_);
        mercury_.time_step(time_step_);
          venus_.time_step(time_step_);
          earth_.time_step(time_step_);
           moon_.time_step(time_step_);
           mars_.time_step(time_step_);
        update_body_positions();

        ship_.update_ship();

        // Desired ship speed (in units of Euclidean distance per animation
        // frame, not curve parameter distance). This is the (constant)
        // Euclidean step length we want the ship to make during each time step.
        const float ship_speed = 0.01;
        ship_path_param_ = 0;
        if (ship_path_param_ >= 1) { ship_path_param_ = 0; }
        vec3 tangent = ship_path_.tangent(ship_path_param_);
        ship_path_frame_.alignTo(tangent);
    }
}


//-----------------------------------------------------------------------------


void Solar_viewer::resize(int _width, int _height)
{
    width_  = _width;
    height_ = _height;
    glViewport(0, 0, _width, _height);
}

//-----------------------------------------------------------------------------


void Solar_viewer::initialize()
{
    // set initial state
    glClearColor(1,1,1,0);
    glEnable(GL_DEPTH_TEST);

    // Allocate textures
    sun_    .tex_.init(GL_TEXTURE0, GL_TEXTURE_2D, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR, GL_REPEAT);
    mercury_.tex_.init(GL_TEXTURE0, GL_TEXTURE_2D, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR, GL_REPEAT);
    venus_  .tex_.init(GL_TEXTURE0, GL_TEXTURE_2D, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR, GL_REPEAT);

    earth_  .tex_.init(GL_TEXTURE0, GL_TEXTURE_2D, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR, GL_REPEAT);
    earth_.night_.init(GL_TEXTURE1, GL_TEXTURE_2D, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR, GL_REPEAT);
    earth_.cloud_.init(GL_TEXTURE2, GL_TEXTURE_2D, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR, GL_REPEAT);
    earth_.gloss_.init(GL_TEXTURE3, GL_TEXTURE_2D, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR, GL_REPEAT);

    moon_   .tex_.init(GL_TEXTURE0, GL_TEXTURE_2D, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR, GL_REPEAT);
    mars_   .tex_.init(GL_TEXTURE0, GL_TEXTURE_2D, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR, GL_REPEAT);
    stars_  .tex_.init(GL_TEXTURE0, GL_TEXTURE_2D, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR, GL_REPEAT);
    ship_   .tex_.init(GL_TEXTURE0, GL_TEXTURE_2D, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR, GL_REPEAT);

    sunglow_.tex_.init(GL_TEXTURE0, GL_TEXTURE_2D, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR, GL_REPEAT);

    // Load/generate textures
    sun_    .tex_.loadPNG(TEXTURE_PATH "/sun.png");
    mercury_.tex_.loadPNG(TEXTURE_PATH "/mercury.png");
    venus_  .tex_.loadPNG(TEXTURE_PATH "/venus.png");

    earth_  .tex_.loadPNG(TEXTURE_PATH "/day.png");
    earth_.night_.loadPNG(TEXTURE_PATH "/night.png");
    earth_.cloud_.loadPNG(TEXTURE_PATH "/clouds.png");
    earth_.gloss_.loadPNG(TEXTURE_PATH "/gloss.png");

    moon_   .tex_.loadPNG(TEXTURE_PATH "/moon.png");
    mars_   .tex_.loadPNG(TEXTURE_PATH "/mars.png");
    stars_  .tex_.loadPNG(TEXTURE_PATH "/stars2.png");

    ship_.     load_model(TEXTURE_PATH "/spaceship.off");
    ship_   .tex_.loadPNG(TEXTURE_PATH "/ship.png");

    sunglow_.tex_.createSunBillboardTexture();

    // setup shaders
    color_shader_.load(SHADER_PATH "/color.vert", SHADER_PATH "/color.frag");
    phong_shader_.load(SHADER_PATH "/phong.vert", SHADER_PATH "/phong.frag");
    earth_shader_.load(SHADER_PATH "/earth.vert", SHADER_PATH "/earth.frag");
      sun_shader_.load(SHADER_PATH   "/sun.vert", SHADER_PATH   "/sun.frag");

    solid_color_shader_.load(SHADER_PATH "/solid_color.vert", SHADER_PATH "/solid_color.frag");

    ship_path_renderer_.initialize();
    ship_path_cp_renderer_.initialize();
    ship_path_frame_.initialize();

    ship_path_.set_control_polygon(control_polygon_, true);
    ship_path_renderer_.sample(ship_path_);
    ship_path_cp_renderer_.setPoints(ship_path_.bezier_control_points());
}
//-----------------------------------------------------------------------------


void Solar_viewer::paint()
{
    // clear framebuffer and depth buffer first
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    vec4     eye = vec4(0,0,0,1);
    vec4      up = vec4(0,1,0,0);
    vec4  center;

    if (in_ship_) {

        center = ship_.pos_;
        mat4 translate_system_matrix = mat4::translate(vec3(center));

        // We translate the camera slightly aboove the ship (one radius above)
        mat4 translate_camera_matrix = mat4::translate(
          vec3(0,SCALING_SHIP_RADIUS_FACTOR
            * ship_.radius_,-dist_factor_
            * SCALING_SHIP_RADIUS_FACTOR * ship_.radius_));

        mat4 rotate_y_matrix = mat4::rotate_y(y_angle_ + ship_.angle_);
        eye = translate_system_matrix * (rotate_y_matrix * (translate_camera_matrix * eye));

        billboard_x_angle_ = 0;
        billboard_y_angle_ = y_angle_ + ship_.angle_;

    } else {

        center = planet_to_look_at_->pos_;
        float radius = planet_to_look_at_->radius_;

        mat4 translate_system_matrix = mat4::translate(vec3(center));
        mat4 translate_camera_matrix = mat4::translate(vec3(0,0,dist_factor_ * radius));
        mat4 rotate_x_matrix = mat4::rotate_x(x_angle_);
        mat4 rotate_y_matrix = mat4::rotate_y(y_angle_);
        up = rotate_y_matrix * rotate_x_matrix * up;
        eye = translate_system_matrix * (rotate_y_matrix * (rotate_x_matrix * (translate_camera_matrix * eye)));

        billboard_x_angle_ = x_angle_;
        billboard_y_angle_ = y_angle_;
    }

    mat4 view = mat4::look_at(vec3(eye), vec3(center), vec3(up));

    /** \todo Orient the billboard used to display the sun's glow
     *  Update billboard_x_andle_ and billboard_y_angle_ so that the billboard plane
     *  drawn to produce the sun's halo is orthogonal to the view vector for
     *  the sun's center.
     */

    mat4 projection = mat4::perspective(fovy_, (float)width_/(float)height_, near_, far_);
    draw_scene(projection, view);
}


//-----------------------------------------------------------------------------


void Solar_viewer::draw_scene(mat4& _projection, mat4& _view)
{
    switch (curve_display_mode_) {
        case CURVE_SHOW_PATH_FRAME:
            ship_path_frame_.draw(solid_color_shader_, _projection * _view, ship_path_(ship_path_param_));
        case CURVE_SHOW_PATH_CP:
            solid_color_shader_.use();
            solid_color_shader_.set_uniform("modelview_projection_matrix", _projection * _view);
            solid_color_shader_.set_uniform("color", vec4(0.8, 0.8, 0.8, 1.0));
            ship_path_cp_renderer_.draw();
        case CURVE_SHOW_PATH:
            solid_color_shader_.use();
            solid_color_shader_.set_uniform("modelview_projection_matrix", _projection * _view);
            solid_color_shader_.set_uniform("color", vec4(1.0, 0.0, 0.0, 1.0));
            ship_path_renderer_.draw();
        default:
            break;
    }

    // the matrices we need: model, modelview, modelview-projection, normal
    mat4 m_matrix;
    mat4 mv_matrix;
    mat4 mvp_matrix;
    mat3 n_matrix;

    // the sun is centered at the origin and -- for lighting -- considered to be a point, so that is the light position in world coordinates
    vec4 light = vec4(0.0, 0.0, 0.0, 1.0); //in world coordinates
    // convert light into camera coordinates
    light = _view * light;

    static float sun_animation_time = 0;
    if (timer_active_) sun_animation_time += 0.01f;

    // ---------- DRAW THE SUN SHADED OBJECTS ---------- //

    sun_shader_.use();

    // render sun
    m_matrix   = mat4::rotate_y(sun_.angle_self_) * mat4::scale(sun_.radius_);
    mv_matrix  = _view * m_matrix;
    mvp_matrix = _projection * mv_matrix;
    sun_shader_.set_uniform("modelview_projection_matrix", mvp_matrix);
    sun_shader_.set_uniform("t", sun_animation_time, true /* Indicate that time parameter is optional;
                                                             it may be optimized away by the GLSL    compiler if it's unused. */);
    sun_shader_.set_uniform("tex", 0);
    sun_shader_.set_uniform("greyscale", (int)greyscale_);
    sun_shader_.set_uniform("radius", sun_.radius_);
    sun_.tex_.bind();
    unit_sphere_.draw();

    sun_shader_.disable();

    // ---------- DRAW THE EARTH SHADED OBJECTS ---------- //

    earth_shader_.use();

    // render earth
    m_matrix   = mat4::translate(vec3(earth_.pos_)) * mat4::rotate_y(earth_.angle_self_) * mat4::scale(earth_.radius_);
    mv_matrix  = _view * m_matrix;
    mvp_matrix = _projection * mv_matrix;
    earth_shader_.set_uniform("light_position", light);

    earth_shader_.set_uniform("modelview_projection_matrix", mvp_matrix);
    earth_shader_.set_uniform("modelview_matrix", mv_matrix);
    earth_shader_.set_uniform("normal_matrix", transpose(inverse(mv_matrix)));

    //bind all earth textures
    earth_shader_.set_uniform("day_texture",   0);
    earth_shader_.set_uniform("night_texture", 1);
    earth_shader_.set_uniform("cloud_texture", 2);
    earth_shader_.set_uniform("gloss_texture", 3);

    earth_shader_.set_uniform("greyscale", (int)greyscale_);

    earth_.tex_.bind();
    earth_.night_.bind();
    earth_.cloud_.bind();
    earth_.gloss_.bind();

    unit_sphere_.draw();

    earth_shader_.disable();

    // ---------- DRAW THE PHONG SHADED OBJECTS ---------- //

    phong_shader_.use();
    // Set the uniform value of "tex", "grayscale" and "light_position" once for all the phong shaded objects
    phong_shader_.set_uniform("light_position", light);
    phong_shader_.set_uniform("tex", 0);
    phong_shader_.set_uniform("greyscale", (int)greyscale_);

    // render mercury
    m_matrix   = mat4::translate(vec3(mercury_.pos_)) * mat4::rotate_y(mercury_.angle_self_) * mat4::scale(mercury_.radius_);
    mv_matrix  = _view * m_matrix;
    mvp_matrix = _projection * mv_matrix;
    phong_shader_.set_uniform("modelview_projection_matrix", mvp_matrix);
    phong_shader_.set_uniform("modelview_matrix", mv_matrix);
    phong_shader_.set_uniform("normal_matrix", transpose(inverse(mv_matrix)));
    mercury_.tex_.bind();
    unit_sphere_.draw();

    // render venus
    m_matrix   = mat4::translate(vec3(venus_.pos_)) * mat4::rotate_y(venus_.angle_self_) * mat4::scale(venus_.radius_);
    mv_matrix  = _view * m_matrix;
    mvp_matrix = _projection * mv_matrix;
    phong_shader_.set_uniform("modelview_projection_matrix", mvp_matrix);
    phong_shader_.set_uniform("modelview_matrix", mv_matrix);
    phong_shader_.set_uniform("normal_matrix", transpose(inverse(mv_matrix)));
    venus_.tex_.bind();
    unit_sphere_.draw();

    // render mars
    m_matrix   = mat4::translate(vec3(mars_.pos_)) * mat4::rotate_y(mars_.angle_self_) * mat4::scale(mars_.radius_);
    mv_matrix  = _view * m_matrix;
    mvp_matrix = _projection * mv_matrix;
    phong_shader_.set_uniform("modelview_projection_matrix", mvp_matrix);
    phong_shader_.set_uniform("modelview_matrix", mv_matrix);
    phong_shader_.set_uniform("normal_matrix", transpose(inverse(mv_matrix)));
    mars_.tex_.bind();
    unit_sphere_.draw();

    // render moon
    m_matrix   = mat4::translate(vec3(moon_.pos_)) * mat4::rotate_y(moon_.angle_self_) * mat4::scale(moon_.radius_);
    mv_matrix  = _view * m_matrix;
    mvp_matrix = _projection * mv_matrix;
    phong_shader_.set_uniform("modelview_projection_matrix", mvp_matrix);
    phong_shader_.set_uniform("modelview_matrix", mv_matrix);
    phong_shader_.set_uniform("normal_matrix", transpose(inverse(mv_matrix)));
    moon_.tex_.bind();
    unit_sphere_.draw();

    // render ship
    m_matrix   = mat4::translate(vec3(ship_.pos_)) * mat4::rotate_y(ship_.angle_) * mat4::scale(ship_.radius_);
    mv_matrix  = _view * m_matrix;
    mvp_matrix = _projection * mv_matrix;
    phong_shader_.set_uniform("modelview_projection_matrix", mvp_matrix);
    phong_shader_.set_uniform("modelview_matrix", mv_matrix);
    phong_shader_.set_uniform("normal_matrix", transpose(inverse(mv_matrix)));
    ship_.tex_.bind();
    ship_.draw();

    phong_shader_.disable();


    // ---------- DRAW THE COLOR SHADED OBJECTS ---------- //

    color_shader_.use();

    // render stars background
    m_matrix   = mat4::scale(stars_.radius_);
    mv_matrix  = _view * m_matrix;
    mvp_matrix = _projection * mv_matrix;
    color_shader_.set_uniform("modelview_projection_matrix", mvp_matrix);
    stars_.tex_.bind();
    unit_sphere_.draw();

    /** \todo Switch from using color_shader_ to the fancier shaders you'll
     * implement in this assignment:
     *      mercury, venus, moon, mars, ship: phong_shader_
     *      earth: earth_shader_
     *      stars, sunglow: still use color_shader_
     *  You'll need to make sure all the GLSL uniform variables are set. For
     *  Phong shading, you need to pass in the modelview matrix, the normal transformation
     *  matrix, and light position in addition to the color_shader_ parameters.
     */

    /** \todo Render the sun's halo here using the "color_shader_"
    *   - Construct a model matrix that scales the billboard to 3 times the
    *     sun's radius and orients it according to billboard_x_angle_ and
    *     billboard_y_angle_
    *   - Bind the texture for and draw sunglow_
    **/

    // render the sun billboard
    m_matrix   = mat4::rotate_y(billboard_y_angle_)*mat4::rotate_x(billboard_x_angle_)*mat4::scale(3*sun_.radius_);
    mv_matrix  = _view * m_matrix;
    mvp_matrix = _projection * mv_matrix;
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    color_shader_.set_uniform("modelview_projection_matrix", mvp_matrix);
    sunglow_.tex_.bind();
    sunglow_.draw();
    glDisable(GL_BLEND);

    color_shader_.disable();


    // check for OpenGL errors
    glCheckError();
}

void Solar_viewer::randomize_planets()
{
    std::cout << "Randomizing planets..." << std::endl;
    float temp_dt = time_step_;
    time_step_ = (float)(rand()%20000);
    timer();
    time_step_ = temp_dt;
}


//=============================================================================
