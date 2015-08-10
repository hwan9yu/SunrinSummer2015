#include "GameScene.h"
#include "App.h"
#include "Arrow.h"
#include "Enemy.h"
#include "Bullet.h"

CGameScene::CGameScene() : time(0.0f), delay(1.5f)
{
	m_pBackground = new CBackground();
	PushScene(m_pBackground);

	m_pPlayer = new CPlayer();
	PushScene(m_pPlayer);
	m_pPlayer->SetPosition( App::WIDTH/2 - m_pPlayer->normalAni->width/2,
		App::HEIGHT - m_pPlayer->normalAni->height );

	m_pArrowScene = new IScene();
	PushScene(m_pArrowScene);
	m_pEffectScene = new IScene();
	PushScene(m_pEffectScene);
	m_pEnemyScene = new IScene();
	PushScene(m_pEnemyScene);
	m_pBulletScene = new IScene();
	PushScene(m_pBulletScene);

	bulletTime = 0.f;
	
	CGSoundManager * sm = App::GetInstance()->g_pSoundManager;			//사운드매니저를 가져와서
	sm->AddSoundBuffer(sm->LoadWav(_T("resource/sound/play.wav")));		//원하는
	sm->AddSoundBuffer(sm->LoadWav(_T("resource/sound/fire.wav")));		//사운드를
	sm->AddSoundBuffer(sm->LoadWav(_T("resource/sound/destroy.wav")));	//추가해
	sm->Play(0, TRUE);

}

CGameScene::~CGameScene()
{
	CGSoundManager * sm = App::GetInstance()->g_pSoundManager;
	sm->Stop(0);
}

void CGameScene::Input(float eTime)
{
	IScene::Input(eTime);
	if (App::GetInstance()->g_pInputManager->keyState('A') > 0)
	{
		m_pPlayer->Move(-300 * eTime);
	}
	if (App::GetInstance()->g_pInputManager->keyState('D') > 0)
	{
		m_pPlayer->Move(300 * eTime);
	}
	if (App::GetInstance()->g_pInputManager->keyState(VK_SPACE) > 0)
	{
		if (bulletTime > 0.3f)
		{
			this->PushBullet(m_pPlayer->pos.x, m_pPlayer->pos.y);
			CGSoundManager * sm = App::GetInstance()->g_pSoundManager;
			sm->Play(1);

			bulletTime = 0.0f;
		}
	}
}

void CGameScene::Update(float eTime)
{
	IScene::Update(eTime);
	time += eTime;
	bulletTime += eTime;

	if (time >= delay)
	{
		delay = (float)(rand() % 1000) / 300.f;
		time = 0.f;
		//this->PushArrow(rand() % App::WIDTH, -200.0f);
		this->PushEnemy1(rand() % App::WIDTH, -200.0f);
	}

	//this->PushEffect(rand() % App::WIDTH, rand() % App::HEIGHT);

	for (auto iter = m_pBulletScene->children.begin(); iter != m_pBulletScene->children.end();iter++)
	{
		CBullet *bullet = (CBullet*)(*iter);
		
		RECT bulletRect;
		bulletRect.left = bullet->pos.x;
		bulletRect.top = bullet->pos.y;
		bulletRect.right = bullet->pos.x + bullet->sprite->width;
		bulletRect.bottom = bullet->pos.y + bullet->sprite->height;

		for (auto iter2 = m_pEnemyScene->children.begin(); iter2 != m_pEnemyScene->children.end();iter2++)
		{
			IEnemy *enemy = (IEnemy*)(*iter2);
			
			RECT enemyRect;
			enemyRect.left = enemy->pos.x;
			enemyRect.top = enemy->pos.y;
			enemyRect.right = enemy->pos.x + enemy->width;
			enemyRect.bottom = enemy->pos.y + enemy->height;

			RECT t;
			if (IntersectRect(&t, &bulletRect, &enemyRect) == true)
			{
				CParticleSystem *p = PushEffect(bullet->pos.x, bullet->pos.y);
				p->start();
				bullet->available = false;
				enemy->hit();
				break;
			}
		}
	}

}

void CGameScene::Render()
{
	IScene::Render();
	m_pBackground->Render();
	m_pPlayer->Render();
	m_pBulletScene->RenderAll();
	m_pArrowScene->RenderAll();
	m_pEnemyScene->RenderAll();
	m_pEffectScene->RenderAll();
}

void CGameScene::PushArrow(float x, float y, float rot)
{
	CArrow *p = new CArrow();
	p->SetPosition(x, y);
	m_pArrowScene->PushScene(p);
	p->rot = rot;
}

CParticleSystem* CGameScene::PushEffect(float x, float y)
{
	CParticleSystem *p = new CParticleSystem("resource/particle/particle.png",50);
	p->SetPosition(x, y);
	m_pEffectScene->PushScene(p);
	return p;
}

void CGameScene::PushEnemy1(float x, float y)
{
	CEnemy1 *p = new CEnemy1();
	p->SetPosition(x, y);
	m_pEnemyScene->PushScene(p);
}

void CGameScene::PushBullet(float x, float y)
{
	CBullet *p = new CBullet();
	p->SetPosition(x, y);
	m_pBulletScene->PushScene(p);
}