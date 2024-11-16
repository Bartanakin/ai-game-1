//
// Created by bartanakin on 11/15/24.
//

#pragma once
#include "../Agents/Enemy.h"
#include "../Agents/Player.h"
#include "../Agents/Wall.h"
#include "../Events/PlayerMarkerChangeEvent.h"
#include <Events/Events/LeftClickEvent.h>
#include <StaticObjectManager.h>

class Wall;

class PlayerShotSubscriber: public virtual Barta::LeftClickEventSubscriberInterface, public virtual PlayerMarkerChangeSubscriberInterface {
    using EnemyList = Barta::ListType<Enemy>;
    using WallList = Barta::ListType<Wall>;

public:
    PlayerShotSubscriber(Player& player, EnemyList& enemyList, WallList& wallList) noexcept;

    bool handle(Barta::LeftClickEvent& event) override;

    bool handle(PlayerMarkerChangeEvent& event) override;

    bool isValid() const noexcept override;

    std::pair<Barta::Ray, Enemy*> getClosestTarget() const;

private:
    Player& player;
    EnemyList& enemyList;
    WallList& wallList;
};
