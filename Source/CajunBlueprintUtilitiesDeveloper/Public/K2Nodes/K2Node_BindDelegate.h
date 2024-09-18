// Copyright 2024 Cajun Pro LLC. All Rights Reserved.

#pragma once

#include "K2Node.h"

#include "KismetNodes/K2Interface_SelectDelegate.h"

#include "Misc/Guid.h"

#include "K2Node_BindDelegate.generated.h"

struct FSearchTagDataPair;
class FCompilerResultsLog;

UCLASS()
class CAJUNBLUEPRINTUTILITIESDEVELOPER_API UK2Node_BindDelegate : public UK2Node, public IK2Interface_SelectDelegate
{
	GENERATED_BODY()

public:
	// Pin accessors
	UEdGraphPin* GetTargetPin() const;
	UEdGraphPin* GetObjectInPin() const;

	// K2Node API
	[[nodiscard]] virtual bool IsNodeSafeToIgnore() const override { return true; }
	virtual void PostReconstructNode() override;
	virtual void GetMenuActions(FBlueprintActionDatabaseRegistrar& ActionRegistrar) const override;
	virtual FText GetMenuCategory() const override;
	virtual int32 GetNodeRefreshPriority() const override { return Low_ReceivesDelegateSignature; }

	// Ed Graph Node API
	virtual void AllocateDefaultPins() override;
	virtual void ExpandNode(FKismetCompilerContext& CompilerContext, UEdGraph* SourceGraph) override;
	virtual void PinConnectionListChanged(UEdGraphPin* Pin) override;
	virtual void PinTypeChanged(UEdGraphPin* Pin) override;
	virtual void NodeConnectionListChanged() override;
	virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;
	virtual FText GetTooltipText() const override;
	virtual UObject* GetJumpTargetForDoubleClick() const override;
	virtual void AddSearchMetaDataInfo(TArray<FSearchTagDataPair>& OutTaggedMetaData) const override;
	virtual TSharedPtr<SGraphNode> CreateVisualWidget() override;

	// Select Delegate Interface API
	virtual void SetDelegateFunction(FName Name) override;
	virtual FName GetDelegateFunctionName() const override;
	virtual UFunction* GetDelegateSignature() const override;
	virtual UClass* GetScopeClass(bool bDontUseSkeletalClassForSelf = false) const override;
	virtual bool HandleAnyChangeWithoutNotifying() override;
	virtual void UpdateNodeTitle() override;
	// Assign a selection as the currently selected delegate to bind to
	void SetDelegate(FName Name);

	// Get the name of the delegate that is currently being bound to
	FName GetDelegateName() const;

	// Get the class that should be searched for possible delegates to bind to
	UClass* GetDelegateOwnerClass(bool bDontUseSkeletalClassForSelf = false) const;

	// Compiler hook to re-validate functions
	void ValidationAfterFunctionsAreCreated(FCompilerResultsLog& MessageLog, bool bFullCompile) const;

private:
	FNodeTextCache CachedNodeTitle;
	static const FName TargetPinName;

	// Determine if there are any configuration problems with this node instance
	[[nodiscard]] bool CheckForErrors(const FKismetCompilerContext& CompilerContext) const;

	// Check the validity of the delegate binding
	bool IsValid(FString* OutMsg = nullptr, bool bDontUseSkeletalClassForSelf = false) const;

	// The currently selected function
	UPROPERTY(meta=(BlueprintSearchable=true))
	FName SelectedFunctionName;

	// A stable reference to the selected function
	UPROPERTY()
	FGuid SelectedFunctionGuid;

	// The name of the delegate that is currently being bound to
	UPROPERTY(meta=(BlueprintSearchable=true))
	FName SelectedDelegateName;
};
