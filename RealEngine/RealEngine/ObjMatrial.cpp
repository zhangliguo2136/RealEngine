#include "ObjMatrial.h"

ObjMatrial::ObjMatrial()
{

}

ObjMatrial::~ObjMatrial()
{
	if (this->diffuseTexture != nullptr)
	{
		//delete diffuseTexture;

		diffuseTexture = nullptr;
	}
}