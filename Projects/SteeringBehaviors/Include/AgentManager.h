#pragma once
#include "Target.h"

#include <memory>
#include <unordered_map>

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
	void SpawnAgent(const Vec2& Position);
	void SetCurrentBehavior(EBehaviorIndex Index); 

private:
	void BoundaryLooper();
	void DrawGUI();

private:
	Vec2 Bounds_;
	const EBehaviorIndex CurrentBehaviorIndex_;
	SteeringBehaviorBase* CurrentBehavior_;
	std::unordered_map<EBehaviorIndex, std::unique_ptr<SteeringBehaviorBase, BehaviorDeleter>> Behaviors_;
	
private:
	std::vector<Agent> Agents_;
	Target Target_;
};

