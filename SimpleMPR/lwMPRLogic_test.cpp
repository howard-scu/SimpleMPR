//#define CATCH_CONFIG_MAIN
//#include <catch2\catch.hpp>
//
//#include "lwMPRLogic.h"
//
//using Catch::Matchers::Equals;
//
//TEST_CASE("Test for viewer synchron", "[single-file]")
//{
//	shared_ptr<lwMPRLogic> viewer1 = make_shared<lwMPRLogic>();
//	shared_ptr<lwMPRLogic> viewer2 = make_shared<lwMPRLogic>();
//	shared_ptr<lwMPRLogic> viewer3 = make_shared<lwMPRLogic>();
//	viewer1->SetView(lwMPRLogic::AXIAL);
//	viewer2->SetView(lwMPRLogic::CORONAL);
//	viewer3->SetView(lwMPRLogic::SAGITTAL);
//	SECTION("Sync I")
//	{
//		viewer1->UpdateXAxis(vector<double>{1, 2, 3});
//		viewer1->UpdateCenter(vector<double>{6, 6, 6});
//		auto v1 = viewer1->GetXAxis();
//		auto v2 = viewer1->GetYAxis();
//		auto v3 = viewer1->GetZAxis();
//		auto v4 = viewer1->GetCenter();
//		CHECK_THAT(v1, Equals(vector<double>{1, 2, 3}));
//		CHECK_THAT(v2, Equals(vector<double>{0, 1, 0}));
//		CHECK_THAT(v3, Equals(vector<double>{0, 0, 1}));
//		CHECK_THAT(v4, Equals(vector<double>{6, 6, 6}));
//	}
//	SECTION("Sync II")
//	{
//		viewer1->SyncView(viewer2.get());
//		viewer1->UpdateXAxis(vector<double>{1, 2, 3});
//		viewer1->UpdateCenter(vector<double>{11, 22, 33});
//		auto v1 = viewer1->GetXAxis();
//		auto v2 = viewer2->GetXAxis();
//		auto v3 = viewer1->GetCenter();
//		auto v4 = viewer2->GetCenter();
//		CHECK_THAT(v1, Equals(vector<double>{1, 2, 3}));
//		CHECK_THAT(v2, Equals(vector<double>{1, 2, 3}));
//		CHECK_THAT(v3, Equals(vector<double>{11, 22, 33}));
//		CHECK_THAT(v4, Equals(vector<double>{11, 22, 33}));
//	}
//	SECTION("Sync III")
//	{
//		viewer1->SyncView(viewer2.get());
//		viewer2->UpdateXAxis(vector<double>{1, 2, 3});
//		viewer2->UpdateCenter(vector<double>{6, 6, 6});
//		auto v1 = viewer1->GetXAxis();
//		auto v2 = viewer2->GetXAxis();
//		auto v3 = viewer1->GetCenter();
//		auto v4 = viewer2->GetCenter();
//		CHECK_THAT(v1, Equals(vector<double>{1, 0, 0}));
//		CHECK_THAT(v2, Equals(vector<double>{1, 2, 3}));
//		CHECK_THAT(v3, Equals(vector<double>{0, 0, 0}));
//		CHECK_THAT(v4, Equals(vector<double>{6, 6, 6}));
//	}
//	SECTION("Sync IV")
//	{
//		viewer1->SyncView(viewer2.get());
//		viewer2->SyncView(viewer3.get());
//		viewer3->SyncView(viewer1.get());
//
//		viewer1->UpdateXAxis(vector<double>{1, 2, 3});
//		viewer2->UpdateYAxis(vector<double>{4, 5, 6});
//		viewer3->UpdateZAxis(vector<double>{7, 8, 9});
//		viewer3->UpdateCenter(vector<double>{6, 6, 6});
//
//		auto v1 = viewer2->GetXAxis();
//		auto v2 = viewer3->GetYAxis();
//		auto v3 = viewer1->GetZAxis();
//		auto v4 = viewer2->GetCenter();
//		CHECK_THAT(v1, Equals(vector<double>{1, 2, 3}));
//		CHECK_THAT(v2, Equals(vector<double>{4, 5, 6}));
//		CHECK_THAT(v3, Equals(vector<double>{7, 8, 9}));
//		CHECK_THAT(v4, Equals(vector<double>{6, 6, 6}));
//	}
//}
//
