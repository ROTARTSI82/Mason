//
// Created by Grant on 9/26/19.
//


#include "mason/gl/gl_window.h"

namespace mason::gl {

    gl_window::gl_window(const int &w, const int &h, const char *title) {
        init_glfw();
        win = glfwCreateWindow(w, h, title, nullptr, nullptr);
        if (!win) {
            glfwTerminate();
            MASON_CRITICAL("Failed to create GLFW context! This WILL crash!");
            return;
        }

        bind();

        init_glew();
        init_gl();
    }

    void gl_window::bind() {
        glfwMakeContextCurrent(win);
    }

    gl_window::~gl_window() {
        glfwDestroyWindow(win);
    }

    void gl_window::clear() {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
    }

    void gl_window::flip() {
        glfwSwapBuffers(win);
        glfwPollEvents();
    }

    bool gl_window::poll_close() {
        return glfwWindowShouldClose(win);
    }
}

