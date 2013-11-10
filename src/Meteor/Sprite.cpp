#include "stdafx.h"
#include "Sprite.h"
#include "MainWindow.h"
#include "D2DBitmap.h"
#include "ResourceManager.h"

CD2DSprite::CD2DSprite()
	: m_pD2DBitmap(nullptr)
{
}


CD2DSprite::CD2DSprite( std::wstring path )
{
	m_Matrix = D2D1::Matrix3x2F::Translation( 200, 200 );

	CD2DBitmap * bitmap = new CD2DBitmap();
	bitmap->LoadResource( path );
	m_pD2DBitmap = bitmap;

	// TODO: test code
	m_ImageWidth = 80;
 	m_ImageHeight = 100;

// Real Code
//	m_ImageWidth = m_pD2DBitmap->GetD2DBitmap()->GetSize().width;
//	m_ImageHeight = m_pD2DBitmap->GetD2DBitmap()->GetSize().width;
}


CSprite * CSprite::Create( std::wstring path )
{
	// TODO : Use Resource Manager
	return new CD2DSprite( path );
}


void CD2DSprite::Render()
{
	CD2DRenderer::GetInstance().GetHwndRenderTarget()->SetTransform( m_Matrix );
	CD2DRenderer::GetInstance().GetHwndRenderTarget()->DrawBitmap(m_pD2DBitmap->GetD2DBitmap(), D2D1::RectF(0.f, 0.f, m_ImageWidth, m_ImageHeight), m_Opacity );
}


void CD2DSprite::Release()
{
	SafeRelease( m_pD2DBitmap );
	CResourceManager::GetInstance().ReleaseResource( this );
}


CD2DSprite::~CD2DSprite()
{
	Release();
}