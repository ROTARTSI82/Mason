//
// Created by Grant on 9/27/19.
//

#pragma once

#ifndef __MASON_VERTEX_BUFFER_H
#define __MASON_VERTEX_BUFFER_H

#include "mason/gl/gl_core.h"
#include "mason/gl/vertex_data.h"

#include <vector>

namespace mason::gl {
    class vertex_buffer {
    public:
        GLuint id = 0;

        vertex_buffer(GLsizeiptr size, const GLvoid *data, GLenum usage);

        explicit vertex_buffer(const std::vector<float> &buffer_data);

        ~vertex_buffer();

        void bind();
    };

    std::vector<float> pack_vertex_data(const std::vector<vertex_data> &data);
}

#endif //__MASON_VERTEX_BUFFER_H
