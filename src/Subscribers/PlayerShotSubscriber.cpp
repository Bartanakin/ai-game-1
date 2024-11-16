//
// Created by bartanakin on 11/15/24.
//

#include "Graphics/GraphicsDataTransformer.h"
#include "PlayerShotSubscriber.h"

PlayerShotSubscriber::PlayerShotSubscriber(
    Player& player,
    EnemyList& enemyList,
    WallList& wallList
) noexcept:
    player(player),
    enemyList(enemyList),
    wallList(wallList) {}

bool PlayerShotSubscriber::handle(
    Barta::LeftClickEvent& event
) {
    if (!this->player.tryToShoot()) {
        return false;
    }

    auto hitEnemy_ptr = this->getClosestTarget().second;

    if (hitEnemy_ptr == nullptr) {
        return false;
    }

    hitEnemy_ptr->receiveShot();

    return false;
}

bool PlayerShotSubscriber::handle(
    PlayerMarkerChangeEvent& event
) {
    if (event.player->isToBeDeleted()) {
        return true;
    }

    Barta::Color color;
    if (Player::RELOAD_TIME > std::chrono::steady_clock::now() - event.player->getLastShotTime()) {
        color = {161, 3, 50};
    } else {
        color = {255, 255, 255};
    }

    auto closestTarget = this->getClosestTarget();
    if (closestTarget.second == nullptr) {
        event.player->setMarker(Barta::GraphicsDataTransformer(color).fromOBB({{}, {}, 0.f}));

        return false;
    }

    auto radians = -closestTarget.first.direction.angleTo();
    constexpr float RAY_HEIGHT = 3.f;
    auto rotateTranslation = Barta::Vector2f{0.f, -0.5f * RAY_HEIGHT}.rotated(radians);
    auto obb = Barta::OBB(closestTarget.first.origin + rotateTranslation, {closestTarget.first.direction.length(), RAY_HEIGHT}, radians);
    event.player->setMarker(Barta::GraphicsDataTransformer(color).fromOBB(obb));

    return false;
}

bool PlayerShotSubscriber::isValid() const noexcept {
    return !player.isToBeDeleted();
}

std::pair<Barta::Ray, Enemy*> PlayerShotSubscriber::getClosestTarget() const {
    auto closestParam = std::numeric_limits<float>::max();
    Enemy* hitEnemy_ptr = nullptr;
    Barta::Ray trajectory{player.getCurrentDynamicsData().massCenter, player.getDirection()};
    for (auto wall_ptr: this->wallList) {
        if (wall_ptr->isToBeDeleted()) {
            continue;
        }

        for (const auto intersectionParam: wall_ptr->getHitbox()->intersectsWithRay(trajectory)) {
            if (intersectionParam < closestParam) {
                closestParam = intersectionParam;
                hitEnemy_ptr = nullptr;
            }
        }
    }

    for (auto enemy_ptr: this->enemyList) {
        if (enemy_ptr->isToBeDeleted()) {
            continue;
        }

        for (const auto intersectionParam: enemy_ptr->getHitbox()->intersectsWithRay(trajectory)) {
            if (intersectionParam < closestParam) {
                closestParam = intersectionParam;
                hitEnemy_ptr = enemy_ptr;
            }
        }
    }

    return {
        {trajectory.origin, trajectory.direction * closestParam},
        hitEnemy_ptr
    };
}
