/**
 * \file Item.h
 *
 * \author Elizabeth Lipin
 *
 * Base class for item in aquarium
 */

#pragma once
#include "XmlNode.h"
#include<memory>
#include <string>



class CAquarium;

/**
* Base class for item in aquarium.
*/
class CItem
{
public:
	/// Destructor
	virtual ~CItem();
    
    /** The X location of the item
     * \returns X location in pixels */
    double GetX() const { return mX; }

    /** The Y location of the item
    * \returns Y location in pixels */
    double GetY() const { return mY; }

    /// Set the item location
    /// \param x X location
    /// \param y Y location
    void SetLocation(double x, double y) { mX = x; mY = y; }
    
    /// Default constructor (disabled)
    CItem() = delete;

    /// Copy constructor (disabled)
    CItem(const CItem&) = delete;
    /// Draw this item
    /// \param graphics Graphics device to draw on
    void Draw(Gdiplus::Graphics* graphics);
    /**
    * Save the item data
    * \param node an xml node of an item to save
    * \return a saved node
    */
    virtual std::shared_ptr<xmlnode::CXmlNode> XmlSave(const std::shared_ptr<xmlnode::CXmlNode>& node);
    /**
    * Load the item data
    * \param node an xml node of an item to load
    */
    virtual void XmlLoad(const std::shared_ptr<xmlnode::CXmlNode>& node);
    /** Test this item to see if it has been clicked on
     * \param x X location on the aquarium to test
     * \param y Y location on the aquarium to test
     * \return true if clicked on */
    bool HitTest(int x, int y);
    /// Handle updates for animation
    /// \param elapsed The time since the last update
    virtual void Update(double elapsed) {}
    /// Get the aquarium this item is in
    /// \returns Aquarium pointer
    CAquarium* GetAquarium() { return mAquarium; }
    /// Set the mirror status
    /// \param m New mirror flag
    void SetMirror(bool m) { mMirror = m; }
    /// Get the width of the aquarium
    /// \returns Item width
    int GetWidthItem() const { return mItemImage->GetWidth(); }
    /// Get the height of the aquarium
    /// \returns Item height
    int GetHeightItem() const { return mItemImage->GetHeight(); }
private:
    /// The aquarium this item is contained in
    CAquarium* mAquarium;

    // Item location in the aquarium
    double  mX = 0;     ///< X location for the center of the item
    double  mY = 0;     ///< Y location for the center of the item
    /// The image of this fish
    std::unique_ptr<Gdiplus::Bitmap> mItemImage;
    bool mMirror = false;   ///< True mirrors the item image
protected:
    CItem(CAquarium* aquarium, const std::wstring& filename);
};

