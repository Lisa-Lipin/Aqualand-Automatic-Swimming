/**
 * \file FishBeta.cpp
 *
 * \author Elizabeth Lipin
 */

#include "pch.h"
#include "FishBeta.h"
#include <string>
using namespace Gdiplus;
using namespace std;

 /// Fish filename 
const wstring FishBetaImageName = L"images/beta.png";

 /** Constructor
  * \param aquarium The aquarium this is a member of
 */
CFishBeta::CFishBeta(CAquarium* aquarium) : CFish(aquarium, FishBetaImageName)
{
}


/**
 * Save this item to an XML node
 * \param node The node we are going to be a child of
 */
std::shared_ptr<xmlnode::CXmlNode>
CFishBeta::XmlSave(const std::shared_ptr<xmlnode::CXmlNode>& node)
{
    auto itemNode = CItem::XmlSave(node);

    itemNode->SetAttribute(L"type", L"beta");
    itemNode->SetAttribute(L"speedx", GetSpeedX());
    itemNode->SetAttribute(L"speedy", GetSpeedY());

    return itemNode;
}

/**
    * gets range for speed x
    * \param xRange a pair to put min and max x speed in
    */
void CFishBeta::GetSpeedXRange(std::pair<double, double>& xRange)
{
    xRange.first = mMinSpeedX;
    xRange.second = mMaxSpeedX;
}

/**
    * gets range for speed y
    * \param xRange a pair to put min and max y speed in
    */
void CFishBeta::GetSpeedYRange(std::pair<double, double>& xRange)
{
    xRange.first = mMinSpeedY;
    xRange.second = mMaxSpeedY;
}