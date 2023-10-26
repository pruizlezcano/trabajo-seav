#include "utils.h"

float Utils::calculateShootPower(unsigned long startTime) {
    // TODO: habra que probar mucho cambiando estos valores hasta encontrar un valor optimo
    float maxShootPower = 20;
    float powerFactor = 10;
    
    float durationInSeconds = (ofGetElapsedTimeMillis() - startTime) / 1000.0;
    
    float shotPower = powerFactor * durationInSeconds;
    
    if (shotPower > maxShootPower) {
        return maxShootPower;
    }
    
    return shotPower;
}
