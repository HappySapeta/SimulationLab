#include "AgentManager.h"
#include "Behaviors.h"
#include "Core/WindowConfiguration.h"

#include <cassert>

void BehaviorDeleter::operator()(SteeringBehaviorBase* Ptr)
{
	delete Ptr;
}

AgentManager::AgentManager(const Vec2& Bounds)
	: CurrentBehavior_(nullptr), Bounds_(Bounds)
{
	Target_.SetPosition({SL_WINDOW_WIDTH / 2, SL_WINDOW_HEIGHT / 2});

	Behaviors_.insert({EBehaviorIndex::SEEK, std::unique_ptr<SteeringBehaviorBase, BehaviorDeleter>(new SeekBehavior())});
	Behaviors_.insert({EBehaviorIndex::FLEE, std::unique_ptr<SteeringBehaviorBase, BehaviorDeleter>(new FleeBehavior())});
	Behaviors_.insert({EBehaviorIndex::INTERCEPT, std::unique_ptr<SteeringBehaviorBase, BehaviorDeleter>(new InterceptBehavior())});
	Behaviors_.insert({EBehaviorIndex::PURSUE, std::unique_ptr<SteeringBehaviorBase, BehaviorDeleter>(new PursuitBehavior())});
	Behaviors_.insert({EBehaviorIndex::EVADE, std::unique_ptr<SteeringBehaviorBase, BehaviorDeleter>(new EvasionBehavior())});
	Behaviors_.insert({EBehaviorIndex::WANDER, std::unique_ptr<WanderingBehavior, BehaviorDeleter>(new WanderingBehavior())});
}

void AgentManager::Update(const float DeltaTime)
{
	Target_.Update(DeltaTime);
	Target_.Draw();

	SteeringData Data
	{
		Agent_.GetPosition(),
		Agent_.GetVelocity(),
		Target_.GetPosition(),
		Target_.GetVelocity()
	};
	
	Vec2 Force = CurrentBehavior_->GetSteeringForce(Data);

	if (bUseArriveBehavior_)
	{
		if (PursuitBehavior* Pursue = dynamic_cast<PursuitBehavior*>(CurrentBehavior_))
		{
			Force += ArriveBehavior::GetSteeringForce(Pursue->GetPursuitData());
		}
		if (InterceptBehavior* Intercept = dynamic_cast<InterceptBehavior*>(CurrentBehavior_))
		{
			Force += ArriveBehavior::GetSteeringForce(Intercept->GetInterceptionData());
		}
		else if (dynamic_cast<FleeBehavior*>(CurrentBehavior_) == nullptr)
		{
			Force += ArriveBehavior::GetSteeringForce(Data);
		}
	}
		
	Agent_.AddForce(Force);
	Agent_.Update(DeltaTime);
	Agent_.Draw();

	BoundaryLooper();
}

void AgentManager::SetTargetMovementMode(int ModeAsInt)
{
	Target_.SetMovementMode(ToMovementMode(ModeAsInt));
}

void AgentManager::BoundaryLooper()
{
	static auto Loop = [this](const Vec2& Position) -> Vec2
	{
		float PosX = Position.x;
		float PosY = Position.y;
		PosX = PosX < 0 ? Bounds_.x : (PosX > Bounds_.x ? 0 : PosX);
		PosY = PosY < 0 ? Bounds_.y : (PosY > Bounds_.y ? 0 : PosY);

		return {PosX, PosY};
	};
	
	Agent_.SetPosition(Loop(Agent_.GetPosition()));
	Target_.SetPosition(Loop(Target_.GetPosition()));
}

void AgentManager::SpawnAgent()
{
	float PosX = (std::rand() / (float)RAND_MAX) * SL_WINDOW_WIDTH;
	float PosY = (std::rand() / (float)RAND_MAX) * SL_WINDOW_HEIGHT;
	SpawnAgent({PosX, PosY});
}

void AgentManager::SpawnAgent(const Vec2& Position)
{
	Agent_.SetPosition(Position);
}

void AgentManager::SetCurrentScene(EBehaviorIndex Behavior)
{
	if (Behaviors_.contains(Behavior))
	{
		CurrentBehavior_ = Behaviors_.at(Behavior).get();
		assert(CurrentBehavior_);
	}
}
