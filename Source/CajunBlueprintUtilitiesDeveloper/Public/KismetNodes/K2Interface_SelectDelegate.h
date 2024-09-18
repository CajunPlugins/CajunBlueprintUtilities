// Copyright 2024 Cajun Pro LLC. All Rights Reserved.

#pragma once

#include "UObject/Interface.h"

#include "K2Interface_SelectDelegate.generated.h"

// Static class for interface required to be compatible with the K2SelectDelegate graph node
UINTERFACE(meta=(CannotImplementInterfaceInBlueprint))
class CAJUNBLUEPRINTUTILITIESDEVELOPER_API UK2Interface_SelectDelegate : public UInterface
{
	GENERATED_BODY()
};

// Interface required to be compatible with the K2SelectDelegate graph node
class CAJUNBLUEPRINTUTILITIESDEVELOPER_API IK2Interface_SelectDelegate
{
	GENERATED_BODY()

public:
	// Set new Function name (Without notifying about the change)
	virtual void SetDelegateFunction(FName Name) = 0;

	// Get the name of the function that is currently bound to this event
	[[nodiscard]] virtual FName GetDelegateFunctionName() const = 0;

	// Get the class that contains the possible functions to choose from
	[[nodiscard]] virtual UClass* GetScopeClass(bool bDontUseSkeletalClassForSelf = false) const = 0;

	// Get the function object that defines the function signature
	[[nodiscard]] virtual UFunction* GetDelegateSignature() const = 0;
	
	// Get the function object that defines the function signature
	virtual void UpdateNodeTitle() = 0;

	// Update for any change that have occurred but without affecting the blueprint graph
	virtual bool HandleAnyChangeWithoutNotifying() = 0;

	// Update for any changes that have occurred
	void HandleAnyChange(bool bForceModify = false);
};
