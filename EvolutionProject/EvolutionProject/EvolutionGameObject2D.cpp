#include "EvolutionGameObject2D.h"

EVGameObject2D::EVGameObject2D()
{
	_parent = NULL;

	_update = true;

	D3DXMatrixIdentity(&_transformMatrix);

	_scale				= D3DXVECTOR2(1.0f, 1.0f);
	_scalingCenter		= D3DXVECTOR2(0.0f, 0.0f);
	_rotationCenter		= D3DXVECTOR2(0.0f, 0.0f);
	_position			= D3DXVECTOR2(0.0f, 0.0f);
	_rotation			= 0.0f;
}

EVGameObject2D::~EVGameObject2D()
{
	for (list<EVGameObject2D*>::iterator it = _child.begin(); it != _child.end(); ++it)
	{
		delete (*it);
		(*it) = NULL;
	}

	_child.clear();
}

void EVGameObject2D::Update()
{
	for (list<EVGameObject2D*>::iterator it = _child.begin(); it != _child.end(); ++it)
	{
		if ((*it)->_update)
		{
			(*it)->Update();
		}
	}
}

void EVGameObject2D::Render()
{
	D3DXMatrixTransformation2D(
		&_transformMatrix,
		&_scalingCenter,
		NULL,
		&_scale,
		&_rotationCenter,
		_rotation,
		&_position);

	if (_parent != NULL)
	{
		_transformMatrix = _transformMatrix * _parent->_transformMatrix;
	}
}

void EVGameObject2D::PushChildObject(EVGameObject2D* gameObject, std::string tag, bool isUpdate)
{
	gameObject->_tag = tag;

	gameObject->_update = isUpdate;
	gameObject->_parent = this;

	_child.push_back(gameObject);
}

void EVGameObject2D::PopChildObject(std::string tag, bool isErase)
{
	for (list<EVGameObject2D*>::iterator it = _child.begin(); it != _child.end(); ++it)
	{
		if ((*it)->_tag == tag)
		{
			(*it)->_parent = NULL;
			it = _child.erase(it);

			if (isErase)
			{
				delete (*it);
				if (it == _child.end())
				{
					break;
				}
			}
		}
	}
}

EVGameObject2D* EVGameObject2D::FindChildObject(std::string tag)
{
	for (list<EVGameObject2D*>::iterator it = _child.begin(); it != _child.end(); ++it)
	{
		if ((*it)->_tag == tag)
		{
			return (*it);
		}
	}

	return NULL;
}