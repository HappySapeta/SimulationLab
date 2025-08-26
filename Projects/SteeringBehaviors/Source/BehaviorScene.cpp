#include "BehaviorScene.h"
#include "AgentManager.h"

#include "Behaviors.h"

void SeekScene::Load(AgentManager& Manager)
{
	Agent_ = Manager.SpawnAgent();
	Agent_.lock()->SetPosition({0, 0});

	Target_ = Manager.SpawnTarget();
	Target_.lock()->SetPosition({SL_WINDOW_WIDTH / 2, SL_WINDOW_HEIGHT / 2});
	Target_.lock()->SetMovementMode(EMovementMode::DIAGONAL);
}

void SeekScene::Update(AgentManager& Manager, const float DeltaTime)
{
	if (!Agent_.expired() && !Target_.expired())
	{
		Agent* AgentPtr = Agent_.lock().get();
		Target* TargetPtr = Target_.lock().get();
		SteeringData Data
		{
			AgentPtr->GetPosition(),
			AgentPtr->GetVelocity(),
			TargetPtr->GetPosition(),
			TargetPtr->GetVelocity()
		};
		const Vec2 Force = Behaviors::Seek(Data);

		AgentPtr->AddForce(Force);
	}
}

void FleeScene::Load(AgentManager& Manager)
{
	for (int Count = 0; Count < 5; ++Count)
	{
		float PosX = (std::rand() / (float)RAND_MAX) * SL_WINDOW_WIDTH;
		float PosY = (std::rand() / (float)RAND_MAX) * SL_WINDOW_HEIGHT;
		Agents_.emplace_back(Manager.SpawnAgent());
		Agents_.back().lock()->SetPosition({PosX, PosY});
	}
	
	Target_ = Manager.SpawnTarget();
	Target_.lock()->SetPosition({SL_WINDOW_WIDTH / 2, SL_WINDOW_HEIGHT / 2});
	Target_.lock()->SetMovementMode(EMovementMode::CIRCLE);
}

void FleeScene::Update(AgentManager& Manager, const float DeltaTime)
{
	for (auto AgentX : Agents_)
	{
		if (!AgentX.expired() && !Target_.expired())
		{
			Agent* AgentPtr = AgentX.lock().get();
			Target* TargetPtr = Target_.lock().get();
			SteeringData Data
			{
				AgentPtr->GetPosition(),
				AgentPtr->GetVelocity(),
				TargetPtr->GetPosition(),
				TargetPtr->GetVelocity()
			};

			Vec2 Force;
			if (Vec2::Distance(Data.AgentPosition, Data.TargetPosition) < SL_AGENT_FLEE_RADIUS)
			{
				Force = Behaviors::Flee(Data, SL_AGENT_FLEE_RADIUS);
			}
			else
			{
				Force = Behaviors::Wander(Data, WanderTheta_, SL_AGENT_WANDER_RADIUS, SL_AGENT_WANDER_LENGTH);
			}
			AgentPtr->AddForce(Force);
		}
	}
}

void EvadeScene::Load(AgentManager& Manager)
{
	Agent_ = Manager.SpawnAgent();
	Agent_.lock()->SetPosition({SL_WINDOW_WIDTH / 2, SL_WINDOW_HEIGHT / 2});
	
	Target_ = Manager.SpawnTarget();
	Target_.lock()->SetMovementMode(EMovementMode::DIAGONAL);
}

void EvadeScene::Update(AgentManager& Manager, const float DeltaTime)
{
	if (!Agent_.expired() && !Target_.expired())
	{
		Agent* AgentPtr = Agent_.lock().get();
		Target* TargetPtr = Target_.lock().get();
		SteeringData Data
		{
			AgentPtr->GetPosition(),
			AgentPtr->GetVelocity(),
			TargetPtr->GetPosition(),
			TargetPtr->GetVelocity()
		};

		Vec2 Force;
		if (Vec2::Distance(Data.AgentPosition, Data.TargetPosition) < SL_AGENT_FLEE_RADIUS)
		{
			Force = Behaviors::Evade(Data);
		}
		AgentPtr->AddForce(Force);
	}
}

void PursueScene::Load(AgentManager& Manager)
{
	Agent_ = Manager.SpawnAgent();
	Agent_.lock()->SetPosition({0, 0});
	
	Target_ = Manager.SpawnTarget();
	Target_.lock()->SetPosition({SL_WINDOW_WIDTH / 2, SL_WINDOW_HEIGHT / 2});
}

void PursueScene::Update(AgentManager& Manager, const float DeltaTime)
{
	if (!Agent_.expired() && !Target_.expired())
	{
		Agent* AgentPtr = Agent_.lock().get();
		Target* TargetPtr = Target_.lock().get();
		SteeringData Data
		{
			AgentPtr->GetPosition(),
			AgentPtr->GetVelocity(),
			TargetPtr->GetPosition(),
			TargetPtr->GetVelocity()
		};
		Vec2 Force = Behaviors::Pursue(Data, SL_AGENT_PURSUE_RADIUS);
		const Vec2 PursueTarget = Behaviors::GetPursueTarget(Data, SL_AGENT_PURSUE_RADIUS);
		Force += Behaviors::Arrive({Data.AgentPosition, Data.AgentVelocity, PursueTarget, {0,0}}, SL_AGENT_ARRIVAL_RADIUS * 5);

		AgentPtr->AddForce(Force);
	}
}

void InterceptScene::Load(AgentManager& Manager)
{
	Agent_ = Manager.SpawnAgent();
	Agent_.lock()->SetPosition({0, 0});

	Target_ = Manager.SpawnTarget();
	Target_.lock()->SetPosition({SL_WINDOW_WIDTH / 2, SL_WINDOW_HEIGHT / 2});
	Target_.lock()->SetMovementMode(EMovementMode::CIRCLE);
}

void InterceptScene::Update(AgentManager& Manager, const float DeltaTime)
{
	if (!Agent_.expired() && !Target_.expired())
	{
		Agent* AgentPtr = Agent_.lock().get();
		Target* TargetPtr = Target_.lock().get();
		SteeringData Data
		{
			AgentPtr->GetPosition(),
			AgentPtr->GetVelocity(),
			TargetPtr->GetPosition(),
			TargetPtr->GetVelocity()
		};
		const Vec2 Force = Behaviors::Intercept(Data, SL_AGENT_INTERCEPT_LOOKAHEAD * 5);
		
		AgentPtr->AddForce(Force);
	}
}

void WanderScene::Load(AgentManager& Manager)
{
	for (int Count = 0; Count < 1; ++Count)
	{
		float PosX = SL_WINDOW_WIDTH / 2;//(std::rand() / (float)RAND_MAX) * SL_WINDOW_WIDTH;
		float PosY = 0;//(std::rand() / (float)RAND_MAX) * SL_WINDOW_HEIGHT;
		Agents_.emplace_back(Manager.SpawnAgent());
		Agents_.back().lock()->SetPosition({PosX, PosY});

		WanderThetas_.push_back(0.0f);
	}
}

void WanderScene::Update(AgentManager& Manager, const float DeltaTime)
{
	int Index = 0;
	for (auto AgentX : Agents_)
	{
		if (!AgentX.expired())
		{
			Agent* AgentPtr = AgentX.lock().get();
			const SteeringData Data{AgentPtr->GetPosition(), AgentPtr->GetVelocity(), {0,0}, {0,0}};
			
			const Vec2 Force = Behaviors::Wander(Data, WanderThetas_[Index++], SL_AGENT_WANDER_RADIUS, SL_AGENT_WANDER_LENGTH);
			AgentPtr->AddForce(Force);
		}
	}
}

