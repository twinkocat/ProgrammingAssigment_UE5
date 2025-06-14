// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/PlayersPickUp.h"
#include "Features/Inventory/InventoryComponent.h"
#include "Net/UnrealNetwork.h"


// Sets default values
APlayersPickUp::APlayersPickUp()
{
	PrimaryActorTick.bCanEverTick = false;
}

void APlayersPickUp::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(APlayersPickUp, ItemWrapper)
}

void APlayersPickUp::OnRep_ItemWrapper()
{
	ItemToAdd = ItemWrapper.Tag;
	CountToAdd = ItemWrapper.Count;
	OnItemSetup.Broadcast(ItemWrapper);
}

void APlayersPickUp::SetupItem_Implementation(const FInventoryItemWrapper& Item)
{
	ItemWrapper = Item;
	OnRep_ItemWrapper();
}
