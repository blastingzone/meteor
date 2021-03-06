#include "stdafx.h"
#include "Scene.h"
#include "InputManager.h"
#include "ResourceManager.h"

CScene::CScene(void)
	: m_Zone( nullptr )
{
	m_CameraPosition.x = 0.0f;
	m_CameraPosition.y = 0.0f;

	m_PlayerCharacter.LoadAnimation();

	CZoneInfo * zoneInfo = CResourceManager::GetInstance().GetZoneInfo( L"zone_village" );
	m_Zone = zoneInfo->CreateZone();
	m_Zone->Enter( &m_PlayerCharacter, nullptr );
	SafeRelease( zoneInfo );
}


CScene::~CScene(void)
{
	SafeDelete( m_Zone );
}


bool CScene::Update( float deltaTime )
{
	switch ( CInputManager::GetInstance().GetKeyState( VK_LEFT ) )
	{
	case INPUT_DOWN:
		m_PlayerCharacter.SetDirection( LEFT );
		m_PlayerCharacter.SetStatus( WALK );
		break;

	case INPUT_UP:
		m_PlayerCharacter.SetStatus( STAND );
		break;

	default:
		break;
	}

	switch ( CInputManager::GetInstance().GetKeyState( VK_RIGHT ) )
	{
	case INPUT_DOWN:
		m_PlayerCharacter.SetDirection( RIGHT );
		m_PlayerCharacter.SetStatus( WALK );
		break;

	case INPUT_UP:
		m_PlayerCharacter.SetStatus( STAND );
		break;

	default:
		break;
	}

	switch ( CInputManager::GetInstance().GetKeyState( VK_UP ) )
	{
	case INPUT_DOWN:
		m_PlayerCharacter.SetDirection( UP );
		m_PlayerCharacter.SetStatus( WALK );
		break;

	case INPUT_UP:
		m_PlayerCharacter.SetStatus( STAND );
		break;

	default:
		break;
	}

	switch( CInputManager::GetInstance().GetKeyState( VK_DOWN ) )
	{
	case INPUT_DOWN:
		m_PlayerCharacter.SetDirection( DOWN );
		m_PlayerCharacter.SetStatus( WALK );
		break;

	case INPUT_UP:
		m_PlayerCharacter.SetStatus( STAND );
		break;

	default:
		break;
	}

	m_PlayerCharacter.Update( deltaTime );
	m_CameraPosition = m_PlayerCharacter.GetPosition();
	m_Zone->Update( deltaTime, m_CameraPosition );

	return true;
}

void CScene::Render()
{
	m_Zone->Render( m_CameraPosition );
	m_PlayerCharacter.Render( m_CameraPosition );
}
