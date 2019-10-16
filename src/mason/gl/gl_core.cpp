//
// Created by Grant on 9/26/19.
//

#include "mason/gl/gl_core.h"

namespace mason::gl {
    void (*quit)() = &glfwTerminate;

    void init_glfw() {
        if (!glfwInit()) {
            MASON_CRITICAL("Failed to init GLFW! This WILL crash!");
        }
    }

    void init_glew() {
        if (glewInit() != GLEW_OK) {
            MASON_CRITICAL("Failed to init GLEW! This WILL crash!");
        }
    }

    void init_gl() {
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glBlendEquation(GL_ADD);

        glEnable(GL_DEPTH_TEST);
        glDepthFunc(GL_LESS);

        glEnable(GL_CULL_FACE);
        glCullFace(GL_BACK);
        glFrontFace(GL_CCW);

        glEnable(GL_STENCIL_TEST);
        glStencilMask(0x00);  // Everything gets written as-is
        glStencilFunc(GL_ALWAYS, 0, 0x00);  // Everything passes
        glStencilOp(GL_KEEP, GL_KEEP, GL_KEEP);  // Keep everything
    }

#ifdef MASON_DEBUG_MODE

    void handle_single_error(const std::string &msg) {
        GLenum err = glGetError();
        if (err != GL_NO_ERROR) {
            MASON_WARN("[** OPENGL ERROR {} **]: {}", err, msg);
        }
    }

    void flush_errors(const std::string &msg) {
        GLenum err = glGetError();
        while (err != GL_NO_ERROR) {
            MASON_WARN("[** OPENGL ERROR {} **]: {}", err, msg);
            err = glGetError();
        }
    }

#else
    void handle_single_error(const std::string &msg) {}
    void flush_errors(const std::string &msg) {}
#endif
}
