#pragma once

#include "CoreMinimal.h"
#include "MotionControllerComponent.h"
#include "Components/VRHandSkeletalMeshComponent.h"
#include "Animation/VRHandAnimInstance.h"
#include "EnhancedInputComponent.h"
#include "InputActionValue.h"
#include "InputMappingContext.h"
#include "InputAction.h"
#include "HandGraph.generated.h"

UCLASS()
class CRYPTRIDER_API UVRInputDataConfig : public UObject
{
    GENERATED_BODY()

public:
    UVRInputDataConfig();

    UInputMappingContext* InputMappingContext = nullptr;

public:
    UInputAction* IA_Grab_Left = nullptr;
    UInputAction* IA_Grab_Right = nullptr;

    UInputAction* IA_Point_Left = nullptr;
    UInputAction* IA_Point_Right = nullptr;

    UInputAction* IA_IndexCurl_Left = nullptr;
    UInputAction* IA_IndexCurl_Right = nullptr;

    UInputAction* IA_Thumb_Left = nullptr;
    UInputAction* IA_Thumb_Right = nullptr;
};

UCLASS()
class CRYPTRIDER_API UHandGraph : public UObject
{
    GENERATED_BODY()

public:
    enum class EHandType
    {
        Left,
        Right
    };

public:
    void SetupPlayerInputComponent(UMotionControllerComponent* InMotionControllerComponent, UEnhancedInputComponent* InputComponent);
    void OnGrabTriggered(const FInputActionValue& InputActionValue);
    void OnGrabCompleted(const FInputActionValue& InputActionValue);

    void OnPointStarted(const FInputActionValue& InputActionValue);
    void OnPointCompleted(const FInputActionValue& InputActionValue);

    void OnIndexCurlTriggered(const FInputActionValue& InputActionValue);
    void OnIndexCurlCompleted(const FInputActionValue& InputActionValue);

    void OnThumbStarted(const FInputActionValue& InputActionValue);
    void OnThumbCompleted(const FInputActionValue& InputActionValue);

    UMotionControllerComponent* MotionControllerComponent = nullptr;
    UVRHandAnimInstance* VRHandAnimInstance = nullptr;
    EHandType HandType = EHandType::Left; // Set the default value to Left or as needed
};
