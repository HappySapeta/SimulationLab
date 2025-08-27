#pragma once
#include <array>
#include <cstdint>

constexpr int NUM_SCENES = 6;
enum class ESceneIndex : uint8_t
{
	SEEK,
	FLEE,
	INTERCEPT,
	PURSUE,
	EVADE,
	WANDER,
	COUNT = NUM_SCENES
};

inline ESceneIndex ToSceneIndex(const int Index)
{
	using UnderlyingType = std::underlying_type_t<ESceneIndex>;
	ESceneIndex Behavior = Index >= static_cast<UnderlyingType>(ESceneIndex::SEEK) &&
							  Index < static_cast<UnderlyingType>(ESceneIndex::COUNT)
								  ? static_cast<ESceneIndex>(Index)
								  : ESceneIndex::SEEK;

	return Behavior;
}

static std::array<char[20], NUM_SCENES> SceneNames {"SEEK", "FLEE", "INTERCEPT", "PURSUE", "EVADE", "WANDER"};