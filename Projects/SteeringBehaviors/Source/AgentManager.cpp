#include "AgentManager.h"
#include "Behaviors.h"
#include "Core/WindowConfiguration.h"

#include <cassert>

void AgentManager::Initialize()
{
	Target_.SetPosition({SL_WINDOW_WIDTH / 2, SL_WINDOW_HEIGHT / 2});
	Target_.SetVelocity({0,0});
	Target_.SetTargetType(ETargetType::SEEK);

	Behaviors_.insert({EBehaviorIndex::SEEK, std::unique_ptr<SteeringBehaviorBase, BehaviorDeleter>(new SeekBehavior())});
	Behaviors_.insert({EBehaviorIndex::FLEE, std::unique_ptr<SteeringBehaviorBase, BehaviorDeleter>(new FleeBehavior())});
	Behaviors_.insert({EBehaviorIndex::INTERCEPT, std::unique_ptr<SteeringBehaviorBase, BehaviorDeleter>(new InterceptBehavior())});
}

void BehaviorDeleter::operator()(SteeringBehaviorBase* Ptr)
{
	delete Ptr;
}

void AgentManager::Update(const float DeltaTime)
{
	Target_.Update(DeltaTime);
	Target_.Draw();
	for (Agent& Agent : Agents_)
	{
		SteeringData Data
		{
			Agent.GetPosition(),
			Agent.GetVelocity(),
			Target_.GetPosition(),
			Target_.GetVelocity()
		};
		const Vec2 Force = CurrentBehavior_->GetSteeringForce(Data);
		
		Agent.AddForce(Force);
		Agent.Update(DeltaTime);
		Agent.Draw();
	}
}

void AgentManager::SpawnAgent()
{
	Agents_.emplace_back();
}

void AgentManager::SetCurrentBehavior(EBehaviorIndex Index)
{
	if (Behaviors_.contains(Index))
	{
		CurrentBehavior_ = Behaviors_.at(Index).get();
		assert(CurrentBehavior_);
	}
}
