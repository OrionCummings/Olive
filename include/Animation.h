#pragma once
#ifndef H_ANIMATION
#define H_ANIMATION

#include <stdbool.h>
#include <math.h>
#include "Debug.h"

#define ANIMATION_TICKS 25

typedef enum AnimationDirection {
	FORWARD = 1,
	BACKWARD = -1,
} AnimationDirection;

static const char* AnimationStateNames[] = { "Inactive", "Active", "Done" };

typedef enum AnimationState{
	INACTIVE,
	ACTIVE,
	DONE
} AnimationState;

typedef struct Animation {
	AnimationState State;
	uint32_t Ticks;
	double Time;
	double (*EasingFunction)(double t);
} Animation;

Animation AnimationNew(void* EasingFunction);
void InitZoomAnimation(double (*EasingFunction)(double t));
void InitPanAnimation(double (*EasingFunction)(double t));
void AnimationSetEasingFunction(Animation* A, void* EasingFunction);
void AnimationStart(Animation* A, AnimationDirection Dir);
void AnimationStep(Animation* A, AnimationDirection Dir);
void AnimationPrint(const Animation A);
bool AnimationActive(const Animation A);
bool AnimationInactive(const Animation A);
bool AnimationDone(const Animation A);

// Easing functions (EFs) are (generally) bijective in [0, 1] and undefined elsewhere.
// Most EFs have a codomain of [0, 1], but this is not a hard requirement!
inline double EasingLinear(double T);
inline double EasingInOutCubic(double T);
inline double EasingOutBack(double T);

#endif