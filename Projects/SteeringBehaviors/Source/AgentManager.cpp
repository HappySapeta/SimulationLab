#include "AgentManager.h"
#include "Behaviors.h"
#include "BehaviorScene.h"

#include <cassert>

std::weak_ptr<Agent> AgentManager::SpawnAgent()
{
	Agents_.push_back(std::make_shared<Agent>());
	return Agents_.back();
}

std::weak_ptr<Target> AgentManager::SpawnTarget()
{
	Targets_.push_back(std::make_shared<Target>());
	return Targets_.back();	
}

void AgentManager::ChangeScene(const EBehaviorIndex BehaviorIndex)
{
	if (CurrentSceneIndex_ == BehaviorIndex)
	{
		return;
	}

	CurrentSceneIndex_ = BehaviorIndex;
	if (CurrentScene_)
	{
		Agents_.clear();
		Targets_.clear();
		CurrentScene_.reset();
	}
	
	switch (BehaviorIndex)
	{
		case EBehaviorIndex::SEEK :
		{
			CurrentScene_ = std::unique_ptr<SceneInterface, SceneDeleter>(new SeekScene());
			break;
		}
		case EBehaviorIndex::FLEE :
		{
			CurrentScene_ = std::unique_ptr<SceneInterface, SceneDeleter>(new FleeScene());
			break;
		}
		case EBehaviorIndex::INTERCEPT :
		{
			CurrentScene_ = std::unique_ptr<SceneInterface, SceneDeleter>(new InterceptScene());
			break;
		}
		case EBehaviorIndex::PURSUE :
		{
			CurrentScene_ = std::unique_ptr<SceneInterface, SceneDeleter>(new PursueScene());
			break;
		}
		case EBehaviorIndex::EVADE :
		{
			CurrentScene_ = std::unique_ptr<SceneInterface, SceneDeleter>(new EvadeScene());
			break;
		}
		case EBehaviorIndex::WANDER :
		{
			CurrentScene_ = std::unique_ptr<SceneInterface, SceneDeleter>(new WanderScene());
			break;
		}
		default:
		{
			return;
		}
	}

	if (CurrentScene_)
	{
		CurrentScene_->Load(*this);
	}
}

void AgentManager::Update(const float DeltaTime)
{
	if (CurrentScene_)
	{
		CurrentScene_->Update(*this, DeltaTime);
	}

	for (auto Agent : Agents_)
	{
		Agent->Draw();
		Agent->Update(DeltaTime);
	}

	for (auto Target : Targets_)
	{
		Target->Draw();
		Target->Update(DeltaTime);
	}

	BoundaryLooper();
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

	for (auto Agent : Agents_)
	{
		Agent->SetPosition(Loop(Agent->GetPosition()));
	}

	for (auto Target : Targets_)
	{
		Target->SetPosition(Loop(Target->GetPosition()));
	}
}

void SceneDeleter::operator()(SceneInterface* Ptr)
{
	delete Ptr;
}
