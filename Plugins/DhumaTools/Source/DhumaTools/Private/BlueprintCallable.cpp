#include "BlueprintCallable.h"

#define PRINT(Time, Message, ...) if (GEngine) { GEngine->AddOnScreenDebugMessage(-1, Time, FColor::Yellow, Message), __VA_ARGS__; }

TArray<FString> UBlueprintCallable::GetListOfSpawnedRoom(TArray<AActor*> Actors)
{
	TArray<FString> ListOfSpawnedRoom;

	for (int i = 0; i < Actors.Num(); i++)
	{
		FString Name, Code;
		Actors[i]->GetLevel()->GetOuter()->GetName().Split("_LI_", &Name, &Code);
		ListOfSpawnedRoom.Add(Name);
	}

	return ListOfSpawnedRoom;
}

TArray<FRoomData> UBlueprintCallable::GetRoomStats(TArray<FString> ListOfRoom, UDataTable* DataTable)
{
	TMap<FString, int> ListOfUsedRoom;

	for (int i = 0; i < ListOfRoom.Num(); i++)
	{
		int Count = 1;

		if (ListOfUsedRoom.Contains(ListOfRoom[i]))
			Count = ++ListOfUsedRoom[ListOfRoom[i]];

		ListOfUsedRoom.Add(ListOfRoom[i], Count);
	}

	TArray<FRoomData>ListOfRoomData;

	DataTable->EmptyTable();

	for (const TPair<FString, int>& Data : ListOfUsedRoom)
	{
		FRoomData RoomData;
		RoomData.Name = Data.Key;
		RoomData.Spawned = Data.Value;

		ListOfRoomData.Add(RoomData);
		DataTable->AddRow(*Data.Key, RoomData);
	}

	return ListOfRoomData;
}
