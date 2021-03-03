#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Engine/DataTable.h"
#include "BlueprintCallable.generated.h"

USTRUCT(BlueprintType, Category = "Dhuma|Room Data")
struct FRoomData : public FTableRowBase
{
	GENERATED_USTRUCT_BODY();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dhuma|Room Data")
		FString Name;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dhuma|Room Data")
		int Spawned;
};

UCLASS()
class DHUMATOOLS_API UBlueprintCallable : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "Dhuma|Room Data")
		static TArray<FString> GetListOfSpawnedRoom(TArray<AActor*> Actors);
	UFUNCTION(BlueprintCallable, Category = "Dhuma|Room Data")
		static TArray<FRoomData> GetRoomStats(TArray<FString> ListOfRoom, UDataTable* DataTable);
};
