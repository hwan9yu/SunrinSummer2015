#pragma once
class IObject
{
protected:
	IObject *parent;
public:
	IObject(){}
	virtual ~IObject(){}

	void SetParent(IObject *p){ parent = p; }
	IObject* GetParent(){ return parent; }

	virtual void Input(){}
	virtual void Update(){}
	virtual void Render(){}
	virtual void Clear(){}
};