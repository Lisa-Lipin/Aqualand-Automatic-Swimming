/**
 * \file FishBeta.h
 *
 * \author Elizabeth Lipin
 *
 * Class that forms beta fish in aquarium
 */
#pragma once
#include "Item.h"
#include "Fish.h"
#include<memory>
/**
* Class that forms beta fish in aquarium
*/
class CFishBeta :
    public CFish
{
public:
    CFishBeta(CAquarium* aquarium);
    /// Default constructor (disabled)
    CFishBeta() = delete;

    /// Copy constructor (disabled)
    CFishBeta(const CFishBeta&) = delete;
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
    const double mMaxSpeedX = 50;
    /// min speed for x
    const double mMinSpeedX = 40;
    /// max speed for y
    const double mMaxSpeedY = 60;
    /// min speed for y
    const double mMinSpeedY = 50;
};

