/**
 * \file Aquarium.h
 *
 * \author Elizabeth Lipin
 *
 * Class that forms aquarium
 */

#pragma once
#include<memory>
#include<vector>
#include "Item.h"

/**
* Class that forms aquarium
*/
class CAquarium
{
public:
	/// constructor
	CAquarium();
	void Add(std::shared_ptr<CItem> item);
	std::shared_ptr<CItem> HitTest(int x, int y);
	void Save(const std::wstring& filename);
	void XmlItem(const std::shared_ptr<xmlnode::CXmlNode>& node);
	void Update(double elapsed);
	void Load(const std::wstring& filename);
	void Clear();
	/// draw the aquarium
	void OnDraw(Gdiplus::Graphics* graphics); 
	/// move clicked items to end of vector
	void MoveToEnd(std::shared_ptr<CItem> item);
	/// Get the width of the aquarium
	/// \returns Aquarium width
	int GetWidth() const { return mBackground->GetWidth(); }
	/// Get the height of the aquarium
	/// \returns Aquarium height
	int GetHeight() const { return mBackground->GetHeight(); }
	/// iterate through items and see its too close
	/// \param item a fish to check
	/// \return whether fish is too close to another
	bool TooClose(CItem* item);
private:
	std::unique_ptr<Gdiplus::Bitmap> mBackground; ///< Background image to use
	/// All of the items to populate our aquarium
	std::vector<std::shared_ptr<CItem> > mItems;
};

