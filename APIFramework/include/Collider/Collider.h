#pragma once

#include "../Ref.h"
class CCollider : public CRef
{
protected:
	friend class CObject;

protected:
	CCollider();
	CCollider( const CCollider& coll );
	virtual ~CCollider() = 0;

protected:
	COLLIDER_TYPE	m_eCollType;
	class CObject*	m_pObj;

public:
	COLLIDER_TYPE GetColliderType()const
	{
		return m_eCollType;
	}

	class CObject* GetObj() const
	{
		return m_pObj;
	}

public:
	void SetObj( class CObject* pObj )
	{
		m_pObj = pObj;
	}

public:
	virtual bool Init() = 0;
	virtual void Input( float fDeltaTime );
	virtual int Update( float fDeltaTime );
	virtual int LateUpdate( float fDeltaTime );
	virtual void Collision( float fDeltaTime );
	virtual void Render( HDC hDC, float fDeltaTime );
	virtual CCollider* Clone() = 0;
};

