#include "pch.h"
#include "NpcCharacter.h"

NpcCharacter::NpcCharacter(int InTID)
{
	std::cout << "NpcCharacter ������ ȣ��\n";
	SetCharacter(ECharacterType::Npc, InTID);
}

NpcCharacter::~NpcCharacter()
{
	std::cout << "~NpcCharacter �Ҹ��� ȣ��\n";
}
