#pragma once
class CInputManager
{
private:
	static bool lkey[256];
	static bool rkey[256];
	static CInputManager *instance;
	// ΩÃ±€≈Ê ∞¥√º¿« ¿ŒΩ∫≈œΩ∫
public:
	CInputManager();
	~CInputManager();

	static void getKey();
	static int keyState(int key);
	static CInputManager* GetInstance()
	{
		if (instance == nullptr)
		{
			instance = new CInputManager();
		}
		return instance;
	}
};