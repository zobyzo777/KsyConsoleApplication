#include "pch.h"
#include "PlayerCharacter.h"
#include "BaseCharacter.h"

PlayerCharacter::PlayerCharacter(int InTID)
{
	std::cout << "PlayerCharacter ������ ȣ��\n";
	SetCharacter(ECharacterType::Player, InTID);	
}

PlayerCharacter::~PlayerCharacter()
{
	std::cout << "~PlayerCharacter �Ҹ��� ȣ��\n";
}