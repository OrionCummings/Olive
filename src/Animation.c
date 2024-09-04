#include "Animation.h"

Animation AnimationNew(void* EasingFunction) {
	return (Animation) { .State = INACTIVE, .Ticks = 0, .Time = 0.0, .EasingFunction = EasingFunction };
}

void AnimationStart(Animation* A, AnimationDirection Dir) {
	A->State = ACTIVE;
	A->Ticks = (Dir) ? ANIMATION_TICKS : 0;
	A->Time = (Dir) ? 1.0 : 0.0;
}

void AnimationStep(Animation* A, AnimationDirection Dir) {

	if (A == NULL) {
		ERROR("Passed null animation");
		return;
	}

	if (A->EasingFunction == NULL) {
		ERROR("Passed null easing function");
		return;
	}

	if (A->State == ACTIVE) {
		switch (Dir) {
		case(FORWARD): {
			if ((A->Ticks)++ < ANIMATION_TICKS) {
				A->Time = A->EasingFunction((double)A->Ticks / ANIMATION_TICKS);
			}
			else {
				A->State = INACTIVE;
				A->Time = 1.0;
				A->Ticks = ANIMATION_TICKS;
			}
			break;
		}
		case(BACKWARD): {
			if ((A->Ticks)-- > 0) {
				A->Time = A->EasingFunction((double)A->Ticks / ANIMATION_TICKS);
			}
			else {
				A->State = INACTIVE;
				A->Time = 0.0;
				A->Ticks = 0;
			}
			break;
		}
		}
	}
}

void AnimationSetEasingFunction(Animation* A, void* EasingFunction) {
	if (EasingFunction == NULL) {
		ERROR("Null easing function");
		return;
	}

	A->EasingFunction = EasingFunction;
}

bool AnimationActive(const Animation A) {
	return A.State == ACTIVE;
}

bool AnimationInactive(const Animation A) {
	return A.State == INACTIVE;
}

bool AnimationDone(const Animation A) {
	return A.State == DONE;
}

void AnimationPrint(const Animation A) {
	printf("[ANIMATION] %s: %.4f (%u/%u)\n", AnimationStateNames[A.State], A.Time, A.Ticks, ANIMATION_TICKS);
}

// Easing functions
double EasingLinear(double t) {
	return t;
}

double EasingInOutCubic(double t) {
	return (t < 0.5) ? (4 * t * t * t) : 1 - (((-2 * t + 2) * (-2 * t + 2) * (-2 * t + 2)) / 2);
}

double EasingOutBack(double t) {
	const double c1 = 1.70158;
	const double c3 = c1 + 1;
	return 1 + c3 * pow(t - 1, 3) + c1 * pow(t - 1, 2);
}