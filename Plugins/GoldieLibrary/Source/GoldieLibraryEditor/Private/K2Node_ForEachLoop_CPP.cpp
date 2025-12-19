// Fill out your copyright notice in the Description page of Project Settings.

#include "K2Node_ForEachLoop_CPP.h"

void UK2Node_ForEachLoop_CPP::GetMenuActions(FBlueprintActionDatabaseRegistrar& ActionRegistrar) const
{
    UClass* ActionKey = GetClass();
    if (ActionRegistrar.IsOpenForRegistration(ActionKey))
    {
        UBlueprintNodeSpawner* NodeSpawner = UBlueprintNodeSpawner::Create(GetClass());
        check(NodeSpawner);

        ActionRegistrar.AddBlueprintAction(ActionKey, NodeSpawner);
    }
}

// Title of the Node
FText UK2Node_ForEachLoop_CPP::GetNodeTitle(ENodeTitleType::Type TitleType) const
{
    return FText::FromString("For Each Loop (C++)");
}

// The Bold Tooltip when hovering over the node (and when hovering over the add button)
FText UK2Node_ForEachLoop_CPP::GetTooltipText() const
{
    return FText::FromString("A faster For Each Loop coded in C++ instead of Blueprints");
}

// The Normal Tooltip when hovering over the node
FText UK2Node_ForEachLoop_CPP::GetToolTipHeading() const
{
    return FText::FromString("C++ coded For Each Loop");
}

// Keywords
FText UK2Node_ForEachLoop_CPP::GetKeywords() const
{
    return FText::FromString("ForEach C++ cpp Faster Goldie");
}

// Title Bar Color
FLinearColor UK2Node_ForEachLoop_CPP::GetNodeTitleColor() const
{
    return FLinearColor::Blue;
}

// Body Color
FLinearColor UK2Node_ForEachLoop_CPP::GetNodeBodyTintColor() const
{
    return FLinearColor(1,0,1,1);
}

// On Node Created
void UK2Node_ForEachLoop_CPP::AllocateDefaultPins()
{
    Super::AllocateDefaultPins();

    // Execute Pin
    CreatePin(EGPD_Input, UEdGraphSchema_K2::PC_Exec, UEdGraphSchema_K2::PN_Execute);
    UEdGraphPin* ArrayPin = CreatePin(EGPD_Input, UEdGraphSchema_K2::PC_Wildcard, TEXT("Array"));
    ArrayPin->PinType.ContainerType = EPinContainerType::Array;

    // Loop Body and Completed
    CreatePin(EGPD_Output, UEdGraphSchema_K2::PC_Exec, TEXT("Loop Body"));
    CreatePin(EGPD_Output, UEdGraphSchema_K2::PC_Wildcard, TEXT("Array Element"));
    CreatePin(EGPD_Output, UEdGraphSchema_K2::PC_Int, TEXT("Array Index"));
    CreatePin(EGPD_Output, UEdGraphSchema_K2::PC_Exec, TEXT("Completed"));
}

// Wildcard Support
void UK2Node_ForEachLoop_CPP::NotifyPinConnectionListChanged(UEdGraphPin* Pin)
{
    Super::NotifyPinConnectionListChanged(Pin);

    UEdGraphPin* InputPin = FindPin(TEXT("Array"));
    UEdGraphPin* OutputPin = FindPin(TEXT("Array Element"));

    if (InputPin->LinkedTo.Num() == 0 && OutputPin->LinkedTo.Num() == 0)
    {
        // Reset input pin to wildcard
        InputPin->PinType.PinCategory = UEdGraphSchema_K2::PC_Wildcard;
        InputPin->PinType.PinSubCategory = TEXT("");
        InputPin->PinType.PinSubCategoryObject = nullptr;

        // Reset output pin to wildcard
        OutputPin->PinType.PinCategory = UEdGraphSchema_K2::PC_Wildcard;
        OutputPin->PinType.PinSubCategory = TEXT("");
        OutputPin->PinType.PinSubCategoryObject = nullptr;
    }
    else if ((Pin == InputPin || Pin == OutputPin) && Pin->LinkedTo.Num() > 0 && Pin->LinkedTo[0]->PinType.PinCategory != UEdGraphSchema_K2::PC_Wildcard)
    {
        // Set the wildcard pin type to the connected pin type.
        Pin->PinType = Pin->LinkedTo[0]->PinType;

        // Update all wildcard pins to have the same type.
        InputPin->PinType.PinCategory = Pin->PinType.PinCategory;
        OutputPin->PinType.PinCategory = Pin->PinType.PinCategory;

        // Break any connection if it's no longer valid.
        UEdGraphSchema_K2::ValidateExistingConnections(InputPin);
        UEdGraphSchema_K2::ValidateExistingConnections(OutputPin);
    }
}

void UK2Node_ForEachLoop_CPP::ExpandNode(FKismetCompilerContext& CompilerContext, UEdGraph* SourceGraph)
{
    Super::ExpandNode(CompilerContext, SourceGraph);

    // Get pins from the node
    UEdGraphPin* ExecPin = FindPin(TEXT("Execute"));
    UEdGraphPin* ArrayPin = FindPin(TEXT("Array"));
    UEdGraphPin* LoopBodyPin = FindPin(TEXT("Loop Body"));
    UEdGraphPin* CompletedPin = FindPin(TEXT("Completed"));
    UEdGraphPin* ElementPin = FindPin(TEXT("Array Element"));
    UEdGraphPin* IndexPin = FindPin(TEXT("Array Index"));
}