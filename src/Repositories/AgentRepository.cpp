//
// Created by bartanakin on 10/12/24.
//

#include "AgentRepository.h"
#include <Graphics/SFML_GraphicsBridge.h>
#include <Graphics/SpriteBuilder/RectangleWithColorsSpriteBuilder.h>
#include <Graphics/SpriteBuilder/SpriteMerger.h>
#include <Graphics/SpriteBuilder/TriangleSprite.h>
#include <Hitbox/AABB_Hitbox.h>
#include <Hitbox/CircleHitbox.h>

AgentRepository::AgentRepository(
    ListManager& listManager,
    Barta::ObjectManagerInterface& objectManager
) noexcept:
    listManager(listManager),
    objectManager(objectManager) {}

Player* AgentRepository::addNewPlayer() noexcept {
    auto player = new Player(
        {
            Barta::SFML_GraphicsBridge::createNewTransformableInstance(),
            {},
            4
    },
        std::unique_ptr<Barta::HitboxInterface>(new Barta::CircleHitbox({8.f, {10.f, 14.f}})),
        {{}, false, 1.f, {}, 0.f, {10.f, 16.f}},

        {Barta::SFML_GraphicsBridge::createNewTransformableInstance(), {}, 4}
    );

    this->listManager.addObject(player);
    this->objectManager.addGraphicsObject(player);
    this->objectManager.addDynamicsObject(player);
    this->objectManager.addNewObject(player);

    return player;
}

Wall* AgentRepository::addNewBoundingWall(
    Barta::Vector2f size,
    Barta::Color color,
    bool infiniteMass
) noexcept {
    auto spriteBuilder = Barta::RectangleWithColorsSpriteBuilder();
    spriteBuilder.setVertex1({0.f, 0.f});
    spriteBuilder.setSize(size);
    spriteBuilder.setAllColors(color);
    auto merger = Barta::SpriteMerger();
    merger.addRectangleWithColors(spriteBuilder.build());
    auto aabb = new Wall(
        {
            Barta::SFML_GraphicsBridge::createNewTransformableInstance(),
            merger.merge(false),
            4
    },
        std::unique_ptr<Barta::HitboxInterface>(new Barta::AABB_Hitbox({{0.f, 0.f}, size})),
        {{0., 0.}, infiniteMass, infiniteMass ? 0.f : 1.f}
    );

    this->listManager.addObject(aabb);
    this->objectManager.addGraphicsObject(aabb);
    this->objectManager.addDynamicsObject(aabb);
    this->objectManager.addNewObject(aabb);

    return aabb;
}

Wall* AgentRepository::addNewWall(
    float radius,
    Barta::Vector2f position
) noexcept {
    auto circle = Barta::Circle{
        radius,
        {radius, radius}
    };
    auto merger = Barta::SpriteMerger();
    merger.addCircleSprite({
        {radius, {radius, radius}},
        {28, 25, 181, 255}
    });
    Barta::DynamicsDTO dynamics = {{}};
    dynamics.hasInfiniteMass = true;
    dynamics.massCenter = {radius, radius};
    auto wall = new Wall(
        {Barta::SFML_GraphicsBridge::createNewTransformableInstance(), merger.merge(false), 4},
        std::unique_ptr<Barta::HitboxInterface>(new Barta::CircleHitbox(circle)),
        dynamics
    );

    wall->move(position);

    this->listManager.addObject(wall);
    this->objectManager.addGraphicsObject(wall);
    this->objectManager.addDynamicsObject(wall);
    this->objectManager.addNewObject(wall);

    return wall;
}

Enemy* AgentRepository::addNewEnemy(
    Barta::Vector2f position,
    std::random_device& randomDevice
) noexcept {
    constexpr float ENEMY_RADIUS = 8.f;
    auto circle = Barta::Circle{
        ENEMY_RADIUS,
        {ENEMY_RADIUS, ENEMY_RADIUS}
    };
    auto merger = Barta::SpriteMerger();
    merger.addCircleSprite({
        {ENEMY_RADIUS, {ENEMY_RADIUS, ENEMY_RADIUS}},
        {255, 0, 0, 255}
    });
    Behaviours::BehaviourData behaviourData{};
    behaviourData.wander.distance = 20.f;
    behaviourData.wander.jitter = 10.f;
    behaviourData.wander.radius = 20.f;
    behaviourData.wander.target = {};
    behaviourData.obstacleAvoidance.minDetectionBoxWidth = 2.f * ENEMY_RADIUS;
    behaviourData.obstacleAvoidance.additionalDetectionBoxWidth = ENEMY_RADIUS + 0.5f;
    behaviourData.obstacleAvoidance.minDetectionBoxLength = 10.f;
    behaviourData.obstacleAvoidance.additionalDetectionBoxLength = 40.f;
    behaviourData.hide.distanceFromBoundary = 30.f;
    behaviourData.groupBehaviours.neighborhoodRadius = 80.f;
    behaviourData.groupBehaviours.cohesionCoefficient = 0.3f;
    behaviourData.groupBehaviours.alignmentCoefficient = 2.f;
    behaviourData.groupBehaviours.separationCoefficient = 1.f;
    behaviourData.groupBehaviours.minimalSeparationDistance = 2 * ENEMY_RADIUS + 5.f;
    behaviourData.maxSpeed = Enemy::MAX_SPEED;
    behaviourData.accelerationDelay = .5f;
    std::default_random_engine engine(randomDevice());
    auto enemy = new Enemy(
        {
            Barta::SFML_GraphicsBridge::createNewTransformableInstance(),
            merger.merge(false),
            4
    },
        std::unique_ptr<Barta::HitboxInterface>(new Barta::CircleHitbox(circle)),
        {Barta::Vector2f(Enemy::MAX_SPEED, 0.f).rotated(std::uniform_real_distribution<float>(0.f, 2.f * M_PI)(engine)),
         false,
         1.f,
         {},
         0.f,
         {ENEMY_RADIUS, ENEMY_RADIUS}},
        behaviourData,
        circle
    );

    enemy->move(position);

    this->listManager.addObject(enemy);
    this->objectManager.addGraphicsObject(enemy);
    this->objectManager.addDynamicsObject(enemy);
    this->objectManager.addNewObject(enemy);

    return enemy;
}
