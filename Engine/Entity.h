#pragma once

#include "GameEngine.h"
#include <vector>

#include "ECS.h"
#include "Component.h"

#include "Transform.h"
#include "SpriteComponent.h"
#include "TextComponent.h"
#include "Rigidbody.h"
#include "Animator.h"
#include "Collider.h"

class Entity
{
public:

	Entity();

	virtual ~Entity();

	template<typename T, typename... TArgs>
	T& AddComponent(TArgs&&... args) {
		T* comp(new T(std::forward<TArgs>(args)...));

		std::unique_ptr<Component> uptr{ comp };
		components.emplace_back(std::move(uptr));
		comp->entity = this;

		if (comp->Init())
		{
			compList[GetComponentTypeID<T>()] = comp;
			compBitset[GetComponentTypeID<T>()] = true;
			comp->entity = this;
			return *comp;
		}

		return *static_cast<T*>(nullptr);
	}

	template<typename T>
	T& GetComponent() const
	{
		auto ptr(compList[GetComponentTypeID<T>()]);
		return *static_cast<T*>(ptr);
	}

	template <typename T>
	inline bool HasComponent() const {

		return compBitset[GetComponentTypeID<T>()];
	}

	inline bool IsActive() const {
		return active;
	}

	inline void Destroy() {
		active = false;
	}

	/*bool HasGroup(Group mGroup)
	{
		return groupBitset[mGroup];
	}*/

	//void AddGroup(Group mGroup);

	/*void delGroup(Group mGroup)
	{
		groupBitset[mGroup] = false;
	}*/

	virtual void Init() {};

	virtual void Draw();

	virtual void Update();

	virtual void WasHit(Entity* collidedObject) {};

private:

	class Level* level{ nullptr };
	bool active{ true };
	ComponentList compList{};
	ComponentBitset compBitset{};
	std::vector<std::unique_ptr<Component>> components;
	//GroupBitset groupBitset;
};