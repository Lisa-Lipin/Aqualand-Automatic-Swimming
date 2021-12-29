/**
 * \file Fish.cpp
 *
 * \author Elizabeth Lipin
 */

#include "pch.h"
#include "Item.h"
#include "Dory.h"
#include "Fish.h"
#include "math.h"
#include "Aquarium.h"

using namespace std;

/**
 * Constructor
 * \param aquarium The aquarium we are in
 * \param filename Filename for the image we use
 */
CFish::CFish(CAquarium* aquarium, const std::wstring& filename) :
    CItem(aquarium, filename)
{
    
}

/**
* initializes fish speeds
*/
void CFish::Initialize()
{
    std::pair<double, double> xRange;
    std::pair<double, double> yRange;
    GetSpeedXRange(xRange);
    GetSpeedYRange(yRange);
    mSpeedX = xRange.first + ((double)rand() / RAND_MAX) * (xRange.second - xRange.first);
    mSpeedY = yRange.first + ((double)rand() / RAND_MAX) * (yRange.second - yRange.first);
}
/**
 * Handle updates in time of our fish
 *
 * This is called before we draw and allows us to
 * move our fish. We add our speed times the amount
 * of time that has elapsed.
 * \param elapsed Time elapsed since the class call
 */
void CFish::Update(double elapsed)
{
    SetMirror(mSpeedX < 0);
    SetLocation(GetX() + mSpeedX * elapsed,
        GetY() + mSpeedY * elapsed);
    wchar_t buffer[256] = {0};
    wsprintf(buffer, L"Fish position %d,%d , hts: %d, speedY: %d \n", (int)GetX(), (int)GetY(), (int)(GetAquarium()->GetHeight()), (int)mSpeedY);
    OutputDebugString(buffer);
    //turn fish around if it gets too close to an edge
    if (mSpeedX > 0 && (GetX() >= (double)(GetAquarium()->GetWidth())-(GetWidthItem()/2)-10))
    {
        mSpeedX = -mSpeedX;
        SetMirror(mSpeedX < 0);
    }
    else if (mSpeedX < 0 && (GetX() <= ((double)((GetWidthItem()) / 2) + 10)))
    {
        mSpeedX = -mSpeedX;
        SetMirror(mSpeedX < 0);
    }
    if (mSpeedY > 0 && (GetY() >= (double)(GetAquarium()->GetHeight()) - (GetHeightItem() / 2) - 10))
    {
        mSpeedY = -mSpeedY;
    }
    else if (mSpeedY < 0 && (GetY() <= ((double)((GetHeightItem()) / 2) + 10)))
    {
        mSpeedY = -mSpeedY;
    }
    //if fish is too close to another, turn around
    if (GetAquarium()->TooClose(this))
    {
        mSpeedX = -mSpeedX;
        SetMirror(mSpeedX < 0);
        mSpeedY = -mSpeedY;
        SetLocation(GetX() + mSpeedX * elapsed,
            GetY() + mSpeedY * elapsed);
    }
     //produce a random number
    int randomize = rand() % 100000000;
    //int to accellerate x and decellerate y
    int accelX = 5;
    //int to accellerate y and decellerate x
    int accelY = 3;
    //int to accellerate x and decellerate y by greater extent
    int quickChange = 53;
    //if that numbers is evenly divisible by another random number, change speeds
    //if x changes mirror if needed
    //used c++ reference for info on how rand function works
    if (randomize % accelX == 0)
    {
        mSpeedX = mSpeedX - 2;
        SetMirror(mSpeedX < 0);
        mSpeedY = mSpeedY + 2;
    }
    else if (randomize % accelY == 0)
    {
        mSpeedX = mSpeedX + 2;
        SetMirror(mSpeedX < 0);
        mSpeedY = mSpeedY - 2;
    }
    else if (randomize % quickChange == 0)
    {
        mSpeedX = mSpeedX * 1.02;
        mSpeedY = mSpeedY / 2;
    }

}

/**
 * Load the attributes for an fish node.
 *
 * This is the  base class version that loads the attributes
 * common to all fish. Override this to load custom attributes
 * for specific items.
 *
 * \param node The Xml node we are loading the fish from
 */
void CFish::XmlLoad(const std::shared_ptr<xmlnode::CXmlNode>& node)
{
    CItem::XmlLoad(node);
    mSpeedX = node->GetAttributeDoubleValue(L"speedx", 0);
    mSpeedY = node->GetAttributeDoubleValue(L"speedy", 0);
}