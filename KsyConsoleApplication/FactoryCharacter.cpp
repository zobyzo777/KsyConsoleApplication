#include "pch.h"
#include <deque>
#include <map>
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
	LocalPlayerMap.insert(make_pair(LocalPlayer->GetUID(), LocalPlayer));
	return LocalPlayer;
}

weak_ptr<ICharacter> FactoryCharacter::CreateNpc(int InTID)
{
	shared_ptr<ICharacter> LocalNpc(new NpcCharacter(InTID));
	LocalNpcMap.insert(make_pair(LocalNpc->GetUID(), LocalNpc));
	return LocalNpc;
}

weak_ptr<ICharacter> FactoryCharacter::CreateMonster(int InTID)
{
	shared_ptr<ICharacter> LocalMonster(new MonsterCharacter(InTID));
	LocalMonsterMap.insert(make_pair(LocalMonster->GetUID(), LocalMonster));
	return LocalMonster;
}

map<int, std::shared_ptr<ICharacter>>& FactoryCharacter::GetCharacterMap(const ECharacterType& InType)
{
	switch (InType)
	{
	case ECharacterType::Player:
		return LocalPlayerMap;
	case ECharacterType::Npc:
		return LocalNpcMap;
	default:
		return LocalMonsterMap;
	}
}

void FactoryCharacter::SetRemoveCharacter(shared_ptr<ICharacter>& InDeathCharacter)
{
	if (InDeathCharacter)
	{
		map<int, shared_ptr<ICharacter>>& CharacterMap = GetCharacterMap(InDeathCharacter->GetCharacterType());
		CharacterMap.erase(InDeathCharacter->GetUID());
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
	map<int, shared_ptr<ICharacter>> CharacterMap = GetCharacterMap(InType);
	map<int, shared_ptr<ICharacter>>::iterator Iter = CharacterMap.find(InUID);
	return Iter->second;
}

vector<ECharacterType> FactoryCharacter::GetAbleBattleCharacterTypeVector()
{
	vector<ECharacterType> CharacterTypeVector;
	if (LocalPlayerMap.size() > 0)
		CharacterTypeVector.push_back(ECharacterType::Player);

	if (LocalNpcMap.size() > 0)
		CharacterTypeVector.push_back(ECharacterType::Npc);

	if (LocalMonsterMap.size() > 0)
		CharacterTypeVector.push_back(ECharacterType::Monster);

	return CharacterTypeVector;
}

weak_ptr<ICharacter> FactoryCharacter::GetRandTypeCharacter(vector<ECharacterType>& InCharacterTypeVector)
{
	weak_ptr<ICharacter> WeakCharacter;
	
	//랜덤으로 공격자&피격자 Type 지정
	srand((unsigned int)time(0) + ++StaticRandSeed);
	size_t iCharacterTypeSize = InCharacterTypeVector.size();
	size_t iRandIndex = (size_t)(rand() %  iCharacterTypeSize);

	if (iCharacterTypeSize > iRandIndex)
	{
		vector<ECharacterType>::iterator Iter = InCharacterTypeVector.begin();
		Iter += iRandIndex;
		map<int, shared_ptr<ICharacter>>& CharacterMap = GetCharacterMap(*Iter);
		iRandIndex = rand() % CharacterMap.size();

		int iIndex = 0;
		map<int, shared_ptr<ICharacter>>::iterator It;		
		for (It = CharacterMap.begin(); It != CharacterMap.end(); It++)
		{
			if (iIndex == iRandIndex)
			{
				WeakCharacter = It->second;
				break;
			}
			iIndex++;
		}

		InCharacterTypeVector.erase(Iter);
	}

	return WeakCharacter;
}