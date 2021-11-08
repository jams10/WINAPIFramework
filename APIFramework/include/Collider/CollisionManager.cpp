#include "CollisionManager.h"
#include "../Object/Object.h"
#include "Collider.h"

DEFINITION_SINGLE( CCollisionManager )

CCollisionManager::CCollisionManager()
{

}

CCollisionManager::~CCollisionManager()
{

}

void CCollisionManager::AddObject( CObject* pObj )
{
	if( pObj->CheckCollider() )
	{
		m_CollisionList.push_back( pObj );
	}
}

void CCollisionManager::Collision( float fDeltaTime )
{
	if( m_CollisionList.size() < 2 )
	{
		m_CollisionList.clear();
		return;
	}

	// process collision between objects
}
