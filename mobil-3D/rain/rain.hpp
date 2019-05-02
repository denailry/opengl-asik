#ifndef RAIN_HPP
#define RAIN_HPP

#include <glm/glm.hpp>
#include <vector>
#include <stdlib.h>
#include <time.h>
#include "raindrop.hpp"

const float RAIN_X_OFFSET = 2;
const float RAIN_Z_OFFSET = 2;
const float RAIN_Y_OFFSET = 4;
const float RAIN_WIDTH = 0.005;
const float RAIN_HEIGHT = 0.1;

class Rain {
private:
    std::vector<RainDrop> raindrops;
    int rainSize;
    int area;
public: 
    Rain(int rainSize, int area) {
        srand (time(NULL));
        this->rainSize = rainSize;
        this->area = area;
    }

    void update() {
        std::vector<RainDrop> newRainDrops;

        for (RainDrop &raindrop : raindrops) {
            if (raindrop.getOffset().y > -5.0) {
                raindrop.move();
                newRainDrops.push_back(raindrop);
            }
        }

        if (newRainDrops.size() < this->rainSize) {
            int x = rand() % 100 + 1;
            if (x <= 50) {
                newRainDrops.push_back(generateRain());
            }
        }
        
        this->raindrops = newRainDrops;
    }

    std::vector<RainDrop> getRainDrops() const {
        return this->raindrops;
    }

    RainDrop generateRain() {
        float x = ((float) (rand() % (this->area * 1000))) / 1000.0 - ((float) this->area) + RAIN_X_OFFSET;
        float z = ((float) (rand() % (this->area * 1000))) / 1000.0 - ((float) this->area) + RAIN_Y_OFFSET;
        return RainDrop(x, z);
    }
};

#endif