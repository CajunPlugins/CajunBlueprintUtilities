// Copyright 2024 Cajun Pro LLC. All Rights Reserved.

#include "KismetNodes/K2Interface_SelectDelegate.h"

// BlueprintGraph
#include "K2Node.h"

// UnrealEd
#include "Kismet2/BlueprintEditorUtils.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(K2Interface_SelectDelegate)

void IK2Interface_SelectDelegate::HandleAnyChange(bool bForceModify)
{
	const auto NodeThis = CastChecked<UK2Node>(this);
	UpdateNodeTitle();
	if (HandleAnyChangeWithoutNotifying() || bForceModify)
	{
		if (const auto Graph = NodeThis->GetGraph())
			Graph->NotifyGraphChanged();

		if (UBlueprint* Blueprint = NodeThis->GetBlueprint(); Blueprint && !Blueprint->bBeingCompiled)
		{
			FBlueprintEditorUtils::MarkBlueprintAsModified(Blueprint);
			Blueprint->BroadcastChanged();
		}
	}
	else if (GetDelegateFunctionName() == NAME_None)
	{
		if (const auto Graph = NodeThis->GetGraph())
			Graph->NotifyGraphChanged();
	}
}
