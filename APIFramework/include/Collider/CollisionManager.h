#pragma once

#include "../Game.h"

class CCollisionManager
{
private:
	list<class CObject*> m_CollisionList;

public:
	void AddObject( class CObject* pObj );
	void Collision( float fDeltaTime );

	DECLARE_SINGLE( CCollisionManager )
};

