#include "ParticleSystem.h"

CParticleSystem::CParticleSystem( char* path, int number )
{
	count = 0;
	time = 0.f;
	RenderState = 1;
	direction=0;

	this->path = path;
	this->number = number;

	spread = 360.f;
	rotSpeed = 60.f;

	setColor1(255,255,80,30);
	setColor2(0,0,0,0);

	setLife(0.5,0.5);
	setSpeed(0,150);
	setScalep(1.2,2.0);
	
	bEnd=false;

}
CParticleSystem::~CParticleSystem()
{
	for( PARTICLE::iterator iter=particle.begin() ; iter!=particle.end() ; iter++ )
		delete( *iter );
	particle.clear();
}

void CParticleSystem::start()
{
	for( int i=0 ; i<number ; i++ )
	{
		createParticle();
	}
}

void CParticleSystem::setColor1(int a, int r, int g, int b)
{
	sa=a; sr=r; sg=g; sb=b;
}

void CParticleSystem::setColor2(int a, int r, int g, int b)
{
	ea=a; er=r; eg=g; eb=b;
}

void CParticleSystem::pushParticle( CParticle* p )
{
	particle.push_back( p );
	p->parent=this;
}
void CParticleSystem::createParticle()
{
	CRandom Random;
	float s = minSpeed+Random.nextInt(int(maxSpeed-minSpeed));
	float a = direction+Random.nextInt((int)spread)-(int)spread/2;

	D3DXVECTOR2 speed = D3DXVECTOR2( (s)*cos(a/180 * D3DX_PI),
									 (s)*sin(a / 180 * D3DX_PI));
	float lifetime = minLifeTime+Random.nextInt(int(maxLifeTime-minLifeTime));
	float size = minScale + Random.nextInt(int(maxScale-minScale));
	count++;

	CParticle *par=new CParticle( path, speed, lifetime, size, rotSpeed, sa, sr, sg, sb, RenderState ) ;
	pushParticle( par );
}

void CParticleSystem::Render()
{
	IScene::Render();

	for( PARTICLE::iterator iter=particle.begin() ; iter!=particle.end() ; iter++ )
	{
		(*iter)->Render();
	}
}
void CParticleSystem::Update( float eTime )
{
	IScene::Update( eTime );
	time += eTime;
	
	for( PARTICLE::iterator iter=particle.begin() ; iter!=particle.end() ; iter++ )
	{
		(*iter)->Update( eTime );
		
		if( int(sa + (*iter)->nowLifeTime/(*iter)->lifeTime*(ea-sa)) > 0 )
			(*iter)->a = int(sa + (*iter)->nowLifeTime/(*iter)->lifeTime*(ea-sa));
		else if( 255-ea != 0 )
			(*iter)->a = 0;

		(*iter)->r = int(sr + ((*iter)->nowLifeTime/(*iter)->lifeTime*(er-sr)));
		(*iter)->g = int(sg + ((*iter)->nowLifeTime/(*iter)->lifeTime*(eg-sg)));
		(*iter)->b = int(sb + ((*iter)->nowLifeTime/(*iter)->lifeTime*(eb-sb)));

		if( (*iter)->nowLifeTime >= (*iter)->lifeTime )
		{
			delete( *iter );
			iter = particle.erase( iter );
			count--;

			if( iter == particle.end() )
				break;
		}
	}
	if(count<=0)
	{
		bEnd=true;
		this->parent->PopScene(this);
	}
}