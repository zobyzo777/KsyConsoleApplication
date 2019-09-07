#include "pch.h"
#include <deque>
#include <time.h>
#include "FactoryCharacter.h"
#include "BaseCharacter.h"
#include "PlayerCharacter.h"
#include "NpcCharacter.h"
#include "MonsterCharacter.h"

using namespace std;

//싱글턴 인스턴스
FactoryCharacter* FactoryCharacter::instance_ = nullptr;
//Rand Seed 정보
static unsigned StaticRandSeed = 0;

FactoryCharacter::FactoryCharacter()
{
}

FactoryCharacter::~FactoryCharacter()
{
}

FactoryCharacter& FactoryCharacter::GetInstance()
{
	if (instance_ == nullptr)
		instance_ = new FactoryCharacter();

	return *instance_;
}

void FactoryCharacter::FactoryDestroy()
{
	delete instance_;
}

weak_ptr<ICharacter> FactoryCharacter::CreatePlayer(int InTID)
{
	shared_ptr<ICharacter> LocalPlayer(new PlayerCharacter(InTID));
	LocalPlayerList.push_back(LocalPlayer);
	return LocalPlayer;
}

weak_ptr<ICharacter> FactoryCharacter::CreateNpc(int InTID)
{
	shared_ptr<ICharacter> LocalNpc(new NpcCharacter(InTID));
	LocalNpcList.push_back(LocalNpc);
	return LocalNpc;
}

weak_ptr<ICharacter> FactoryCharacter::CreateMonster(int InTID)
{
	shared_ptr<ICharacter> LocalMonster(new MonsterCharacter(InTID));
	LocalMonsterList.push_back(LocalMonster);
	return LocalMonster;
}

std::list<std::shared_ptr<ICharacter>>& FactoryCharacter::GetCharacterList(const ECharacterType& InType)
{
	switch (InType)
	{
	case ECharacterType::Player:
		return LocalPlayerList;
	case ECharacterType::Npc:
		return LocalNpcList;
	default:
		return LocalMonsterList;
	}
}

void FactoryCharacter::SetRemoveCharacter(shared_ptr<ICharacter>& InDeathCharacter)
{
	if (InDeathCharacter)
	{
		list<shared_ptr<ICharacter>>& CharacterList = GetCharacterList(InDeathCharacter->GetCharacterType());

		list<shared_ptr<ICharacter>>::iterator It;
		int iIndex = 0;
		for (It = CharacterList.begin(); It != CharacterList.end(); It++)
		{
			if ((*It)->GetUID() == InDeathCharacter->GetUID())
			{
				CharacterList.erase(It);
				break;
			}
			iIndex++;
		}
	}
}

std::string FactoryCharacter::EnumToString(const ECharacterType& InType)
{
	string strText = "";
	switch (InType)
	{
	case ECharacterType::Player:
		strText = "플레이어";
		break;
	case ECharacterType::Npc:
		strText = "NPC";
		break;
	case ECharacterType::Monster:
		strText = "몬스터";
		break;
	}

	return strText;
}

std::shared_ptr<ICharacter> FactoryCharacter::GetCharacter(const ECharacterType& InType, const int InUID)
{
	list<shared_ptr<ICharacter>> CharacterList = GetCharacterList(InType);
	list<shared_ptr<ICharacter>>::iterator It;

	for (It = CharacterList.begin(); It != CharacterList.end(); It++)
	{
		if ((*It)->GetUID() == InUID)
			return *It;
	}

	return nullptr;
}

vector<ECharacterType> FactoryCharacter::GetAbleBattleCharacterTypeVector()
{
	vector<ECharacterType> CharacterTypeVector;
	if (LocalPlayerList.size() > 0)
		CharacterTypeVector.push_back(ECharacterType::Player);

	if (LocalNpcList.size() > 0)
		CharacterTypeVector.push_back(ECharacterType::Npc);

	if (LocalMonsterList.size() > 0)
		CharacterTypeVector.push_back(ECharacterType::Monster);

	return CharacterTypeVector;
}

weak_ptr<ICharacter> FactoryCharacter::GetRandTypeCharacter(vector<ECharacterType>& InCharacterTypeVector)
{
	weak_ptr<ICharacter> WeakCharacter;
	
	//랜덤으로 공격자&피격자 Type 지정
	srand((unsigned int)time(0) + ++StaticRandSeed);
	signed int iCharacterTypeSize = InCharacterTypeVector.size();
	signed int iRandIndex = rand() %  iCharacterTypeSize;

	if (iCharacterTypeSize > iRandIndex)
	{
		vector<ECharacterType>::iterator Iter = InCharacterTypeVector.begin();
		Iter += iRandIndex;
		list<shared_ptr<ICharacter>>& CharacterList = GetCharacterList(*Iter);		
		iRandIndex = rand() % CharacterList.size();

		int iIndex = 0;
		list<shared_ptr<ICharacter>>::iterator It;		
		for (It = CharacterList.begin(); It != CharacterList.end(); It++)
		{
			if ((*It) == nullptr)
			{
				break;
			}

			if (iIndex == iRandIndex)
			{
				WeakCharacter = *It;
				break;
			}
			iIndex++;
		}

		InCharacterTypeVector.erase(Iter);
	}

	return WeakCharacter;
}