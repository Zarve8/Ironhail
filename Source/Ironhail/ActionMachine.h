#pragma once
#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "GameFramework/Actor.h"
#include "ActionMachine.generated.h"


class Action_AM {
public:
	float seconds_left = 0.1;
	Action_AM() = default;
	virtual void Start() {}
	virtual void Proceed(float delta_seconds) {}
	virtual Action_AM* Next() {
		return nullptr;
	}
};

class Delay_AM : public Action_AM {
public:
	Delay_AM(){
		seconds_left = 0.1;
	}
	Delay_AM(float delay){
		this->seconds_left = delay;
	}
};

class Sleep_AM : public Action_AM {
	Action_AM* Current;
public:
	Sleep_AM(Action_AM* Currrent) : Current(Current) {
		seconds_left = 100;
	}
	void Proceed(float delta_seconds) override {
		seconds_left = 100;
	}
	Action_AM* Next() override {
		return Current;
	}
};

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UActionMachine : public UInterface
{
	GENERATED_BODY()
};


class IRONHAIL_API IActionMachine
{
	GENERATED_BODY()
protected:
	Action_AM* Current_Action = nullptr;
public:
	virtual Action_AM* GetBaseAction() {
		return new Delay_AM();
	}
	IActionMachine() {
		Current_Action = GetBaseAction();
		if (!Current_Action) {
			Current_Action = new Delay_AM();
		}
	}
	void ActionBeginPlay() {
		if (Current_Action) {
			Current_Action->Start();
		}
		else {
			Current_Action = new Delay_AM();
		}
	}
	void ActionTick(float delta_seconds) {
		if (!Current_Action) {
			Current_Action = GetBaseAction();
			if (Current_Action) {
				Current_Action->Start();
			}
		}
		Current_Action->seconds_left -= delta_seconds;
		if (Current_Action->seconds_left <= 0) {
			Current_Action = Current_Action->Next();
			if (!Current_Action) {
				Current_Action = GetBaseAction();
			}
			if (Current_Action) {
				Current_Action->Start();
			}
		}
		else {
			if (Current_Action) {
				Current_Action->Proceed(delta_seconds);
			}
		}
	}
	void ActionSleep() {
		Current_Action = new Sleep_AM(Current_Action);
	}
	void ActionAwake() {
		Current_Action = Current_Action->Next();
	}
	void ActionAbort(Action_AM* Replace_Action) {
		if (Replace_Action) {
			Current_Action = Replace_Action;
			Current_Action->Start();
		}
		else {
			Current_Action = GetBaseAction();
			if (Current_Action) {
				Current_Action->Start();
			}
			else {
				Current_Action = new Delay_AM;
			}
		}
	}
};
