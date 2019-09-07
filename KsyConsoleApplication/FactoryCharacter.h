#pragma once

interface ICharacter;

class FactoryCharacter
{
public:
	FactoryCharacter();
	~FactoryCharacter();

	//�̱��� �ν��Ͻ�
	static FactoryCharacter& GetInstance();
	
	//Factory �� ����Ʈ������ ��ü �޸� �ʱ�ȭ
	static void FactoryDestroy();
	
	//ĳ���� ���� �Լ�
	weak_ptr<ICharacter> CreatePlayer(int InTID);
	weak_ptr<ICharacter> CreateNpc(int InTID);
	weak_ptr<ICharacter> CreateMonster(int InTID);

	//���� ���� ĳ���� Ÿ�� ��ȯ
	vector<ECharacterType> GetAbleBattleCharacterTypeVector();
	
	//������ & �ǰ��� ���� ����
	weak_ptr<ICharacter> GetRandTypeCharacter(vector<ECharacterType>& InCharacterTypeVector);

	//ĳ���� Ÿ�Ժ� ����Ʈ ��ȯ
	list<shared_ptr<ICharacter>>& GetCharacterList(const ECharacterType& InType);

	//ĳ���� ���� ��ȯ
	shared_ptr<ICharacter> GetCharacter(const ECharacterType& InType, const int InUID);

	//ĳ���� State ����
	void SetRemoveCharacter(shared_ptr<ICharacter>& InDeathCharacter);

	string EnumToString(const ECharacterType& InType);

private:
	//�̱��� Factory ��ü
	static FactoryCharacter* instance_;
	
	//ĳ���� ��ü ����Ʈ������ ����
	list<shared_ptr<ICharacter>> LocalPlayerList;
	list<shared_ptr<ICharacter>> LocalNpcList;
	list<shared_ptr<ICharacter>> LocalMonsterList;
};

