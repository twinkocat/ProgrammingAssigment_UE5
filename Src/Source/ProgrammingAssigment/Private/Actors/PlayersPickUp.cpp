// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/PlayersPickUp.h"
#include "Features/Inventory/InventoryComponent.h"
#include "Features/Inventory/InventoryItem.h"
#include "Net/UnrealNetwork.h"


// Sets default values
APlayersPickUp::APlayersPickUp()
{
	PrimaryActorTick.bCanEverTick = false;
}

void APlayersPickUp::BeginPlay()
{
	Super::BeginPlay();
	ItemWrapperChanged();
}

void APlayersPickUp::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(APlayersPickUp, ItemImage);
}

void APlayersPickUp::OnRep_ItemImage()
{
	ItemWrapperChanged();
}

void APlayersPickUp::SetupItem_Implementation(const FInventoryItemWrapper& Wrapper)
{
	Server_SetupItem(Wrapper);
}

void APlayersPickUp::Server_SetupItem_Implementation(const FInventoryItemWrapper& Wrapper)
{
	SetupItem_Internal(Wrapper);	
}

void APlayersPickUp::SetupItem_Internal(const FInventoryItemWrapper& Wrapper)
{
	ItemToAdd = Wrapper.Tag;
	CountToAdd = Wrapper.Count;
	ItemImage = Wrapper.Item->GetImage();
	ItemWrapperChanged();
}

void APlayersPickUp::ItemWrapperChanged()
{
	if (!HasActorBegunPlay())
	{
		return;
	}
	OnItemSetup.Broadcast();
}
