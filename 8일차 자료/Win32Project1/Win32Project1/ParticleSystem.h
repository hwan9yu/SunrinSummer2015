#pragma once
#include "Particle.h"
#include <list>

using namespace std;
class CRandom
{
public:
	CRandom(){}
	~CRandom(){}

	int nextInt( int n )
	{
		if( n == 0 ) return 0;
		return rand()%n;
	}
};

class CParticleSystem : virtual public IScene
{
private:
	int sa, sr, sg, sb;
	int ea, er, eg, eb;
public:
	CParticleSystem( char* path, int number = 20 );
	~CParticleSystem();
	
	typedef list< CParticle* > PARTICLE;
	PARTICLE particle;

	char *path;
	int count;
	int number;
	int RenderState;
	float time;
	bool bEnd;

	float minSpeed, maxSpeed;
	float minScale, maxScale;
	float minLifeTime, maxLifeTime;
	float rotSpeed;
	float direction;
	float spread;

	bool bCreate;

	void setColor1(int a, int r, int g, int b);
	void setColor2(int a, int r, int g, int b);
	void setSpeed(float ss, float es){minSpeed=ss; maxSpeed=es;}
	void setScalep(float ss, float es){minScale=ss; maxScale=es;}
	void setLife(float sl, float el){minLifeTime=sl; maxLifeTime=el;}

	void pushParticle( CParticle* p );
	void createParticle();

	void start();

	void Render();
	void Update( float eTime );
};