#include "pch.h"
#include "NpcCharacter.h"

NpcCharacter::NpcCharacter(int InTID)
{
	std::cout << "NpcCharacter 생성자 호출\n";
	SetCharacter(ECharacterType::Npc, InTID);
}

NpcCharacter::~NpcCharacter()
{
	std::cout << "~NpcCharacter 소멸자 호출\n";
}
