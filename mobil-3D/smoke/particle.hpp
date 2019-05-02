#ifndef PARTICLE_HPP
#define PARTICLE_HPP

#include <glm/glm.hpp>
#include <stdlib.h>
#include <time.h>

class Particle {
private:
    glm::vec3 offset;
public: 
    Particle(float x, float y, float z) {
        offset = glm::vec3(x, y, z);
    }

    void move() {
        offset += glm::vec3(0.0, 0.01, -0.01);
    }

    glm::vec3 getOffset() const {
        return offset;
    }
};

#endif