//
// Created by Grant on 9/27/19.
//

#pragma once

#ifndef __MASON_SHADER_PROGRAM_H
#define __MASON_SHADER_PROGRAM_H

#include "mason/gl/gl_core.h"

#include <unordered_map>
#include <fstream>
#include <sstream>

#include <algorithm>

#include "glm/glm.hpp"

namespace mason::gl {

    GLuint compile_shader(const std::string &type, const std::string &src, const std::string &full_path);

    class shader_program {
    public:
        std::unordered_map<std::string, GLint> uniform_cache;

        GLuint id = 0;

        explicit shader_program(const std::string &path);

        explicit shader_program(std::unordered_map<std::string, std::string> shaders);

        ~shader_program();

        GLint get_uniform_location(const std::string &name);

        void set_uniform_3f(const std::string &name, float f1, float f2, float f3);

        void set_uniform_4f(const std::string &name, float f1, float f2, float f3, float f4);

        void set_uniform_mat4fv(const std::string &name, glm::mat4 &mat, GLboolean transpose = GL_FALSE);

        void set_uniform_1i(const std::string &name, int i);

        void bind();
    };

}


#endif //__MASON_SHADER_PROGRAM_H
