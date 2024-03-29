//
// Created by Grant on 2019-09-03.
//

#pragma once

#ifndef MASON_MASON_H
#define MASON_MASON_H

#include <chrono>

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtx/euler_angles.hpp"

#include "mason/log.h"

namespace mason {

    class transform_info {
    public:
        glm::vec3 position;
        glm::vec3 rotation;
        glm::vec3 scale;

        glm::mat4 transforms;
        glm::vec3 up, right, forward;

        explicit transform_info(glm::vec3 pos = glm::vec3(0), glm::vec3 rot = glm::vec3(0), glm::vec3 scale = glm::vec3(1));

        void update_transforms();
    };
}

#endif //MASON_MASON_H
