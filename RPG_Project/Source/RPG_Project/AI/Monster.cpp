// Fill out your copyright notice in the Description page of Project Settings.


#include "Monster.h"
#include "../Global/GlobalGameInstance.h"
#include "MyAIController.h"
#include "../Global/GlobalEnums.h"
#include "MonsterData.h"
#include "Kismet/GameplayStatics.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Components/CapsuleComponent.h"
#include "../MainPlayer/MainPlayerCharacter.h"
#include "../Global/Projectile.h"

AMonster::AMonster()
{

}

void AMonster::BeginPlay()
{	
	// Super::BeginPlay();


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
	GetBlackboardComponent()->SetValueAsFloat(TEXT("AttackRange"), 50.0f);
	GetBlackboardComponent()->SetValueAsFloat(TEXT("SearchRange"), 500.0f);

	GetBlackboardComponent()->SetValueAsVector(TEXT("OriginPos"), GetActorLocation());

	GetBlackboardComponent()->SetValueAsBool(TEXT("bIsDeath"), false);

	CapsuleComp = GetCapsuleComponent();
	CapsuleComp->OnComponentBeginOverlap.AddDynamic(this, &AMonster::BeginOverlap);

	GetBlackboardComponent()->SetValueAsBool(TEXT("SpawnCoin"), false);

	GetBlackboardComponent()->SetValueAsFloat(TEXT("Monster1HP"), 0.3f); // ������ Monster1HP SET
}

void AMonster::Tick(float DeltaSecond)
{
	Super::Tick(DeltaSecond);
}

void AMonster::BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	
		AMainPlayerCharacter* Player = Cast<AMainPlayerCharacter>(OtherActor);
		if (nullptr != Player)
		{
			
			// �÷��̾��� �ִ� �ν��Ͻ� ��������
			UMainPlayerAnimInstance* PlayerAnimInstance = Player->GetMainPlayerAnimInstance();
			if (PlayerAnimInstance)
			{
				if (PlayerAnimInstance->GetCurrentAnimationState() == EAniState::Attack)
				{
					isoverlap = false; // �÷��̾ �������϶���, hp ���� x
					GetBlackboardComponent()->SetValueAsBool(TEXT("bIsDeath"), true); // BTTASK_BASE ���� �� ���� ���� �������� BTTASK_DEATH �ҷ���
				}
				else
				{
					isoverlap = true;
					GetBlackboardComponent()->SetValueAsBool(TEXT("bIsDeath"), false);
				}
			}
		}
}

//UGlobalGameInstance* AMonster::GetGlobalGameInstance()
//{
//	UGlobalGameInstance* inst = Cast<UGlobalGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
//	if (nullptr != inst)
//	{
//		int a = 0;
//		return inst;
//	}
//	return nullptr;
//}