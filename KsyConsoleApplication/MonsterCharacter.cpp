#include "pch.h"
#include "MonsterCharacter.h"

MonsterCharacter::MonsterCharacter(int InTID)
{
	std::cout << "MonsterCharacter 생성자 호출\n";
	SetCharacter(ECharacterType::Monster, InTID);
}

MonsterCharacter::~MonsterCharacter()
{
	std::cout << "~MonsterCharacter 소멸자 호출\n";
}
