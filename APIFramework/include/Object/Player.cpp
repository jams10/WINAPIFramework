#include "Player.h"
#include "../Resources/Texture.h"
#include "../Core/Input.h"

CPlayer::CPlayer()
{
}

CPlayer::CPlayer( const CPlayer& player )
    :
    CMoveObject( player )
{
}

CPlayer::~CPlayer()
{
}

bool CPlayer::Init()
{
    SetPos( 50.f, 50.f );
    SetSize( 100.f, 100.f );
    SetSpeed( 400.f );
    SetPivot( 0.5f, 0.5f );

    SetTexture( "Player", L"Kirby.bmp" );

    m_pTexture->SetColorKey( RGB( 255, 0, 255 ) );

    return true;
}

void CPlayer::Input( float fDeltaTime )
{
    CMoveObject::Input( fDeltaTime );

    if( KEYPRESS( "MoveUp" ) )
    {
        MoveYAsSpeed( fDeltaTime, MD_BACK );
    }
    if( KEYPRESS( "MoveDown" ) )
    {
        MoveYAsSpeed( fDeltaTime, MD_FRONT );
    }
    if( KEYPRESS("MoveLeft") )
    {
        MoveXBySpeed( fDeltaTime, MD_BACK );
    }
    if( KEYPRESS( "MoveRight" ) )
    {
        MoveXBySpeed( fDeltaTime, MD_FRONT );
    }
    if( KEYDOWN( "Fire" ) )
    {
        Fire();
    }
    if( KEYDOWN( "Skill1" ) )
    {
        MessageBox( NULL, L"Skill1", L"Skill1", MB_OK );
    }
}

int CPlayer::Update( float fDeltaTime )
{
    CMoveObject::Update( fDeltaTime );

    return 0;
}

int CPlayer::LateUpdate( float fDeltaTime )
{
    CMoveObject::LateUpdate( fDeltaTime );

    return 0;
}

void CPlayer::Collision( float fDeltaTime )
{
    CMoveObject::Collision( fDeltaTime );
}

void CPlayer::Render( HDC hDC, float fDeltaTime )
{
    CMoveObject::Render( hDC, fDeltaTime );
}

CPlayer* CPlayer::Clone()
{
    return new CPlayer(*this);
}

void CPlayer::Fire()
{
    CObject* pBullet = CMoveObject::CreateCloneObj( "Bullet", "PlayerBullet", m_pLayer );

    // Get middle point of right
    POSITION tPos;
    tPos.x = GetRight() + pBullet->GetSize().x * pBullet->GetPivot().x;
    tPos.y = GetCenter().y;

    pBullet->SetPos( tPos );
}
