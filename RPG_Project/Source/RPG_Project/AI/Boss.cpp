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
#include "Components/AudioComponent.h"
#include "../Global/Projectile.h"

ABoss::ABoss()
{

}

void ABoss::BeginPlay()
{	
	// Super::BeginPlay();
	SetAllSound(MapSound);

	if (nullptr == AudioComponent)
	{
		// ����÷��̿��� �ѹ��� ã�°� ���� ����.
		AudioComponent = Cast<UAudioComponent>(GetComponentByClass(UAudioComponent::StaticClass()));
		AudioComponent->Stop();
	}

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
	GetBlackboardComponent()->SetValueAsFloat(TEXT("SearchRange"), 2000.0f);

	GetBlackboardComponent()->SetValueAsVector(TEXT("OriginPos"), GetActorLocation());

	GetBlackboardComponent()->SetValueAsBool(TEXT("bIsDeath"), false);

	CapsuleComp = GetCapsuleComponent();
	CapsuleComp->OnComponentBeginOverlap.AddDynamic(this, &ABoss::BeginOverlap);

	GetBlackboardComponent()->SetValueAsBool(TEXT("SpawnCoin"), false);

	GetBlackboardComponent()->SetValueAsFloat(TEXT("BossMonsterHP"), 4.0f); // ������ BossHP SET

	GlobalAnimInstance->OnPlayMontageNotifyBegin.AddDynamic(this, &ABoss::AnimNotifyBegin);
}

void ABoss::Tick(float DeltaSecond)
{
	Super::Tick(DeltaSecond);
}

void ABoss::BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	int a = 0;
	// �÷��̾��� �Ѿ˿� �¾������. hp ����
	AProjectile* Projectile = Cast<AProjectile>(OtherActor);
	if (Projectile != nullptr)
	{
		GetBlackboardComponent()->SetValueAsBool(TEXT("bIsDeath"), true); // �������� death��
	}
}
//void ABoss::EndOverlap(UPrimitiveComponent* OverlappedComponent,
//	AActor* OtherActor,
//	UPrimitiveComponent* OtherComp,
//	int32 OtherBodyIndex)
//{
//	int a = 0;
//	GetBlackboardComponent()->SetValueAsBool(TEXT("bIsDeath"), false); // �������� death false��
//}


void ABoss::AnimNotifyBegin(FName NotifyName, const FBranchingPointNotifyPayload& BranchingPointPayload)
{
	AudioComponent->SetSound(MapSound[EAniState::Attack]);
	AudioComponent->Play();

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

void ABoss::Setbdeathfalse()
{
	GetBlackboardComponent()->SetValueAsBool(TEXT("bIsDeath"), false);
}