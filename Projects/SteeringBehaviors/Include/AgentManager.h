#pragma once
#include "Agent.h"
#include "Target.h"
#include "SteeringGUI.h"

#include <unordered_map>
#include <memory>

#include "CommonTypes.h"

class SceneInterface;
class SteeringBehaviorBase;

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
	void ChangeScene(const ESceneIndex BehaviorIndex);
	std::weak_ptr<Agent> SpawnAgent();
	std::weak_ptr<Target> SpawnTarget();

private:
	void BoundaryLooper();

private:
	Vec2 Bounds_;
	ESceneIndex CurrentSceneIndex_ = ESceneIndex::SEEK;
	std::unique_ptr<SceneInterface, SceneDeleter> CurrentScene_;
	std::vector<std::shared_ptr<Agent>> Agents_;
	std::vector<std::shared_ptr<Target>> Targets_;
};
