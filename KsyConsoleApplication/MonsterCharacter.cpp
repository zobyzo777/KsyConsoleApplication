#include "pch.h"
#include "MonsterCharacter.h"

MonsterCharacter::MonsterCharacter(int InTID)
{
	std::cout << "MonsterCharacter ������ ȣ��\n";
	SetCharacter(ECharacterType::Monster, InTID);
}

MonsterCharacter::~MonsterCharacter()
{
	std::cout << "~MonsterCharacter �Ҹ��� ȣ��\n";
}
