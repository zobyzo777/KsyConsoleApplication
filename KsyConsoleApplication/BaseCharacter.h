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
	virtual ~ICharacter() { std::cout << "~ICharacter �Ҹ��� ȣ��\n"; };	//�������̽� �Ҹ��ڰ� �ʿ��Ѱ�? �ʿ��ϴٸ� ��?

	
	virtual void SetCharacter(const ECharacterType& InCharacterType, int InCharacterID) = 0;
	//ĳ���� ����
	virtual void SetAttack(shared_ptr<ICharacter>& InAttackedCharacter) = 0;
	//ĳ���� ����
	virtual void SetDamage(shared_ptr<ICharacter>& InAttacker) = 0;
	//ĳ���� �̵�
	virtual void SetMove(int InMoveSlot) = 0;
	
	//ĳ���� Ÿ��
	virtual const ECharacterType& GetCharacterType() = 0;
	//ĳ���� TableID
	virtual int GetTID() = 0;
	//ĳ���� ����ID
	virtual int GetUID() = 0;
	//ĳ���� ���ݷ�
	virtual int GetAttackValue() = 0;
	//ĳ���� ����
	virtual int GetDefValue() = 0;
	//ĳ���� ü��
	virtual int GetHpValue() = 0;
};

class BaseCharacter : public ICharacter
{
public:
	BaseCharacter();
	virtual ~BaseCharacter();

protected:
	//ĳ���� �ʱ�ȭ
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
	//���� �ʱ�ȭ �Լ�
	void InitStatData();

private:
	ECharacterType eCharacterType;
	int iTID;
	int iUID;
	int iAttackValue;
	int iDefValue;
	int iHpValue;
};

