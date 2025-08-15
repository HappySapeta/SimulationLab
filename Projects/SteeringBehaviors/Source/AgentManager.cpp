#include "AgentManager.h"
#include "Behaviors.h"
#include "Core/WindowConfiguration.h"

#include <cassert>

void BehaviorDeleter::operator()(SteeringBehaviorBase* Ptr)
{
	delete Ptr;
}

AgentManager::AgentManager(const Vec2& Bounds)
	: CurrentBehaviorIndex_(EBehaviorIndex::SEEK), CurrentBehavior_(nullptr), Bounds_(Bounds)
{
	Target_.SetPosition({SL_WINDOW_WIDTH / 2, SL_WINDOW_HEIGHT / 2});

	Behaviors_.insert({EBehaviorIndex::SEEK, std::unique_ptr<SteeringBehaviorBase, BehaviorDeleter>(new SeekBehavior())});
	Behaviors_.insert({EBehaviorIndex::FLEE, std::unique_ptr<SteeringBehaviorBase, BehaviorDeleter>(new FleeBehavior())});
	Behaviors_.insert({EBehaviorIndex::INTERCEPT, std::unique_ptr<SteeringBehaviorBase, BehaviorDeleter>(new InterceptBehavior())});
	Behaviors_.insert({EBehaviorIndex::PURSUE, std::unique_ptr<SteeringBehaviorBase, BehaviorDeleter>(new PursuitBehavior())});
	Behaviors_.insert({EBehaviorIndex::EVADE, std::unique_ptr<SteeringBehaviorBase, BehaviorDeleter>(new EvasionBehavior())});
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
		
		CurrentBehavior_ = Behaviors_.at(CurrentBehaviorIndex_).get();
		assert(CurrentBehavior_);
		Vec2 Force = CurrentBehavior_->GetSteeringForce(Data);

		if (bUseArriveBehavior_)
		{
			if (CurrentBehaviorIndex_ == EBehaviorIndex::PURSUE)
			{
				if (PursuitBehavior* Pursue = dynamic_cast<PursuitBehavior*>(CurrentBehavior_))
				{
					Force += ArriveBehavior::GetSteeringForce(Pursue->GetPursuitData());
				}
			}
			else if (CurrentBehaviorIndex_ != EBehaviorIndex::FLEE)
			{
				Force += ArriveBehavior::GetSteeringForce(Data);
			}
		}
		
		Agent.AddForce(Force);
		Agent.Update(DeltaTime);
		Agent.Draw();
	}

	BoundaryLooper();
}

void AgentManager::SetTargetMovementMode(int ModeAsInt)
{
	Target_.SetMovementMode(ToMovementMode(ModeAsInt));
}

void AgentManager::BoundaryLooper()
{
	for (Agent& Agent : Agents_)
	{
		float X = Agent.GetPosition().x;
		float Y = Agent.GetPosition().y;

		X = X < 0 ? Bounds_.x : (X > Bounds_.x ? 0 : X);
		Y = Y < 0 ? Bounds_.y : (Y > Bounds_.y ? 0 : Y);

		Agent.SetPosition({X, Y});
	}

	float X = Target_.GetPosition().x;
	float Y = Target_.GetPosition().y;

	X = X < 0 ? Bounds_.x : (X > Bounds_.x ? 0 : X);
	Y = Y < 0 ? Bounds_.y : (Y > Bounds_.y ? 0 : Y);

	Target_.SetPosition({X, Y});
}

void AgentManager::SpawnAgent()
{
	float PosX = (std::rand() / (float)RAND_MAX) * SL_WINDOW_WIDTH;
	float PosY = (std::rand() / (float)RAND_MAX) * SL_WINDOW_HEIGHT;
	SpawnAgent({PosX, PosY});
}

void AgentManager::SpawnAgent(const Vec2& Position)
{
	Agents_.emplace_back();
	Agents_.back().SetPosition(Position);
}

void AgentManager::DeSpawnAll()
{
	Agents_.clear();
}

void AgentManager::SetCurrentBehavior(int Index)
{
	EBehaviorIndex NewBehaviorIndex = ToBehaviorIndex(Index);
	if (CurrentBehaviorIndex_ != NewBehaviorIndex)
	{
		CurrentBehaviorIndex_ = NewBehaviorIndex;
	}
}

void AgentManager::SetCurrentBehavior(EBehaviorIndex Behavior)
{
	if (Behaviors_.contains(Behavior))
	{
		CurrentBehavior_ = Behaviors_.at(Behavior).get();
		assert(CurrentBehavior_);
	}
}
