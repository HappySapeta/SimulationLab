#pragma once
#include "Agent.h"
#include "Target.h"
#include "Core/WindowConfiguration.h"
#include "SteeringGUI.h"

#include <unordered_map>
#include <memory>

class SceneInterface;
class SteeringBehaviorBase;

enum class EBehaviorIndex : uint8_t
{
	NONE,
	SEEK,
	FLEE,
	INTERCEPT,
	PURSUE,
	EVADE,
	WANDER,
	COUNT
};

inline EBehaviorIndex ToBehaviorIndex(const int Index)
{
	using UnderlyingType = std::underlying_type_t<EBehaviorIndex>;
	EBehaviorIndex Behavior = Index >= static_cast<UnderlyingType>(EBehaviorIndex::NONE) &&
							  Index < static_cast<UnderlyingType>(EBehaviorIndex::COUNT)
								  ? static_cast<EBehaviorIndex>(Index)
								  : EBehaviorIndex::NONE;

	return Behavior;
}

struct SceneDeleter
{
	void operator()(SceneInterface* Ptr);
};

class AgentManager
{
public:
	
	AgentManager(const Vec2& Bounds)
		: Bounds_(Bounds)
	{}
	
	void Update(float DeltaTime);
	void ChangeScene(const EBehaviorIndex BehaviorIndex);
	std::weak_ptr<Agent> SpawnAgent();
	std::weak_ptr<Target> SpawnTarget();

private:
	void BoundaryLooper();

private:
	Vec2 Bounds_;
	EBehaviorIndex CurrentSceneIndex_ = EBehaviorIndex::NONE;
	std::unique_ptr<SceneInterface, SceneDeleter> CurrentScene_;
	std::vector<std::shared_ptr<Agent>> Agents_;
	std::vector<std::shared_ptr<Target>> Targets_;
};
