/**
 * \file Dory.h
 *
 * \author Elizabeth Lipin
 *
 * Class that forms dory fish in aquarium
 */
#pragma once
#include "Item.h"
#include "Fish.h"
#include<memory>
 /**
 * Class that forms dory fish in aquarium
 */
class CDory :
    public CFish
{
public:
    CDory(CAquarium* aquarium);
    /// Default constructor (disabled)
    CDory() = delete;

    /// Copy constructor (disabled)
    CDory(const CDory&) = delete;
    /**
   * Saves fish
   *
   * \param node a node to save fish to
   * \return shared pointer to node
   */
    virtual std::shared_ptr<xmlnode::CXmlNode>
        XmlSave(const std::shared_ptr<xmlnode::CXmlNode>& node) override;
    /**
    * gets range for speed x
    * \param xRange a pair to put min and max x speed in
    */
    void GetSpeedXRange(std::pair<double, double>& xRange);
    /**
    * gets range for speed y
    * \param xRange a pair to put min and max y speed in
    */
    void GetSpeedYRange(std::pair<double, double>& xRange);
private:
    /// max speed for x
    const double mMaxSpeedX = 90;
    /// min speed for x
    const double mMinSpeedX = 60;
    /// max speed for y
    const double mMaxSpeedY = 70;
    /// min speed for y
    const double mMinSpeedY = 50;

};

