#include "pch.h"
#include "CppUnitTest.h"

#include "Aquarium.h"
#include "FishBeta.h"
#include "Dory.h"
#include "Nemo.h"
#include "DecorCastle.h"
#include <regex>
#include <string>
#include <fstream>
#include <streambuf>
#include <vector>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;

const unsigned int RandomSeed = 1238197374;

namespace Testing
{
	TEST_CLASS(CAquariumTest)
	{
	public:

		/**
		* Create a path to a place to put temporary files
		*/
		wstring TempPath()
		{
			// Create a path to temporary files
			wchar_t path_nts[MAX_PATH];
			GetTempPath(MAX_PATH, path_nts);

			// Convert null terminated string to wstring
			return wstring(path_nts);
		}

		/**
		* Read a file into a wstring and return it.
		* \param filename Name of the file to read
		* \return File contents
		*/
		wstring ReadFile(const wstring& filename)
		{
			ifstream t(filename);
			wstring str((istreambuf_iterator<char>(t)),
				istreambuf_iterator<char>());

			return str;
		}
		/**
		 *  Populate an aquarium with three Beta fish
		 */
		void PopulateThreeBetas(CAquarium* aquarium)
		{
			srand(RandomSeed);

			shared_ptr<CFishBeta> fish1 = make_shared<CFishBeta>(aquarium);
			fish1->Initialize();
			fish1->SetLocation(100, 200);
			aquarium->Add(fish1);

			shared_ptr<CFishBeta> fish2 = make_shared<CFishBeta>(aquarium);
			fish2->Initialize();
			fish2->SetLocation(400, 400);
			aquarium->Add(fish2);

			shared_ptr<CFishBeta> fish3 = make_shared<CFishBeta>(aquarium);
			fish3->Initialize();
			fish3->SetLocation(600, 100);
			aquarium->Add(fish3);
		}
		
		void TestThreeBetas(wstring filename)
		{
			Logger::WriteMessage(filename.c_str());

			wstring xml = ReadFile(filename);
			Logger::WriteMessage(xml.c_str());

			// Ensure three items
			Assert::IsTrue(regex_search(xml, wregex(L"<aqua><item.*<item.*<item.*</aqua>")));

			// Ensure the positions are correct
			Assert::IsTrue(regex_search(xml, wregex(L"<item x=\"100\" y=\"200\"")));
			Assert::IsTrue(regex_search(xml, wregex(L"<item x=\"400\" y=\"400\"")));
			Assert::IsTrue(regex_search(xml, wregex(L"<item x=\"600\" y=\"100\"")));

			// Ensure the types are correct
			Assert::IsTrue(regex_search(xml,
				wregex(L"<aqua><item.* type=\"beta\" speedx=\"47\\.415082.*\" speedy=\"55\\.096285.*\"/><item.* type=\"beta\" speedx=\"46\\.2508011.*\" speedy=\"58\\.939176.*\"/><item.* type=\"beta\" speedx=\"41\\.1832026.*\" speedy=\"52\\.228766.*\"/></aqua>")));
		}

		/**
		 *  Populate an aquarium with all types of items
		 */
		void PopulateAllTypes(CAquarium* aquarium)
		{
			srand(RandomSeed);

			shared_ptr<CFishBeta> fish1 = make_shared<CFishBeta>(aquarium);
			fish1->Initialize();
			fish1->SetLocation(652, 307);
			aquarium->Add(fish1);

			shared_ptr<CDory> fish2 = make_shared<CDory>(aquarium);
			fish2->Initialize();
			fish2->SetLocation(736, 661);
			aquarium->Add(fish2);

			shared_ptr<CNemo> fish3 = make_shared<CNemo>(aquarium);
			fish3->Initialize();
			fish3->SetLocation(220, 398);
			aquarium->Add(fish3);

			shared_ptr<CDecorCastle> decor1 = make_shared<CDecorCastle>(aquarium);
			decor1->SetLocation(374, 183);
			aquarium->Add(decor1);
		}

		void TestAllTypes(wstring filename)
		{
			Logger::WriteMessage(filename.c_str());

			wstring xml = ReadFile(filename);
			Logger::WriteMessage(xml.c_str());

			// Ensure three items
			Assert::IsTrue(regex_search(xml, wregex(L"<aqua><item.*<item.*<item.*<item.*</aqua>")));

			// Ensure the positions are correct
			Assert::IsTrue(regex_search(xml, wregex(L"<item x=\"652\" y=\"307\"")));
			Assert::IsTrue(regex_search(xml, wregex(L"<item x=\"736\" y=\"661\"")));
			Assert::IsTrue(regex_search(xml, wregex(L"<item x=\"220\" y=\"398\"")));
			Assert::IsTrue(regex_search(xml, wregex(L"<item x=\"374\" y=\"183\"")));

			// Ensure the types are correct
			Assert::IsTrue(regex_search(xml,
				wregex(L"<aqua><item.* type=\"beta\" speedx=\"47\\.415082.*\" speedy=\"55\\.096285.*\"/><item.* type=\"dory\" speedx=\"78\\.752403.*\" speedy=\"67\\.878353.*\"/><item.* type=\"nemo\" speedx=\"82\\.366405.*\" speedy=\"64\\.4575334.*\"/><item.* type=\"castle\"/></aqua>")));
		}

		/**
	   * Test to ensure an aquarium .aqua file is empty
	   */
		void TestEmpty(wstring filename)
		{
			Logger::WriteMessage(filename.c_str());

			wstring xml = ReadFile(filename);
			Logger::WriteMessage(xml.c_str());
			Assert::IsTrue(regex_search(xml, wregex(L"<\\?xml.*\\?>")));
			Assert::IsTrue(regex_search(xml, wregex(L"<aqua/>")));
		}

		TEST_METHOD_INITIALIZE(methodName)
		{
			extern wchar_t g_dir[];
			::SetCurrentDirectory(g_dir);
		}
		
		TEST_METHOD(TestCAquariumConstruct)
		{
			CAquarium aquarium;
		}

		TEST_METHOD(TestCAquariumHitTest)
		{
			CAquarium aquarium;

			Assert::IsTrue(aquarium.HitTest(100, 200) == nullptr,
				L"Testing empty aquarium");

			shared_ptr<CFishBeta> fish1 = make_shared<CFishBeta>(&aquarium);
			fish1->Initialize();
			fish1->SetLocation(100, 200);
			aquarium.Add(fish1);

			Assert::IsTrue(aquarium.HitTest(100, 200) == fish1,
				L"Testing fish at 100, 200");

			Assert::IsFalse(aquarium.HitTest(10, 210) == fish1,
				L"Testing fish at 10, 210");
			Assert::IsTrue(aquarium.HitTest(10, 210) == nullptr,
				L"Testing fish at 10, 210");
			
			shared_ptr<CFishBeta> fish2 = make_shared<CFishBeta>(&aquarium);
			fish2->Initialize();
			fish2->SetLocation(100, 200);
			aquarium.Add(fish2);

			Assert::IsTrue(aquarium.HitTest(100, 200) == fish2,
				L"Testing fish at 100, 200");
		}

		//Below is a test for the MoveToEnd function
		//I altered the return for this test to verify that it works
		//TEST_METHOD(TestCAquariumMoveToEndTest) 
		//{
		//	CAquarium aquarium;

		//	shared_ptr<CFishBeta> fish1 = make_shared<CFishBeta>(&aquarium);
		//	fish1->SetLocation(100, 200);
		//	aquarium.Add(fish1);

		//	shared_ptr<CFishBeta> fish2 = make_shared<CFishBeta>(&aquarium);
		//	fish1->SetLocation(153, 210);
		//	aquarium.Add(fish2);

		//	Assert::IsTrue(aquarium.MoveToEnd(fish1) == fish1);

		//}

		TEST_METHOD(TestCAquariumSave)
		{
			// Create a path to temporary files
			wstring path = TempPath();

			// Create an aquarium
			CAquarium aquarium;

			//
			// First test, saving an empty aquarium
			//
			wstring file1 = path + L"test1.aqua";
			aquarium.Save(file1);

			TestEmpty(file1);

			//
			// Now populate the aquarium
			//

			PopulateThreeBetas(&aquarium);

			wstring file2 = path + L"test2.aqua";
			aquarium.Save(file2);

			TestThreeBetas(file2);

			//
		   // Test all types
		   //
			CAquarium aquarium3;
			PopulateAllTypes(&aquarium3);

			wstring file3 = path + L"test3.aqua";
			aquarium3.Save(file3);

			TestAllTypes(file3);
		}

		TEST_METHOD(TestCAquariumClear)
		{
			// Create a path to temporary files
			wstring path = TempPath();

			// Create an aquarium
			CAquarium aquarium;

			//Populate aquarium
			PopulateAllTypes(&aquarium);

			aquarium.Clear();
			wstring file = path + L"testclear.aqua";
			aquarium.Save(file);

			TestEmpty(file);
			
		}

		TEST_METHOD(TestCAquariumLoad)
		{
			// Create a path to temporary files
			wstring path = TempPath();

			// Create two aquariums
			CAquarium aquarium, aquarium2;

			//
			// First test, saving an empty aquarium
			//
			wstring file1 = path + L"test1.aqua";

			aquarium.Save(file1);
			TestEmpty(file1);

			aquarium2.Load(file1);
			aquarium2.Save(file1);
			TestEmpty(file1);

			//
			// Now populate the aquarium
			//

			PopulateThreeBetas(&aquarium);

			wstring file2 = path + L"test2.aqua";
			aquarium.Save(file2);
			TestThreeBetas(file2);

			aquarium2.Load(file2);
			aquarium2.Save(file2);
			TestThreeBetas(file2);

			//
			// Test all types
			//
			CAquarium aquarium3;
			PopulateAllTypes(&aquarium3);

			wstring file3 = path + L"test3.aqua";
			aquarium3.Save(file3);
			TestAllTypes(file3);

			aquarium2.Load(file3);
			aquarium2.Save(file3);
			TestAllTypes(file3);
		}
	};
}