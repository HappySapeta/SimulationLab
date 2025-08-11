#pragma once
#include "Target.h"
#include "Core/WindowConfiguration.h"

#include <unordered_map>
#include <memory>

#include "SteeringGUI.h"

class SteeringBehaviorBase;

enum class EBehaviorIndex : uint8_t
{
	SEEK,
	FLEE,
	INTERCEPT
};

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
	void SpawnAgent(const Vec2& Position);
	void DeSpawnAll();
	void SetCurrentBehavior(EBehaviorIndex Index);
	void SetArriveBehavior(bool bUseArriveBehavior) { bUseArriveBehavior_ = bUseArriveBehavior; }

private:
	void BoundaryLooper();

private:
	Vec2 Bounds_;
	const EBehaviorIndex CurrentBehaviorIndex_;
	SteeringBehaviorBase* CurrentBehavior_;
	std::unordered_map<EBehaviorIndex, std::unique_ptr<SteeringBehaviorBase, BehaviorDeleter>> Behaviors_;
	bool bUseArriveBehavior_ = false;
	
private:
	std::vector<Agent> Agents_;
	Target Target_;
};

