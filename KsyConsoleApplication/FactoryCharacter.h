#pragma once
#include <map>

interface ICharacter;

class FactoryCharacter
{
public:
	FactoryCharacter();
	~FactoryCharacter();

	//싱글턴 인스턴스
	static FactoryCharacter& GetInstance();
	
	//Factory 및 스마트포인터 객체 메모리 초기화
	static void FactoryDestroy();
	
	//캐릭터 생성 함수
	weak_ptr<ICharacter> CreatePlayer(int InTID);
	weak_ptr<ICharacter> CreateNpc(int InTID);
	weak_ptr<ICharacter> CreateMonster(int InTID);

	//전투 가능 캐릭터 타입 반환
	vector<ECharacterType> GetAbleBattleCharacterTypeVector();
	
	//공격자 & 피격자 랜덤 선출
	weak_ptr<ICharacter> GetRandTypeCharacter(vector<ECharacterType>& InCharacterTypeVector);

	//캐릭터 타입별 리스트 반환
	map<int, shared_ptr<ICharacter>>& GetCharacterMap(const ECharacterType& InType);

	//캐릭터 정보 반환
	shared_ptr<ICharacter> GetCharacter(const ECharacterType& InType, const int InUID);

	//캐릭터 State 제거
	void SetRemoveCharacter(shared_ptr<ICharacter>& InDeathCharacter);

	string EnumToString(const ECharacterType& InType);

private:
	//싱글턴 Factory 객체
	static FactoryCharacter* instance_;
	
	//캐릭터 객체 스마트보인터 저장
	map<int, shared_ptr<ICharacter>> LocalPlayerMap;
	map<int, shared_ptr<ICharacter>> LocalNpcMap;
	map<int, shared_ptr<ICharacter>> LocalMonsterMap;
};

