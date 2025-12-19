// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "K2Node.h"
#include "BlueprintActionDatabaseRegistrar.h"
#include "BlueprintNodeSpawner.h"

#include "K2Node_ForEachLoop_CPP.generated.h"

UCLASS()
class GOLDIELIBRARYEDITOR_API UK2Node_ForEachLoop_CPP : public UK2Node
{
	GENERATED_BODY()

public:
	virtual void GetMenuActions(FBlueprintActionDatabaseRegistrar& ActionRegistrar) const override;
	virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;
	virtual FText GetTooltipText() const override;
	virtual FText GetToolTipHeading() const override;
	virtual FText GetKeywords() const override;
	virtual FLinearColor GetNodeTitleColor() const override;
	virtual FLinearColor GetNodeBodyTintColor() const override;

	// Node Creation Function
	virtual void AllocateDefaultPins() override;
	// Wildcard Checks
	virtual void NotifyPinConnectionListChanged(UEdGraphPin* Pin) override;

	// Main Execution of Node
	virtual void ExpandNode(FKismetCompilerContext& CompilerContext, UEdGraph* SourceGraph) override;
};