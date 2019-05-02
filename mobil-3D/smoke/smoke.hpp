#ifndef SMOKE_HPP
#define SMOKE_HPP

#include <glm/glm.hpp>
#include <vector>
#include <stdlib.h>
#include <time.h>
#include "particle.hpp"

const float SMOKE_X_OFFSET = 0;
const float SMOKE_Z_OFFSET = -2.5;
const float SMOKE_Y_OFFSET = -3.5;
const float SMOKE_WIDTH = 1.0;
const float SMOKE_HEIGHT = 0.1;

class Smoke {
private:
    std::vector<Particle> particles;
    int rainSize;
    int area;
public: 
    Smoke(int rainSize, int area) {
        srand (time(NULL));
        this->rainSize = rainSize;
        this->area = area;
    }

    void update() {
        std::vector<Particle> newParticles;

        for (Particle &particle : particles) {
            if (particle.getOffset().z > -4.0) {
                particle.move();
                newParticles.push_back(particle);
            }
        }

        if (newParticles.size() < this->rainSize) {
            int x = rand() % 100 + 1;
            if (x <= 50) {
                newParticles.push_back(generateRain());
            }
        }
        
        this->particles = newParticles;
    }

    std::vector<Particle> getParticles() const {
        return this->particles;
    }

    Particle generateRain() {
        // float x = ((float) rand() * 1000.0 / 1000.0) - ((float) this->area) + SMOKE_X_OFFSET;
        // float z = ((float) rand() * 1000.0 / 1000.0) - ((float) this->area) + SMOKE_Y_OFFSET;
        // return Particle(x, z);
        float x = ((float) (rand() % (this->area * 100))) / 1000.0 + SMOKE_X_OFFSET;
        float z = ((float) (rand() % (this->area * 100))) / 1000.0 + SMOKE_Z_OFFSET;
        return Particle(x, SMOKE_Y_OFFSET, z);
    }
};

#endif