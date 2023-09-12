// Fill out your copyright notice in the Description page of Project Settings.


#include "Boss.h"
#include "../Global/GlobalGameInstance.h"
#include "MyAIController.h"
#include "../Global/GlobalEnums.h"
#include "MonsterData.h"
#include "Kismet/GameplayStatics.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Components/CapsuleComponent.h"
#include "../Stage3/MainPlayerCharacter3.h"
#include "../Global/Projectile.h"
#include "../Global/Fire.h"

ABoss::ABoss()
{

}

void ABoss::BeginPlay()
{	
	// Super::BeginPlay();

	GlobalAnimInstance = Cast<UGlobalAnimInstance>(GetMesh()->GetAnimInstance());

	UGlobalGameInstance* GameInst = GetWorld()->GetGameInstance<UGlobalGameInstance>();

	if (nullptr != GameInst) // �۷ι������ν��Ͻ��� ���ؼ�
								// �ִϽ�����Ʈ�� �ִϸ��̼��� �������ش�
	{
		CurMonsterData = GameInst->GetMonsterData(DataName); // ���� ���͵����Ϳ� ���� �־��ְ�

		SetAllAnimation(CurMonsterData->MapAnimation);
		SetAniState(EAniState::None);
	}
	Super::BeginPlay();

	GetBlackboardComponent()->SetValueAsEnum(TEXT("AIAniState"), static_cast<uint8>(EAniState::Idle));
	GetBlackboardComponent()->SetValueAsString(TEXT("TargetTag"), TEXT("Player"));
	GetBlackboardComponent()->SetValueAsFloat(TEXT("AttackRange"), 1500.0f);
	GetBlackboardComponent()->SetValueAsFloat(TEXT("SearchRange"), 3000.0f);

	GetBlackboardComponent()->SetValueAsVector(TEXT("OriginPos"), GetActorLocation());

	GetBlackboardComponent()->SetValueAsBool(TEXT("bIsDeath"), false);

	CapsuleComp = GetCapsuleComponent();
	CapsuleComp->OnComponentBeginOverlap.AddDynamic(this, &ABoss::BeginOverlap);

	GetBlackboardComponent()->SetValueAsBool(TEXT("SpawnCoin"), false);

	GetBlackboardComponent()->SetValueAsFloat(TEXT("Boss1HP"), 0.3f); // ������ BossHP SET

	GlobalAnimInstance->OnPlayMontageNotifyBegin.AddDynamic(this, &ABoss::AnimNotifyBegin);
}

void ABoss::Tick(float DeltaSecond)
{
	Super::Tick(DeltaSecond);
}

void ABoss::BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	// �÷��̾��� �Ѿ˿� �¾������. hp ����
}
void ABoss::AnimNotifyBegin(FName NotifyName, const FBranchingPointNotifyPayload& BranchingPointPayload)
{
	UGlobalGameInstance* Inst = GetWorld()->GetGameInstance<UGlobalGameInstance>();

	TSubclassOf<UObject> Fire = Inst->GetSubClass(TEXT("Fire"));

	TArray<UActorComponent*> FireEffects = GetComponentsByTag(USceneComponent::StaticClass(), TEXT("FireEffect"));
	USceneComponent* FireCom = Cast<USceneComponent>(FireEffects[0]);

	FVector Pos = FireCom->GetComponentToWorld().GetLocation();

	if (nullptr != Fire)
	{
		{	// �߻�ü �����
			AActor* Actor = GetWorld()->SpawnActor<AActor>(Fire);
			FireActor = Cast<AFire>(Actor);

			FireActor->SetActorLocation(Pos);
			FireActor->SetActorRotation(GetActorRotation());
			FireActor->Tags.Add(FName("MonsterAttack"));
			FireActor->GetSphereComponent()->SetCollisionProfileName(TEXT("MonsterAttack"), true);
		}
	}
}

void ABoss::DestroyAttackEffect()
{
	if (AttackEffect)
	{
		AttackEffect->Destroy();
		AttackEffect = nullptr;
	}
}