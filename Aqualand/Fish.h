/**
 * \file Fish.h
 *
 * \author Elizabeth Lipin
 *
 * Class that forms fish
 */

#pragma once
#include "Item.h"

/**
 * Base class for a fish
 * This applies to all of the fish, but not the decor
 * items in the aquarium.
 */
class CFish :
    public CItem
{
public:
    /// Default constructor (disabled)
    CFish() = delete;

    /// Copy constructor (disabled)
    CFish(const CFish&) = delete;
    /**
    * Updates fish coordinates and speed
    * \param elapsed the time gone by
    */
    void Update(double elapsed);
    /**
    * Load the fish data
    * \param node an xml node of a fish to load
    */
    void XmlLoad(const std::shared_ptr<xmlnode::CXmlNode>& node) override;
    /**
    * gets the speed X
    * \return double speedX
    */
    double GetSpeedX() { return mSpeedX; }
    /**
    * gets the speed Y
    * \return double speedY
    */
    double GetSpeedY() { return mSpeedY; }
    /**
    * initializes fish
    */
    void Initialize();
    /**
    * Get the range of x speeds
    * \param xRange a pair which is the min and max speed x
    */
    virtual void GetSpeedXRange(std::pair<double, double>& xRange) = 0;
    /**
    * Get the range of y speeds
    * \param yRange a pair which is the min and max speed y
    */
    virtual void GetSpeedYRange(std::pair<double, double>& yRange) = 0;
    
private:
    /// Fish speed in the X direction
    double mSpeedX = 0;

    /// Fish speed in the Y direction
    double mSpeedY = 0;
    
protected:
    CFish(CAquarium* aquarium, const std::wstring& filename);
    
};

