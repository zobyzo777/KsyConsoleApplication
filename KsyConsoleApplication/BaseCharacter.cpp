#include "pch.h"
#include "BaseCharacter.h"
#include <iostream>
#include <stdio.h>

static int staticUniqID = 0;

BaseCharacter::BaseCharacter()
{
	std::cout << "BaseCharacter ������ ȣ��\n";
	InitStatData();
}

BaseCharacter::~BaseCharacter()
{
	std::cout << "~BaseCharacter �Ҹ��� ȣ��\n";
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

	//..���̺��� �ִٸ� ���̺� ���� �ε�..
	
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
	//���� ���
	int iResultDamate = InAttacker->GetAttackValue() - GetDefValue();
	iResultDamate = iResultDamate < 0 ? 0 : iResultDamate;

	//ü�� ����
	iHpValue -= iResultDamate;
	iHpValue = iHpValue < 0 ? 0 : iHpValue;

	LogDamage(InAttacker);
	
	//���� ó��
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

	printf("[���� ����] ������ = %s, uid = %d, �ǰ��� = %s, uid = %d, hp = %d \n", attackerText.c_str(), InAttacker->GetUID(), DefenderText.c_str(), GetUID(), iHpValue);
}

void BaseCharacter::LogDeath(shared_ptr<ICharacter> InAttacker, shared_ptr<ICharacter> Defender)
{
	string attackerText = FactoryCharacter::GetInstance().EnumToString(InAttacker->GetCharacterType());
	string DefenderText = FactoryCharacter::GetInstance().EnumToString(GetCharacterType());
	const int iReviveCount = FactoryCharacter::GetInstance().GetCharacterList(Defender->GetCharacterType()).size();

	printf("[���� ����] ������ = %s, uid = %d, �ǰ��� = %s, uid = %d, ���������� = %d \n", attackerText.c_str(), InAttacker->GetUID(), DefenderText.c_str(), GetUID(), iReviveCount);
}