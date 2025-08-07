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
	AgentManager()
		: CurrentBehaviorIndex_(EBehaviorIndex::SEEK), CurrentBehavior_(nullptr)
	{}
	
	void Update(float DeltaTime);
	void Initialize();
	void SpawnAgent();
	void SetCurrentBehavior(EBehaviorIndex Index); 

private:

	const EBehaviorIndex CurrentBehaviorIndex_;
	SteeringBehaviorBase* CurrentBehavior_;
	std::unordered_map<EBehaviorIndex, std::unique_ptr<SteeringBehaviorBase, BehaviorDeleter>> Behaviors_;
	
private:
	std::vector<Agent> Agents_;
	Target Target_;
};

