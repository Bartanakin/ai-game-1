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
    auto color = Barta::Color(255.f, 255.f, 0.f);
    auto triangleSprite = Barta::TriangleSprite(
        {
            {10.f, 0.f },
            {0.f,  24.f},
            {20.f, 24.f}
    },
        color,
        color,
        color
    );
    auto merger = Barta::SpriteMerger();
    merger.addTriangle(triangleSprite);
    auto player = new Player(
        {
            Barta::SFML_GraphicsBridge::createNewTransformableInstance(),
            merger.merge(false),
            4
    },
        std::unique_ptr<Barta::HitboxInterface>(new Barta::CircleHitbox({8.f, {10.f, 14.f}})),
        {{}, false, 1.f, {}, 0.f, {10.f, 16.f}}
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
    // this->objectManager.addDynamicsObject(aabb);
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
        {50, 191, 66, 255}
    });
    auto wall = new Wall(
        {Barta::SFML_GraphicsBridge::createNewTransformableInstance(), merger.merge(false), 4},
        std::unique_ptr<Barta::HitboxInterface>(new Barta::CircleHitbox(circle)),
        {{}}
    );

    wall->move(position);

    this->listManager.addObject(wall);
    this->objectManager.addGraphicsObject(wall);
    // this->objectManager.addDynamicsObject(wall);
    this->objectManager.addNewObject(wall);

    return wall;
}

Enemy* AgentRepository::addNewEnemy(
    Barta::Vector2f position,
    float velocityAngleRadians
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
    behaviourData.wanderDistance = 20.f;
    behaviourData.wanderJitter = 10.f;
    behaviourData.wanderRadius = 20.f;
    behaviourData.wanderTarget = {};
    behaviourData.maxSpeed = Enemy::MAX_SPEED;
    behaviourData.detectionBoxWidth = 3.f * ENEMY_RADIUS + 0.5f;
    behaviourData.minDetectionBoxLength = 50.f;
    behaviourData.accelerationDelay = .5f;
    auto enemy = new Enemy(
        {
            Barta::SFML_GraphicsBridge::createNewTransformableInstance(),
            merger.merge(false),
            4
    },
        std::unique_ptr<Barta::HitboxInterface>(new Barta::CircleHitbox(circle)),
        {Barta::Vector2f(Enemy::MAX_SPEED, 0.f).rotated(velocityAngleRadians), false, 1.f, {}, 0.f, {ENEMY_RADIUS, ENEMY_RADIUS}},
        behaviourData
    );

    enemy->move(position);

    this->listManager.addObject(enemy);
    this->objectManager.addGraphicsObject(enemy);
    // this->objectManager.addDynamicsObject(enemy);
    this->objectManager.addNewObject(enemy);

    return enemy;
}
