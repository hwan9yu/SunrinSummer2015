#pragma once
#include "IScene.h"

class CFontSceneNode : virtual public IScene
{
private:
	LPD3DXFONT font;
public:
	char *string;
	char *fontname;
	DWORD color;
	int len;

	CFontSceneNode( int bufferSize, UINT size, char* fontname="¸¼Àº °íµñ" );
	~CFontSceneNode();

	void Render();
	void Update( float eTime );

	void setString( char string[], bool autosize=true);
};