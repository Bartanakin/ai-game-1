//
// Created by bartanakin on 10/25/24.
//

#pragma once
#include <Geometrics/Vector2f.h>

namespace Behaviours {
struct BehaviourData {
    BehaviourData() = default;

    struct ObstacleAvoidance {
        float minDetectionBoxLength;
        float additionalDetectionBoxLength;
        float minDetectionBoxWidth;
        float additionalDetectionBoxWidth;
    };

    struct Wander {
        float radius;
        float distance;
        float jitter;
        Barta::Vector2f target;
    };

    struct Hide {
        float distanceFromBoundary;
    };

    struct GroupBehaviours {
        float neighborhoodRadius;
        float cohesionCoefficient;
        float separationCoefficient;
        float minimalSeparationDistance;
        float alignmentCoefficient;
    };

    ObstacleAvoidance obstacleAvoidance;
    Wander wander;
    Hide hide;
    GroupBehaviours groupBehaviours;

    float maxSpeed;
    float accelerationDelay;
};
}
