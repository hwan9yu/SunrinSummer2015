#include "IScene.h"

IScene::IScene()
	:parent(NULL), pos(0, 0), scalingCenter(0, 0), rotatingCenter(0, 0), scale(1.f, 1.f), rot(0.f)
{
	D3DXMatrixIdentity(&mat);
}


IScene::~IScene()
{
	for (auto iter = children.begin(); iter != children.end(); iter++){
		delete((*iter));
	}
	children.clear();
}

void IScene::Input(float eTime)
{
	
}

void IScene::Update(float eTime)
{
	for (auto iter = children.begin(); iter != children.end();){
		(*iter)->Update(eTime);

		if ((*iter) == nullptr)
		{
			iter = children.erase(iter);
		}
		else iter++;
	}
}

void IScene::Render()
{
	D3DXMatrixTransformation2D(&mat, &scalingCenter, 0.f, &scale, &rotatingCenter, rot, &pos);
	if (parent != NULL)
		mat *= parent->mat;
}

void IScene::PushScene(IScene* p)
{
	p->parent = this;
	children.push_back(p);
}

void IScene::PopScene(IScene* p, bool isErase)
{
	for (auto iter = children.begin(); iter != children.end(); iter++){
		if ((*iter) == p){
			if (isErase){
				delete((*iter));
				(*iter) = nullptr;
			}
			return;
		}
	}
}