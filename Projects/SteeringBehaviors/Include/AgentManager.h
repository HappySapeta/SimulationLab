#pragma once
#include "Target.h"
#include "Core/WindowConfiguration.h"
#include "SteeringGUI.h"

#include <unordered_map>
#include <memory>

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

struct BehaviorDeleter
{
	void operator()(SteeringBehaviorBase* Ptr);
};

class AgentManager
{
public:
	AgentManager(const Vec2& Bounds);
	
	void Update(float DeltaTime);
	void SpawnAgent();
	void SetCurrentScene(EBehaviorIndex Behavior);
	void SetArriveBehavior(bool bUseArriveBehavior) { bUseArriveBehavior_ = bUseArriveBehavior; }
	void SetTargetMovementMode(int ModeAsInt);

private:
	void BoundaryLooper();
	void SpawnAgent(const Vec2& Position);

private:
	Vec2 Bounds_;
	SteeringBehaviorBase* CurrentBehavior_;
	std::unordered_map<EBehaviorIndex, std::unique_ptr<SteeringBehaviorBase, BehaviorDeleter>> Behaviors_;
	bool bUseArriveBehavior_ = false;
	
private:
	Agent Agent_;
	Target Target_;
};
