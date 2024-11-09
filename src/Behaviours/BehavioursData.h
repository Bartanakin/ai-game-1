//
// Created by bartanakin on 10/25/24.
//

#pragma once
#include <Geometrics/Vector2f.h>

namespace Behaviours {
struct BehaviourData {
    BehaviourData() = default;
    // obstacle avoidance
    float minDetectionBoxLength;
    float maxSpeed;
    float detectionBoxWidth;

    // wander
    float wanderRadius;
    float wanderDistance;
    float wanderJitter;
    Barta::Vector2f wanderTarget;

    // delay
    float accelerationDelay;
};
}
