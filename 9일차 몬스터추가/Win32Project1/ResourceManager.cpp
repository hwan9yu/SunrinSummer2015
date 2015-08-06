#include "ResourceManager.h"
#include "App.h"

CResourceManager::CResourceManager()
{
}

CResourceManager::~CResourceManager()
{
	for (auto iter = textures.begin(); iter != textures.end(); iter++)
	{
		(iter->second->Release());
	}
	textures.clear();
}

LPDIRECT3DTEXTURE9 CResourceManager::LoadTexture(char *path)
{
	if (textures[path] != NULL) return textures[path];

	D3DXCreateTextureFromFileExA(
		App::g_pd3dDevice,
		path,
		D3DX_DEFAULT_NONPOW2,
		D3DX_DEFAULT_NONPOW2,
		1,
		0,
		D3DFMT_UNKNOWN,
		D3DPOOL_MANAGED,
		D3DX_DEFAULT,
		D3DX_DEFAULT,
		NULL,
		NULL,
		NULL,
		&textures[path]
		);

	return textures[path];
}

void CResourceManager::UnloadTexture(char *path)
{
	if (textures[path] != NULL)
	{
		textures[path]->Release();
		auto iter = textures.find(path);
		textures.erase(iter);
	}
}
