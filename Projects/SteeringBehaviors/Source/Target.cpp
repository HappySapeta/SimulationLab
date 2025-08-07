#include "Target.h"
#include "AgentConfiguration.h"

void Target::Draw()
{
	DrawCircleV(Position_, SL_TARGET_SIZE, YELLOW);
}
