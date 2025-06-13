// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/PlayersPickUp.h"
#include "Features/Inventory/InventoryComponent.h"
#include "Net/UnrealNetwork.h"


// Sets default values
APlayersPickUp::APlayersPickUp()
{
	PrimaryActorTick.bCanEverTick = false;
}

void APlayersPickUp::SetupItem_Implementation(const FInventoryItemWrapper& Item)
{
	ItemToAdd = Item.Tag;
	CountToAdd = Item.Count;
}
