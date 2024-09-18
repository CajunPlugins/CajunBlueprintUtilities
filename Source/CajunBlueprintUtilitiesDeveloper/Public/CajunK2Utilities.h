// Copyright 2024 Cajun Pro LLC. All Rights Reserved.

#pragma once
#include "UObject/NameTypes.h"

class FKismetCompilerContext;
// ReSharper disable once CppUE4CodingStandardNamingViolationWarning
class UEdGraphPin;
class UK2Node;
class FBlueprintActionDatabaseRegistrar;
class UK2Node_CustomEvent;

// Utilities for writing custom K2 nodes
namespace CajunK2Utilities
{
	static const FName Self_ParamName(TEXT("self"));
	static const FName WorldContext_ParamName(TEXT("WorldContext"));
	static const FName PN_WorldContextObject(TEXT("WorldContextObject"));

	// Handle the copy of data from one pin to another either moving the links or copying the default value data
	CAJUNBLUEPRINTUTILITIESDEVELOPER_API void MovePinLinksOrCopyDefaults(FKismetCompilerContext& CompilerContext, UEdGraphPin* Source, UEdGraphPin* Dest);

	// Forcibly detach and attempt to reattach all the links from the pin to other pins
	CAJUNBLUEPRINTUTILITIESDEVELOPER_API void RefreshAllowedConnections(const UK2Node* K2Node, UEdGraphPin* Pin);

	// Get the pin that is acting as an input to the specified pin
	[[nodiscard]] CAJUNBLUEPRINTUTILITIESDEVELOPER_API UEdGraphPin* GetInputPinLink(UEdGraphPin* Pin);

	// Set the tooltip for a pin and prepends the type information to specified tooltip
	CAJUNBLUEPRINTUTILITIESDEVELOPER_API void SetPinToolTip(UEdGraphPin* MutablePin, const FText& PinDescription = FText());

	// Utility function wrapping the bare minimum code needed for implementing overrides of UK2Node::GetMenuActions
	CAJUNBLUEPRINTUTILITIESDEVELOPER_API void DefaultGetMenuActions(const UK2Node* Node, FBlueprintActionDatabaseRegistrar& ActionRegistrar);

	// Utility for creating event nodes that can be used to bind BlueprintInternal function delegate params to custom K2Node exec output pins
	CAJUNBLUEPRINTUTILITIESDEVELOPER_API UK2Node_CustomEvent* CreateCustomEvent(FKismetCompilerContext& CompilerContext,
	                                                                            UEdGraphPin* SourcePin,
	                                                                            UEdGraph* SourceGraph,
	                                                                            UK2Node* Node,
	                                                                            UEdGraphPin* ExternalPin);

	// Delegates used by the CreateFunctionPins and ExpandFunctionPins functions to delegate certain features
	DECLARE_DELEGATE_RetVal_OneParam(FName, FGetPinName, FProperty*);
	DECLARE_DELEGATE_RetVal_OneParam(FText, FGetPinText, FProperty*);
	// Create all pins required for a function signature
	CAJUNBLUEPRINTUTILITIESDEVELOPER_API TArray<UEdGraphPin*> CreateFunctionPins(UK2Node* Node,
	                                                                             const UFunction* Signature,
	                                                                             EEdGraphPinDirection,
	                                                                             bool bMakeAdvanced,
	                                                                             const FGetPinName& GetPinName,
	                                                                             const FGetPinText& GetPinTooltip = {});

	// Create the pins required for any multi-dispatch delegates
	CAJUNBLUEPRINTUTILITIESDEVELOPER_API void CreateEventDispatcherPins(const UClass* Class,
	                                                                    UK2Node* Node,
	                                                                    TArray<UEdGraphPin*>* OutDispatcherPins,
	                                                                    bool bMakeAdvanced,
	                                                                    const TArray<FName>& IgnoreDispatchers = {});

	// Delegate used by ExpandFunctionPins to delegate certain features
	DECLARE_DELEGATE_TwoParams(FDoPinExpansion, FProperty*, UEdGraphPin*);
	// Execute logic for each of the function pins doing whatever the DoPinExpansion delegate wants
	CAJUNBLUEPRINTUTILITIESDEVELOPER_API void ExpandFunctionPins(const UK2Node* Node,
	                                                             const UFunction* Signature,
	                                                             EEdGraphPinDirection Dir,
	                                                             const FGetPinName& GetPinName,
	                                                             const FDoPinExpansion& DoPinExpansion);

	// Attach pins created by CreateEventDispatcherPins to the object
	[[nodiscard]] CAJUNBLUEPRINTUTILITIESDEVELOPER_API UEdGraphPin* ExpandDispatcherPins(FKismetCompilerContext& CompilerContext,
	                                                                                     UEdGraph* SourceGraph,
	                                                                                     UK2Node* Node,
	                                                                                     UEdGraphPin* ExecPin,
	                                                                                     const UClass* Class,
	                                                                                     UEdGraphPin* InstancePin,
	                                                                                     const TFunction<bool(UEdGraphPin*)>& IsGeneratedPin);

	// Change the order of a pin within the Node pins
	CAJUNBLUEPRINTUTILITIESDEVELOPER_API void ReorderPin(UK2Node* Node, UEdGraphPin* Pin, int NewIndex);

	// Retrieve the standard UE4 icon and color for a regular function
	[[nodiscard]] CAJUNBLUEPRINTUTILITIESDEVELOPER_API FSlateIcon GetFunctionIconAndTint(FLinearColor& OutColor);
	// Retrieve the standard UE4 icon and color for a pure function
	[[nodiscard]] CAJUNBLUEPRINTUTILITIESDEVELOPER_API FSlateIcon GetPureFunctionIconAndTint(FLinearColor& OutColor);

	// Utility that makes sure that the visuals of the graph and property panels refresh. Optionally can mark the blueprint dirty to trigger a save later on
	CAJUNBLUEPRINTUTILITIESDEVELOPER_API void HandleGraphChange(const UK2Node* Node, bool bMarkDirty = false);
}
