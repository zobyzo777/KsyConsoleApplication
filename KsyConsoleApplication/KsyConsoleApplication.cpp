// KsyConsoleApplication.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.

#include "pch.h"
#include <list>
#include <time.h>
#include "FactoryCharacter.h"

int main()
{
	std::cout << "전투를 시작합니다.\n";
	int iInput = 0;

	printf("- %s 캐릭터 갯수를 [1~10] :", FactoryCharacter::GetInstance().EnumToString(ECharacterType::Player).c_str());
	std::cin >> iInput;

	//Player 캐릭터 생성
	for (int i = 1; i <= iInput; i++)
	{
		FactoryCharacter::GetInstance().CreatePlayer(i);
	}

	printf("- %s 캐릭터 갯수를 [1~10] :", FactoryCharacter::GetInstance().EnumToString(ECharacterType::Npc).c_str());
	std::cin >> iInput;

	//Npc 캐릭터 생성
	for (int i = 1; i <= iInput; i++)
	{
		FactoryCharacter::GetInstance().CreateNpc(i);
	}

	printf("- %s 캐릭터 갯수를 [1~10] :", FactoryCharacter::GetInstance().EnumToString(ECharacterType::Monster).c_str());
	std::cin >> iInput;

	//Monster 캐릭터 생성
	for (int i = 1; i <= iInput; i++)
	{
		FactoryCharacter::GetInstance().CreateMonster(i);
	}
	
	//전투Process
	while (true)
	{
		vector<ECharacterType> AbleBattleTypeVector = FactoryCharacter::GetInstance().GetAbleBattleCharacterTypeVector();
		
		//둘이상의 대전상대가 없을 경우 전투 종료
		if (AbleBattleTypeVector.size() < 2)
			break;

		weak_ptr<ICharacter> attacker = FactoryCharacter::GetInstance().GetRandTypeCharacter(AbleBattleTypeVector);
		weak_ptr<ICharacter> defender = FactoryCharacter::GetInstance().GetRandTypeCharacter(AbleBattleTypeVector);

		shared_ptr<ICharacter> lockAttacker = attacker.lock();
		shared_ptr<ICharacter> lockDefender = defender.lock();

		if (lockAttacker && lockDefender)
			lockAttacker->SetAttack(lockDefender);
		else
			break;
	}

	//전투 종료
	vector<ECharacterType> AbleBattleTypeVector = FactoryCharacter::GetInstance().GetAbleBattleCharacterTypeVector();
	if (AbleBattleTypeVector.size() == 1)
	{
		const ECharacterType eWinType = *AbleBattleTypeVector.begin();
		const int iReviveCount = FactoryCharacter::GetInstance().GetCharacterMap(eWinType).size();
		std::cout << "========================================================================================\n";
		printf("- 최후의 생존자는 = %s, 생존수 = %d\n", FactoryCharacter::GetInstance().EnumToString(eWinType).c_str(), iReviveCount);
		std::cout << "========================================================================================\n";
	}
	
	//인스턴스 초기화
	FactoryCharacter::FactoryDestroy();

	return 0;
}