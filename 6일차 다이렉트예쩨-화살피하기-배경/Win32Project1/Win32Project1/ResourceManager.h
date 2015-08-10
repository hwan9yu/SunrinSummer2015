#pragma once
#include <d3dx9.h>
#include <map>
using namespace std;
class CResourceManager
{
private:
	map<char*, LPDIRECT3DTEXTURE9> textures;
public:
	CResourceManager();
	~CResourceManager();
public:
	LPDIRECT3DTEXTURE9 LoadTexture(char *path);
	void UnloadTexture(char *path);

};