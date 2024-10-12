//
// Created by bartanakin on 10/12/24.
//

#pragma once
#include "../Agents/Player.h"
#include "../Predefines.h"
#include <Graphics/Color.h>
#include <ObjectManagerInterface.h>

class AgentRepository {
public:
    AgentRepository(ListManager& listManager, Barta::ObjectManagerInterface& objectManager) noexcept;

    Player* addNewPlayer() noexcept;

    Wall* addNewBoundingWall(Barta::Vector2f size, Barta::Color color, bool infiniteMass = true) noexcept;

private:
    ListManager& listManager;
    Barta::ObjectManagerInterface& objectManager;
};
