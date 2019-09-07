#include "pch.h"
#include "BaseCharacter.h"
#include <iostream>
#include <stdio.h>

static int staticUniqID = 0;

BaseCharacter::BaseCharacter()
{
	std::cout << "BaseCharacter 생성자 호출\n";
	InitStatData();
}

BaseCharacter::~BaseCharacter()
{
	std::cout << "~BaseCharacter 소멸자 호출\n";
}

void BaseCharacter::InitStatData()
{
	eCharacterType = ECharacterType::None;
	iTID = 0;
	iUID = 0;
	iAttackValue = 0;
	iDefValue = 0;
	iHpValue = 0;
}

void BaseCharacter::SetCharacter(const ECharacterType& InCharacterType, int InTID)
{
	eCharacterType = InCharacterType;
	iTID = InTID;
	iUID = ++staticUniqID;

	//..테이블이 있다면 테이블 정보 로드..
	
	switch (InCharacterType)
	{
	case ECharacterType::Player:
	{
		iAttackValue = 4;
		iDefValue = 2;
		iHpValue = 9;
	}break;

	case ECharacterType::Npc:
	{
		iAttackValue = 4;
		iDefValue = 2;
		iHpValue = 9;
	}break;

	case ECharacterType::Monster:
	{
		iAttackValue = 4;
		iDefValue = 2;
		iHpValue = 9;
	}break;
	}
}

void BaseCharacter::SetAttack(shared_ptr<ICharacter>& InAttackedCharacter)
{
	if (shared_ptr<ICharacter> Attacker = FactoryCharacter::GetInstance().GetCharacter(GetCharacterType(), GetUID()))
		InAttackedCharacter->SetDamage(Attacker);
}

void BaseCharacter::SetDamage(shared_ptr<ICharacter>& InAttacker)
{
	//피해 계산
	int iResultDamate = InAttacker->GetAttackValue() - GetDefValue();
	iResultDamate = iResultDamate < 0 ? 0 : iResultDamate;

	//체력 감산
	iHpValue -= iResultDamate;
	iHpValue = iHpValue < 0 ? 0 : iHpValue;

	LogDamage(InAttacker);
	
	//죽음 처리
	if (iHpValue <= 0)
	{
		if (shared_ptr<ICharacter> Defender = FactoryCharacter::GetInstance().GetCharacter(GetCharacterType(), GetUID()))
		{
			FactoryCharacter::GetInstance().SetRemoveCharacter(Defender);

			LogDeath(InAttacker, Defender);			
		}			
	}		
}

void BaseCharacter::SetMove(int InMoveSlot)
{
	//..
}

void BaseCharacter::LogDamage(shared_ptr<ICharacter> InAttacker)
{
	string attackerText = FactoryCharacter::GetInstance().EnumToString(InAttacker->GetCharacterType());
	string DefenderText = FactoryCharacter::GetInstance().EnumToString(GetCharacterType());

	printf("[피해 정보] 공격자 = %s, uid = %d, 피격자 = %s, uid = %d, hp = %d \n", attackerText.c_str(), InAttacker->GetUID(), DefenderText.c_str(), GetUID(), iHpValue);
}

void BaseCharacter::LogDeath(shared_ptr<ICharacter> InAttacker, shared_ptr<ICharacter> Defender)
{
	string attackerText = FactoryCharacter::GetInstance().EnumToString(InAttacker->GetCharacterType());
	string DefenderText = FactoryCharacter::GetInstance().EnumToString(GetCharacterType());
	const int iReviveCount = FactoryCharacter::GetInstance().GetCharacterList(Defender->GetCharacterType()).size();

	printf("[죽음 정보] 공격자 = %s, uid = %d, 피격자 = %s, uid = %d, 남은생존자 = %d \n", attackerText.c_str(), InAttacker->GetUID(), DefenderText.c_str(), GetUID(), iReviveCount);
}