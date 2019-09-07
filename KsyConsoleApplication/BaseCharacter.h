#pragma once
#include <combaseapi.h>
#include <vector>
#include <list>
#include <iostream>

using namespace std;

enum ECharacterType
{
	None = 0,
	Player,
	Npc,
	Monster,
	Max
};

interface ICharacter
{
public:
	virtual ~ICharacter() { std::cout << "~ICharacter 소멸자 호출\n"; };	//인터페이스 소멸자가 필요한가? 필요하다면 왜?

	
	virtual void SetCharacter(const ECharacterType& InCharacterType, int InCharacterID) = 0;
	//캐릭터 공격
	virtual void SetAttack(shared_ptr<ICharacter>& InAttackedCharacter) = 0;
	//캐릭터 피해
	virtual void SetDamage(shared_ptr<ICharacter>& InAttacker) = 0;
	//캐릭터 이동
	virtual void SetMove(int InMoveSlot) = 0;
	
	//캐릭터 타입
	virtual const ECharacterType& GetCharacterType() = 0;
	//캐릭터 TableID
	virtual int GetTID() = 0;
	//캐릭터 유저ID
	virtual int GetUID() = 0;
	//캐릭터 공격력
	virtual int GetAttackValue() = 0;
	//캐릭터 방어력
	virtual int GetDefValue() = 0;
	//캐릭터 체력
	virtual int GetHpValue() = 0;
};

class BaseCharacter : public ICharacter
{
public:
	BaseCharacter();
	virtual ~BaseCharacter();

protected:
	//캐릭터 초기화
	void SetCharacter(const ECharacterType& InCharacterType, int InTID);

	virtual const ECharacterType& GetCharacterType() override { return eCharacterType; };
	virtual int GetTID() override { return iTID; }
	virtual int GetUID() override { return iUID; }
	virtual int GetAttackValue() override { return iAttackValue; }
	virtual int GetDefValue() override { return iDefValue; }
	virtual int GetHpValue() override { return iHpValue; }
private:

	virtual void SetAttack(shared_ptr<ICharacter>& InAttackedCharacter) override;
	virtual void SetDamage(shared_ptr<ICharacter>& InAttacker) override;
	virtual void SetMove(int InMoveSlot) override;


	void LogDamage(shared_ptr<ICharacter> InAttacker);
	void LogDeath(shared_ptr<ICharacter> InAttacker, shared_ptr<ICharacter> Defender);

private:
	//스탯 초기화 함수
	void InitStatData();

private:
	ECharacterType eCharacterType;
	int iTID;
	int iUID;
	int iAttackValue;
	int iDefValue;
	int iHpValue;
};

