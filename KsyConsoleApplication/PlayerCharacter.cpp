#include "pch.h"
#include "PlayerCharacter.h"
#include "BaseCharacter.h"

PlayerCharacter::PlayerCharacter(int InTID)
{
	std::cout << "PlayerCharacter 생성자 호출\n";
	SetCharacter(ECharacterType::Player, InTID);	
}

PlayerCharacter::~PlayerCharacter()
{
	std::cout << "~PlayerCharacter 소멸자 호출\n";
}