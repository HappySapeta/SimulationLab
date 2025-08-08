#include "AgentManager.h"
#include "Behaviors.h"
#include "Core/WindowConfiguration.h"

#include <cassert>
#define RAYGUI_IMPLEMENTATION
#include <raylib/raygui.h>

constexpr uint16_t SPAWN_BUTTON_WIDTH = 150;
constexpr uint16_t SPAWN_BUTTON_HEIGHT = 75;

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
}

void AgentManager::Update(const float DeltaTime)
{
	DrawGUI();
	
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

	BoundaryLooper();
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

void AgentManager::DrawGUI()
{
	constexpr uint16_t SPACING = 10;
	Rectangle SpawnButtonBounds
	{
		SL_WINDOW_WIDTH / 2 - SPAWN_BUTTON_WIDTH - SPACING,
		SL_WINDOW_HEIGHT - SL_WINDOW_HEIGHT * 0.1f - SPAWN_BUTTON_HEIGHT / 2,
		SPAWN_BUTTON_WIDTH,
		SPAWN_BUTTON_HEIGHT
	};

	Rectangle ClearButtonBounds
	{
		SL_WINDOW_WIDTH / 2 + SPACING,
		SpawnButtonBounds.y,
		SPAWN_BUTTON_WIDTH,
		SPAWN_BUTTON_HEIGHT
	};
	
	if (GuiButton(SpawnButtonBounds, "SPAWN AGENT"))
	{
		float PosX = (std::rand() / (float)RAND_MAX) * SL_WINDOW_WIDTH;
		float PosY = (std::rand() / (float)RAND_MAX) * SL_WINDOW_HEIGHT;
		SpawnAgent({PosX, PosY});
	}
	if (GuiButton(ClearButtonBounds, "REMOVE ALL AGENTS"))
	{
		Agents_.clear();
	}
}

void AgentManager::SpawnAgent(const Vec2& Position)
{
	Agents_.emplace_back();
	Agents_.back().SetPosition(Position);
}

void AgentManager::SetCurrentBehavior(EBehaviorIndex Index)
{
	if (Behaviors_.contains(Index))
	{
		CurrentBehavior_ = Behaviors_.at(Index).get();
		assert(CurrentBehavior_);
	}
}
