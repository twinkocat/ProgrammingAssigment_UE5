// Copyright (C) Varian Daemon 2023. All Rights Reserved.


#include "Core/LayeredUI_AsyncFunctions.h"

#include "Blueprint/UserWidget.h"
#include "Core/LayeredUI_Subsystem.h"
#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"

ULayeredUI_AddWidgetToLayer* ULayeredUI_AddWidgetToLayer::AddWidgetToLayer_Async(TSoftClassPtr<UUserWidget> Widget, FGameplayTag Layer, UObject* Context)
{
	ULayeredUI_AddWidgetToLayer* NewAsyncObject = NewObject<ULayeredUI_AddWidgetToLayer>(Context);
	NewAsyncObject->WidgetToLoad = Widget;
	NewAsyncObject->LayerDestination = Layer;
	NewAsyncObject->WidgetOwner = Context;
	return NewAsyncObject;
}

void ULayeredUI_AddWidgetToLayer::Activate()
{
	Super::Activate();

	Handle = StreamableManager.RequestAsyncLoad(WidgetToLoad.ToSoftObjectPath(), [this]()
	{
		//Send job to background thread.
		FLayeredWidget NewLayeredWidget;
		bool JobSuccessful = false;
		if(IsValid(WidgetToLoad.Get()))
		{
			ULayeredUI_Subsystem* LayeredUI_Subsystem = UGameplayStatics::GetPlayerController(WidgetOwner, 0)->GetLocalPlayer()->GetSubsystem<ULayeredUI_Subsystem>();

			if(!LayeredUI_Subsystem)
			{
				//Blueprints might be listening to Fail, make sure to broadcast on game thread.
				AsyncTask(ENamedThreads::GameThread, [this, NewLayeredWidget]()
				{
					Fail.Broadcast(NewLayeredWidget);
					RemoveFromRoot();
				});
					
				return;
			}

			// Get widget class	 
			if (UUserWidget* WidgetToCreate = Cast<UUserWidget>(WidgetToLoad->GetDefaultObject()))
			{
				// AddWidgetToLayer needed a class of UserWidget
				// directly creating not necessary 
				LayeredUI_Subsystem->AddWidgetToLayer_Internal(WidgetToCreate ,LayerDestination, NewLayeredWidget);
			}
			
			if(IsValid(NewLayeredWidget.Widget))
			{
				JobSuccessful = true;
			}
		}

		if(JobSuccessful)
		{
			Success.Broadcast(NewLayeredWidget);
			RemoveFromRoot();
		}
		else
		{
			Fail.Broadcast(NewLayeredWidget);
			RemoveFromRoot();
		}
	});
}
