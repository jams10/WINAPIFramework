#include "Object.h"
#include "../Scene/Layer.h"
#include "../Scene/SceneManager.h"
#include "../Scene/Scene.h"
#include "../Resources//ResourcesManager.h"
#include "../Resources/Texture.h"
#include "../Core/Camera.h"
#include "../Collider/Collider.h"

list<CObject*> CObject::m_ObjList;

CObject::CObject()
	:
	m_pTexture( nullptr )
{
}

CObject::CObject( const CObject& obj )
{
	*this = obj;

	if( m_pTexture )
	{
		m_pTexture->AddRef();
	}

	m_ColliderList.clear();

	list<CCollider*>::const_iterator iter;
	list<CCollider*>::const_iterator iterEnd = obj.m_ColliderList.end();

	for( iter = obj.m_ColliderList.begin(); iter != iterEnd; ++iter )
	{
		CCollider* pColl = (*iter)->Clone();

		m_ColliderList.push_back( pColl );
	}
}

CObject::~CObject()
{
	Safe_Release_VecList( m_ColliderList );
	SAFE_RELEASE( m_pTexture );
}

void CObject::AddObj( CObject* pObj )
{
	pObj->AddRef();
	m_ObjList.push_back( pObj );
}

CObject* CObject::FindObject( const string& strTag )
{
	list<CObject*>::iterator iter;
	list<CObject*>::iterator iterEnd = m_ObjList.end();

	for( iter = m_ObjList.begin(); iter != iterEnd; ++iter )
	{
		if( (*iter)->GetTag() == strTag )
		{
			(*iter)->AddRef();
			return *iter;
		}
	}

	return nullptr;
}

void CObject::EraseObj( CObject* pObj )
{
	list<CObject*>::iterator iter;
	list<CObject*>::iterator iterEnd = m_ObjList.end();

	for( iter = m_ObjList.begin(); iter != iterEnd; ++iter )
	{
		if( *iter == pObj )
		{
			SAFE_RELEASE( (*iter) );
			iter = m_ObjList.erase( iter );
			return;
		}
	}
}

void CObject::EraseObj( const string& strTag )
{
	list<CObject*>::iterator iter;
	list<CObject*>::iterator iterEnd = m_ObjList.end();

	for( iter = m_ObjList.begin(); iter != iterEnd; ++iter )
	{
		if( (*iter )->GetTag() == strTag )
		{
			SAFE_RELEASE( (*iter) );
			iter = m_ObjList.erase( iter );
			return;
		}
	}
}

void CObject::EraseObj()
{
	Safe_Release_VecList( m_ObjList );
}

void CObject::SetTexture( CTexture* pTexture )
{
	SAFE_RELEASE( m_pTexture );
	m_pTexture = pTexture;

	if( pTexture )
		pTexture->AddRef();
}

void CObject::SetTexture( const string& strKey, const wchar_t* pFileName, const string& strPathKey )
{
	SAFE_RELEASE( m_pTexture );
	m_pTexture = GET_SINGLE( CResourcesManager )->LoadTexture( strKey, pFileName, strPathKey );
}

void CObject::Input( float fDeltaTime )
{
}

int CObject::Update( float fDeltaTime )
{
	list<CCollider*>::iterator iter;
	list<CCollider*>::iterator iterEnd = m_ColliderList.end();

	for( iter = m_ColliderList.begin(); iter != iterEnd; ++iter )
	{
		if( !(*iter)->GetEnable() )
		{
			++iter;
			continue;
		}

		(*iter)->Update( fDeltaTime );

		if( !(*iter)->GetLife() )
		{
			SAFE_RELEASE( (*iter) );
			iter = m_ColliderList.erase( iter );
			iterEnd = m_ColliderList.end();
		}
		else
			++iter;
	}

	return 0;
}

int CObject::LateUpdate( float fDeltaTime )
{
	list<CCollider*>::iterator iter;
	list<CCollider*>::iterator iterEnd = m_ColliderList.end();

	for( iter = m_ColliderList.begin(); iter != iterEnd; ++iter )
	{
		if( !(*iter)->GetEnable() )
		{
			++iter;
			continue;
		}

		(*iter)->LateUpdate( fDeltaTime );

		if( !(*iter)->GetLife() )
		{
			SAFE_RELEASE( (*iter) );
			iter = m_ColliderList.erase( iter );
			iterEnd = m_ColliderList.end();
		}
		else
			++iter;
	}

	return 0;
}

void CObject::Collision( float fDeltaTime )
{
}

void CObject::Render( HDC hDC, float fDeltaTime )
{
	if( m_pTexture )
	{
		POSITION tPos = m_tPos - m_tSize * m_tPivot;
		POSITION camPos = GET_SINGLE( CCamera )->GetPos();

		tPos = tPos - camPos;

		if( m_pTexture->GetColorKeyEnable() )
		{
			TransparentBlt( hDC, tPos.x, tPos.y, m_tSize.x, m_tSize.y, 
				m_pTexture->GetDC(), 0, 0, m_tSize.x, m_tSize.y, m_pTexture->GetColorKey() );
		}
		else
		{
			BitBlt( hDC, tPos.x, tPos.y, m_tSize.x, m_tSize.y, m_pTexture->GetDC(), 0, 0, SRCCOPY );
		}
	}

	list<CCollider*>::iterator iter;
	list<CCollider*>::iterator iterEnd = m_ColliderList.end();

	for( iter = m_ColliderList.begin(); iter != iterEnd; ++iter )
	{
		if( !(*iter)->GetEnable() )
		{
			++iter;
			continue;
		}

		(*iter)->Render( hDC, fDeltaTime );

		if( !(*iter)->GetLife() )
		{
			SAFE_RELEASE( (*iter) );
			iter = m_ColliderList.erase( iter );
			iterEnd = m_ColliderList.end();
		}
		else
			++iter;
	}
}

CObject* CObject::CreateCloneObj( const string& strPrototypeKey, const string& strTag, CLayer* pLayer )
{
	CObject* pProto = CScene::FindPrototype( strPrototypeKey );

	if( !pProto ) return nullptr;

	CObject* pObj = pProto->Clone();

	pObj->SetTag( strTag );

	if( pLayer )
	{
		pLayer->AddObject( pObj );
	}

	AddObj( pObj );

	return pObj;
}
