#include <iostream>
#include "math.h"

#include "mason/app_node.h"
#include "mason/gl/gl_window.h"
#include "mason/gl/shader_program.h"
#include "mason/gl/vertex_buffer.h"
#include "mason/gl/index_buffer.h"
#include "mason/gl/vertex_array.h"
#include "mason/gl/vb_layout.h"
#include "mason/gl/texture2d.h"
#include "mason/camera.h"

#include "mason/al/al_context.h"
#include "mason/al/al_device.h"
#include "mason/al/al_listener.h"
#include "mason/al/al_core.h"
#include "mason/al/al_buffer.h"
#include "mason/al/al_source.h"

#include <chrono>

mason::gl::gl_window *win;
mason::camera *cam;

bool w, a, s, d, up, down, left, right, space, shift;

class custom_layer : public mason::layer {
public:
    int x;
    bool parState;

    custom_layer(int id, bool ps) : x(id), parState(ps) {};

    void on_attach() {
        std::cout << "Layer " << x << " was attached!" << std::endl;
    }

    void on_detach() {
        std::cout << "Layer " << x << " was detached!" << std::endl;
    }

    void on_update(int thread);

    bool on_event(mason::gl::gl_event *ev) {
        if (ev->type == mason::gl::key) {
            mason::gl::gl_key_event *k = reinterpret_cast<mason::gl::gl_key_event *>(ev);
            if (k->action == GLFW_PRESS) {
                if (k->scancode == glfwGetKeyScancode(GLFW_KEY_SPACE)) {
                    space = true;
                }
                if (k->scancode == glfwGetKeyScancode(GLFW_KEY_LEFT_SHIFT)) {
                    shift = true;
                }
                if (k->scancode == glfwGetKeyScancode(GLFW_KEY_UP)) {
                    up = true;
                }
                if (k->scancode == glfwGetKeyScancode(GLFW_KEY_DOWN)) {
                    down = true;
                }
                if (k->scancode == glfwGetKeyScancode(GLFW_KEY_LEFT)) {
                    left = true;
                }
                if (k->scancode == glfwGetKeyScancode(GLFW_KEY_RIGHT)) {
                    right = true;
                }

                if (k->scancode == glfwGetKeyScancode(GLFW_KEY_A)) {
                    a = true;
                }
                if (k->scancode == glfwGetKeyScancode(GLFW_KEY_W)) {
                    w = true;
                }
                if (k->scancode == glfwGetKeyScancode(GLFW_KEY_S)) {
                    s = true;
                }
                if (k->scancode == glfwGetKeyScancode(GLFW_KEY_D)) {
                    d = true;
                }
            }

            if (k->action == GLFW_RELEASE) {
                if (k->scancode == glfwGetKeyScancode(GLFW_KEY_SPACE)) {
                    space = false;
                }
                if (k->scancode == glfwGetKeyScancode(GLFW_KEY_LEFT_SHIFT)) {
                    shift = false;
                }
                if (k->scancode == glfwGetKeyScancode(GLFW_KEY_UP)) {
                    up = false;
                }
                if (k->scancode == glfwGetKeyScancode(GLFW_KEY_DOWN)) {
                    down = false;
                }
                if (k->scancode == glfwGetKeyScancode(GLFW_KEY_LEFT)) {
                    left = false;
                }
                if (k->scancode == glfwGetKeyScancode(GLFW_KEY_RIGHT)) {
                    right = false;
                }

                if (k->scancode == glfwGetKeyScancode(GLFW_KEY_A)) {
                    a = false;
                }
                if (k->scancode == glfwGetKeyScancode(GLFW_KEY_W)) {
                    w = false;
                }
                if (k->scancode == glfwGetKeyScancode(GLFW_KEY_S)) {
                    s = false;
                }
                if (k->scancode == glfwGetKeyScancode(GLFW_KEY_D)) {
                    d = false;
                }
            }
        }
//        MASON_INFO("Got event!");
        return false;
    }
};

class custom_app : public mason::app_node {
public:
    bool s;

    custom_app(bool x) : s(x) {}

    void on_activate() {
        std::cout << "app was activated!" << std::endl;
    };

    void on_deactivate() {
        std::cout << "app was deactivated!" << std::endl;
    };
};

void custom_layer::on_update(int thread) {
    win->clear();
}

int main() {
    mason::init_logging(true);

    mason::al::update_default_device();
    mason::al::al_context al_cont(mason::al::default_device->dev_obj);
    al_cont.bind();

    mason::al::al_listener::set_orientation({0, 0, 1}, {0, 1, 0});
    mason::al::al_listener::set_position({0, 0, 0});
    mason::al::al_listener::set_velocity({0, 0, 0});

    mason::al::al_buffer al_buf("/Users/25granty/Documents/chicken.ogg");
    mason::al::al_source asrc = mason::al::al_source();
    asrc.bind_buffer(&al_buf);
    asrc.set_gain(1);
    asrc.set_looping(true);
    asrc.set_pitch(1);
    asrc.set_velocity({0, 0, 0});
    asrc.set_position({0, 0, 0});
    asrc.play();

    MASON_FATAL("Hello World! This is an SPDLOG test!");
    win = new mason::gl::gl_window();
    custom_app *app = new custom_app(false);
    mason::gl::event_handler::add_event_subscriber(app);
    cam = new mason::camera(640, 480);

    float x = 1.0f;
    float pos[] = {
            -x, x, x, 0, 0, // 0
            x, x, x, 1, 0, // 1
            x, -x, x, 1, 1, //2
            -x, -x, x, 0, 1, // 3

            -x, x, -x, 0, 0, // 4
            x, x, -x, 1, 0,// 5
            x, -x, -x, 1, 1, // 6
            -x, -x, -x, 0, 1, // 7

            x, -x, x, 0, 1, // 8
            x, x, x, 0, 0, // 9
            x, x, x, 1, 1, // 10
            -x, x, x, 0, 1, // 11
            -x, x, x, 1, 0, // 12
            -x, -x, x, 1, 1, // 13

            -x, -x, x, 0, 0, // 14
            x, -x, x, 1, 0, // 15

    };

//    mason::gl::vertex_array *vao = new mason::gl::vertex_array();
//    vao->bind();


    mason::gl::vertex_buffer *vbo =
            new mason::gl::vertex_buffer(sizeof(pos), &pos, GL_STATIC_DRAW);
    vbo->bind();

    mason::gl::index_buffer *ibo = new mason::gl::index_buffer({3, 2, 1, 0,
                                                                4, 5, 6, 7,

                                                                8, 6, 5,
                                                                9, // (x, x; 0, 0), (x, x; 1, 0), (x, -x; 1, 1), (x, -x; 0, 1)
                                                                11, 10, 5,
                                                                4, // (-x, x, -x);(0, 0), (x, x, -x);(1, 0), (x, x, x);(1, 1), (-x, x, x);(0, 1)
                                                                7, 13, 12, 4, // (-x, x, x);(1, 0), (-x, -x, x);(1, 1);
                                                                7, 6, 15, 14});
    ibo->bind();

    mason::gl::vb_layout lay = mason::gl::vb_layout();
    lay.push_attribute<float>(GL_FLOAT, 3, GL_FALSE);
    lay.push_attribute<float>(GL_FLOAT, 2, GL_FALSE);
    lay.set_attributes();

    mason::image *img = new mason::image("/Users/25granty/Documents/dumbCrap/profile.png");

    mason::gl::texture2d *tex = new mason::gl::texture2d(img);
    tex->bind_slot();
    delete img;

    mason::gl::shader_program *prog = new mason::gl::shader_program(
            "/Users/25granty/Desktop/CLion/Mason/sandbox/res/shader_program");
    prog->bind();
    prog->set_uniform_1i("tex", 0);

    app->push_overlay(new custom_layer(1, false));
    app->on_activate();


    auto last_update = std::chrono::high_resolution_clock::now();

    while (!win->poll_close()) {
        auto now = std::chrono::high_resolution_clock::now();
        auto diff = std::chrono::duration_cast<std::chrono::duration<float>>(now - last_update);
        last_update = now;

        if (d) {
            cam->transforms.position += cam->transforms.right * diff.count() * 10.0f;
            cam->transforms.update_transforms();
        }
        if (w) {
            cam->transforms.position += cam->transforms.forward * diff.count() * 10.0f;
            cam->transforms.update_transforms();
        }
        if (a) {
            cam->transforms.position -= cam->transforms.right * diff.count() * 10.0f;
            cam->transforms.update_transforms();
        }
        if (s) {
            cam->transforms.position -= cam->transforms.forward * diff.count() * 10.0f;
            cam->transforms.update_transforms();
        }

        if (shift) {
            cam->transforms.position -= cam->transforms.up * diff.count() * 10.0f;
            cam->transforms.update_transforms();
        }

        if (space) {
            cam->transforms.position += cam->transforms.up * diff.count() * 10.0f;
            cam->transforms.update_transforms();
        }

        if (up) {
            cam->transforms.rotation.y += 3.14 * diff.count();
            cam->transforms.update_transforms();
        }
        if (down) {
            cam->transforms.rotation.y -= 3.14 * diff.count();
            cam->transforms.update_transforms();
        }
        if (left) {
            cam->transforms.rotation.x += 3.14 * diff.count();
            cam->transforms.update_transforms();
        }
        if (right) {
            cam->transforms.rotation.x -= 3.14 * diff.count();
            cam->transforms.update_transforms();
        }

        int w, h;

        glfwGetWindowSize(win->win, &w, &h);

        cam->width = w;
        cam->height = h;

        mason::gl::event_handler::handle_single_event();
        app->update(1);
        glm::mat4 view, proj;
        view = cam->get_view();
        proj = cam->get_projection();

        prog->set_uniform_mat4fv("proj", proj);
        prog->set_uniform_mat4fv("view", view);

        vbo->bind();
        ibo->bind();
        lay.set_attributes();
        glDrawElements(GL_QUADS, 24, GL_UNSIGNED_INT, nullptr);
        win->flip();

        mason::al::al_listener::set_position(cam->transforms.position);
        mason::al::al_listener::set_orientation(cam->transforms.forward, cam->transforms.up);
    }

    // Proper cleanup routine.
    app->on_deactivate();
    delete app;
    delete ibo;
    delete vbo;
    delete prog;
    delete win;

    mason::gl::quit();

}
