/**
 * \file Angler.cpp
 *
 * \author Elizabeth Lipin
 */

#include "pch.h"
#include "Angler.h"
#include "Item.h"
#include "Aquarium.h"
#include <string>
using namespace Gdiplus;
using namespace std;

/// Fish filename 
const wstring AnglerImageName = L"images/angler.png";

/** Constructor
 * \param aquarium The aquarium this is a member of
*/
CAngler::CAngler(CAquarium* aquarium) : CItem(aquarium, AnglerImageName)
{
}

/**
* This function checks if fish can catch other fish
* \return true
*/
bool CAngler::CanCatch()
{
    return true;
}

/**
* This function lets the angler catch another fish if close enough
* \param item a fish to check
*/
bool CAngler::CatchFish(weak_ptr<CItem> item)
{
    // Distance in the X and Y directions
    double dx = GetX() - item.lock() ->GetX();
    double dy = GetY() - item.lock() ->GetY();

    double distance = sqrt(dx * dx + dy * dy);
    if (distance < 150 && mCaughtFish.lock() != item.lock())
    {
        mCaughtFish = item;
        return true;
    }
    return false;
}

/**
* This function sends movement details to caught fish
* \param changeX The change in the x direction
* \param changeY The change in the y direction
*/
//void CAngler::PreMoved(double changeX, double changeY)
//{
  //  CItem::PreMoved(changeX, changeY);
    //auto caught = mCaughtFish.lock();
    //if (caught != nullptr)
    //{
      //  caught->Follow(changeX, changeY);
  //  }
//}
