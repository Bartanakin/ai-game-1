//
// Created by bartanakin on 11/2/24.
//

#include "Hide.h"

Behaviours::Hide::Hide(
    const Barta::Vector2f& hunterPosition,
    const std::vector<Barta::HitboxAware*>& obstacles
):
    hunterPosition(hunterPosition),
    obstacles(obstacles) {}

Barta::Vector2f Behaviours::Hide::changeBehaviour(
    BehavioursDataAwareInterface& behaviourDataAware,
    float deltaTime
) const {}
