#pragma once
#include "GameEngine.h"
#include <vector>
#include "Entity.h"

class Level
{
public:

	Level(std::string levelName) {};

	~Level();
	

	void Draw();
	void Update();
	void Refresh();
	void Init();

	void AddEntity(Entity* entity);
	void EraseEntity(Entity* entity);
	void ClearLevel();
	std::vector<std::pair<int, Entity*>> renderOrder;
	//void AddToGroup(Entity* mEntity, Group mGroup);
	//std::vector<Entity*>& GetGroup(Group mGroup):

private:
	std::vector<Entity*> levelEntities{};
	std::vector<Entity*> entitiesToAdd{};
	//std::array<std::vector<Entity*>, maxGroups> groupedEntities;
};