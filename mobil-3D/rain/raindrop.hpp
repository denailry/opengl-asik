#ifndef RAINDROP_HPP
#define RAINDROP_HPP

#include <glm/glm.hpp>
#include <stdlib.h>
#include <time.h>

class RainDrop {
private:
    glm::vec3 offset;
public: 
    RainDrop(float x, float z) {
        offset = glm::vec3(x, 0.0, z);
    }

    void move() {
        offset += glm::vec3(0.0, -0.01, 0.0);
    }

    glm::vec3 getOffset() const {
        return offset;
    }
};

#endif