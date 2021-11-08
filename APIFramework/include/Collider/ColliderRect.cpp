#include "ColliderRect.h"
#include "../Object/Object.h"

CColliderRect::CColliderRect()
{
	m_eCollType = COLLIDER_TYPE::CT_RECT;
}

CColliderRect::CColliderRect( const CColliderRect& coll )
	:
	CCollider( coll )
{
	m_tInfo = coll.m_tInfo;
}

CColliderRect::~CColliderRect()
{
}

void CColliderRect::SetRect( float l, float t, float r, float b )
{
	m_tInfo.left = l;
	m_tInfo.top = t;
	m_tInfo.right = r;
	m_tInfo.bottom = b;
}

bool CColliderRect::Init()
{
	return true;
}

void CColliderRect::Input( float fDeltaTime )
{
	CCollider::Input( fDeltaTime );
}

int CColliderRect::Update( float fDeltaTime )
{
	CCollider::Update( fDeltaTime );
	return 0;
}

int CColliderRect::LateUpdate( float fDeltaTime )
{
	CCollider::LateUpdate( fDeltaTime );

	POSITION tPos = m_pObj->GetPos();
	m_tWorldInfo.left = tPos.x + m_tInfo.left;
	m_tWorldInfo.top = tPos.y + m_tInfo.top;
	m_tWorldInfo.right = tPos.x + m_tInfo.right;
	m_tWorldInfo.bottom = tPos.y + m_tInfo.bottom;

	return 0;
}

void CColliderRect::Collision( float fDeltaTime )
{
	CCollider::Collision( fDeltaTime );
}

void CColliderRect::Render( HDC hDC, float fDeltaTime )
{
	CCollider::Render( hDC, fDeltaTime );
}

CColliderRect* CColliderRect::Clone()
{
	return new CColliderRect(*this);
}
