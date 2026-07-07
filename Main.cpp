#include <iostream>

class GameManager
{
private:

	GameManager() {};

public:
	// コピー・代入の禁止
	GameManager(const GameManager&) = delete;
	GameManager& operator=(const GameManager&) = delete;

	static GameManager& Instance()
	{
		static GameManager instance; // C++11 以降のスレッドセーフなローカルstatic
		return instance;
	}

	void StartGame()
	{
		// ゲーム開始処理
		std::cout << "Game Started!" << std::endl;
	}
};

int main()
{
	GameManager::Instance().StartGame();
} 