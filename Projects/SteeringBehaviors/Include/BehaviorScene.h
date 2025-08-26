#pragma once
#include "Agent.h"
#include "Target.h"

class AgentManager;
class SceneInterface
{
public:
	virtual ~SceneInterface() = default;
	virtual void Load(AgentManager& Manager) = 0;
	virtual void Update(AgentManager& Manager, const float DeltaTime) = 0;
};

class SeekScene : public SceneInterface
{
public:
	void Load(AgentManager& Manager) override;
	void Update(AgentManager& Manager, const float DeltaTime) override;

private:

	std::weak_ptr<Agent> Agent_;
	std::weak_ptr<Target> Target_;
};

class FleeScene : public SceneInterface
{
public:
	void Load(AgentManager& Manager) override;
	void Update(AgentManager& Manager, const float DeltaTime) override;

private:
	std::vector<std::weak_ptr<Agent>> Agents_;
	std::weak_ptr<Target> Target_;
	float WanderTheta_ = 0.0f;
};

class EvadeScene : public SceneInterface
{
public:
	void Load(AgentManager& Manager) override;
	void Update(AgentManager& Manager, const float DeltaTime) override;

private:
	std::weak_ptr<Agent> Agent_;
	std::weak_ptr<Target> Target_;
};

class PursueScene : public SceneInterface
{
public:
	void Load(AgentManager& Manager) override;
	void Update(AgentManager& Manager, const float DeltaTime) override;

private:
	std::weak_ptr<Agent> Agent_;
	std::weak_ptr<Target> Target_;
};

class InterceptScene : public SceneInterface
{
public:
	void Load(AgentManager& Manager) override;
	void Update(AgentManager& Manager, const float DeltaTime) override;
	
private:
	std::weak_ptr<Agent> Agent_;
	std::weak_ptr<Target> Target_;
};

class WanderScene : public SceneInterface
{
public:
	void Load(AgentManager& Manager) override;
	void Update(AgentManager& Manager, const float DeltaTime) override;

private:
	std::vector<std::weak_ptr<Agent>> Agents_;
	std::vector<float> WanderThetas_;
};