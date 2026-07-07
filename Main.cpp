#include <iostream>
#include <memory>
#include <conio.h>

///@brief コピー禁止マクロ
#define NONCOPYABLE(className)  \
public: \
    className(const className&) = delete; \
    className& operator=(const className&) = delete;

///@brief シングルトン定義マクロ
#define SINGLETON(className) \
    NONCOPYABLE(className) \
private: \
    className() {} \
public: \
    static className& Instance() \
    { \
        static className instance; \
        return instance; \
    }

///@brief シーンクラス定義
#define DEFINE_SCENE(className) class className : Scene

///@brief シーンクラスのEnter定義
#define SCENE_ENTER() virtual void Enter(GameManager& manager)

///@brief シーンクラスのExec定義
#define SCENE_EXEC() virtual void Execute(GameManager& manager)

///@brief シーンクラスのExit定義
#define SCENE_EXIT() virtual void Exit(GameManager& manager)


class Base
{
protected:
	Base() {}
public:
	Base(const Base&) = delete;
	Base& operator=(const Base&) = delete;

	virtual void Update() = 0;
};

class Title : public Base
{
private:
	Title() {}
public:
	Title(const Title&) = delete;
	Title& operator=(const Title&) = delete;

	static Title& Instance()
	{
		static Title instance;
		return instance;
	}

	void Update()override
	{
		std::cout << "Title" << std::endl;
	}
};

class Play : public Base
{
private:
	Play() {}
public:
	Play(const Play&) = delete;
	Play& operator=(const Play&) = delete;

	static Play& Instance()
	{
		static Play instance;
		return instance;
	}

	void Update()override
	{
		std::cout << "Space to ATTACK!!" << std::endl;
	}
};

class End : public Base
{
private:
	End() {}
public:
	End(const End&) = delete;
	End& operator=(const End&) = delete;

	static End& Instance()
	{
		static End instance;
		return instance;
	}

	void Update()//override
	{
		std::cout << "You Hunt the Monster!" << std::endl;
		std::cout << std::endl;
		std::cout << "Spcae to Back to The Title" << std::endl;
	}
};

class GameManager
{
private:

	enum class Scene
	{
		TITLE,
		PLAY,
		END
	};

	Base* scene = nullptr;
	Scene scene_num = Scene::TITLE;

	/// <summary>
	/// インスタンスを外部から生成するのを防ぐためのprivateコンストラクタ
	/// </summary>
	GameManager() 
	{
		scene = &Title::Instance();	
	}


public:
	
	/// <summary>
	/// 別のインスタンスのコピーを禁止するためのコピーコンストラクタ
	/// </summary>
	GameManager(const GameManager&) = delete;
	/// <summary>
	/// 別のインスタンスのコピーを禁止するためのコピーコンストラクタ
	/// </summary>
	GameManager& operator=(const GameManager&) = delete;

	/// <summary>
	/// スレッドセーフな GameManager の唯一のインスタンスを返すことができる
	/// </summary>
	static GameManager& Instance()
	{
		static GameManager instance; // C++11 以降のスレッドセーフなローカルstatic
		return instance;
	}
	
	void StartGame()
	{
		if (scene == nullptr) return;

		// ゲーム開始処理
		scene->Update();
		while(true)
		{
			if (_kbhit())
			{
				int key = _getch();
				if(key == ' ')
				{
					scene = SceneChange();
					scene->Update();
				}
			}
		}
	}

	Base* SceneChange()
	{
		switch (scene_num)
		{
		case Scene::TITLE:
			scene_num = Scene::PLAY;
			return &Play::Instance();
		case Scene::PLAY:
			scene_num = Scene::END;
			return &End::Instance();
		case Scene::END:
			scene_num = Scene::TITLE;
			return &Title::Instance();
		}
	}
};


int main()
{
	GameManager::Instance().StartGame();

//	GameManager* instance = new GameManager();	 // エラー: privateコンストラクタにアクセスできない
//	GameManager instance;						 // エラー: privateコンストラクタにアクセスできない

//	GameManager::Instance() = GameManager::Instance(); // 代入禁止のためエラー

} 