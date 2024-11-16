//
// Created by bartanakin on 10/12/24.
//
#pragma once

#include "Agents/Enemy.h"
#include "Agents/Player.h"
#include "Events/EnemyEnemyCollisionEvent.h"
#include "Events/EnemyWallCollisionEvent.h"
#include "Events/PlayerEnemyCollisionEvent.h"
#include "Events/PlayerWallCollisionEvent.h"
#include <Collisions/CollisionExecutors/CollisionTestExecutor.h>
#include <Collisions/CollisionExecutors/FilterNoCollisionDecorator.h>
#include <Collisions/CollisionLogger.h>
#include <Events/BartaEventLoggerInterface.h>
#include <StaticObjectManager.h>

typedef Barta::FilterNoCollisionDecorator<Barta::CollisionTestExecutor> CollisionCoreExecutor;

// clang-format off
/**
 * Always insert types in pairs. Each pair tell the logger which object types should be searched for collision.
 * This class runs collision test executors and logs the collisions to an event matcher.
 */
typedef Barta::CollisionLogger<
    Player, Wall,
    Enemy, Wall,
    Player, Enemy,
    Enemy, Enemy
> DefaultCollisionLogger;
// clang-format on

/**
 * This class pairs the found collisions with respective subscribers.
 */
typedef Barta::EventMatcher<PlayerWall, EnemyWall, PlayerEnemy, EnemyEnemy> CollisionEventsLogger; // <--

typedef Barta::StaticObjectManager<Player, Wall, Enemy> ListManager; // <--
