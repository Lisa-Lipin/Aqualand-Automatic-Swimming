/**
 * \file Dory.cpp
 *
 * \author Elizabeth Lipin
 */

#include "pch.h"
#include "Dory.h"
#include <string>
using namespace Gdiplus;
using namespace std;

/// Fish filename 
const wstring DoryImageName = L"images/dory.png";



/** Constructor
 * \param aquarium The aquarium this is a member of
*/
CDory::CDory(CAquarium* aquarium) : CFish(aquarium, DoryImageName)
{
}

/**
 * Save this item to an XML node
 * \param node The node we are going to be a child of
 */
std::shared_ptr<xmlnode::CXmlNode>
CDory::XmlSave(const std::shared_ptr<xmlnode::CXmlNode>& node)
{
    auto itemNode = CItem::XmlSave(node);

    itemNode->SetAttribute(L"type", L"dory");
    itemNode->SetAttribute(L"speedx", GetSpeedX());
    itemNode->SetAttribute(L"speedy", GetSpeedY());


    return itemNode;
}

/**
    * gets range for speed x
    * \param xRange a pair to put min and max x speed in
    */
void CDory::GetSpeedXRange(std::pair<double, double>& xRange)
{
    xRange.first = mMinSpeedX;
    xRange.second = mMaxSpeedX;
}

/**
    * gets range for speed y
    * \param xRange a pair to put min and max y speed in
    */
void CDory::GetSpeedYRange(std::pair<double, double>& xRange)
{
    xRange.first = mMinSpeedY;
    xRange.second = mMaxSpeedY;
}