#pragma once

#include <map>
#include <vector> 

#include "cocos2d.h"

template<class T> class Creator
{
protected:
	std::map<int, std::vector<T*>> mMapOfObjects;
	int mFrameCount;
	 
	/**
	 * Get an inactive object
	 * @return T
	 */
	virtual T* GetAnInactiveObject(const int& mapIndex) = 0;

public:
	Creator()
	{
		// Set local data //
		mFrameCount = 0;
	}

	/**
	 * Make the active objects disappear from the scene
	 */
	virtual void DisappearActiveObjects() = 0;
};
