#include "pch.h"
#include "CppUnitTest.h"
#include "Aquarium.h"
#include "Angler.h"
#include <string>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;

/// Fish filename 
const std::wstring FishBetaImageName = L"images/beta.png";

/** Mock class for testing CItem */
class CItemMock : public CItem
{
public:
	CItemMock(CAquarium* aquarium) : CItem(aquarium, FishBetaImageName) {}

	virtual void Draw(Gdiplus::Graphics* graphics) {}

	/** Test to see if we clicked on this item
	 * \param x X location
	 * \param y Y location
	 * \returns true if we did click on the item */
	virtual bool HitTest(int x, int y) { return false; }
};

class CAnglerMock : public CAngler
{
public:
	CAnglerMock(CAquarium* aquarium) : CAngler(aquarium) {}
	/// checks if fish clicked
	/// \param x x-coord
	/// \param y y-coord
	/// \return true if clicked
	bool HitTest(int x, int y) { return false; }

	/// Default constructor (disabled)
	CAnglerMock() = delete;

	/// Copy constructor (disabled)
	CAnglerMock(const CAnglerMock&) = delete;
	/// checks if fish can catch others
	/// \return true
	bool CanCatch() { return true; }
	//void PreMoved(double changeX, double changeY) {}
	
};

namespace Testing
{
	TEST_CLASS(CAngler)
	{
	public:

		TEST_METHOD_INITIALIZE(methodName)
		{
			extern wchar_t g_dir[];
			::SetCurrentDirectory(g_dir);
		}
		
		TEST_METHOD(CatchFish)
		{
			// Create an aquarium and two items
			CAquarium aquarium;
			shared_ptr<CAnglerMock> angler = make_shared<CAnglerMock>(&aquarium);
			shared_ptr<CItemMock> item2 = make_shared<CItemMock>(&aquarium);

			angler->SetLocation(250, 17.2);
			item2->SetLocation(53.1, 207.8);

			angler->CatchFish(item2);

			Assert::IsFalse(angler->IsCaughtFish(item2));

			angler->SetLocation(10.5, 100);
			item2->SetLocation(53.1, 107.8);

			angler->CatchFish(item2);

			Assert::IsTrue(angler->IsCaughtFish(item2));

		}

	};
}