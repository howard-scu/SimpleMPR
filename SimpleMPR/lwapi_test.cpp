#define CATCH_CONFIG_MAIN
#include <catch2\catch.hpp>

#include "lwMPRBase.h"
#include "lwUtils.h"
#include "lwMPRLogic.h"

#define PI 3.1415926

using Catch::Matchers::Equals;


#define CHECK_VEC_EQUAL(x,y)	do{					\
REQUIRE(x.size() == y.size());						\
for(int i=0;i<x.size();i++)							\
	CHECK(x[i] == Approx(y[i]).margin(1e-5));		\
}while(0)

#define CHECK_MAT_EQUAL(x,y)	do{										\
for(int i=0;i<4;i++)													\
	for(int j=0;j<4;j++){												\
    INFO("MAT["<<i<<"]["<<j<<"] = " << x->GetElement(i,j));				\
	CHECK(x->GetElement(i,j) == Approx(y[i*4+j]).margin(1e-5));}		\
}while(0)

TEST_CASE("lwMPRBase单元测试", "[single-file]")
{
	shared_ptr<lwMPRBase> base = make_shared<lwMPRBase>();
	SECTION("测试Get/Set")
	{
		base->SetView(lwMPRBase::AXIAL);
		CHECK(base->GetView() == lwMPRBase::AXIAL);
		base->SetView(lwMPRBase::CORONAL);
		CHECK(base->GetView() == lwMPRBase::CORONAL);
		base->SetView(lwMPRBase::SAGITTAL);
		CHECK(base->GetView() == lwMPRBase::SAGITTAL);

		// 初始化
		CHECK(base->GetXPos() == Approx(0.0).epsilon(1e-5));
		CHECK(base->GetYPos() == Approx(0.0).epsilon(1e-5));
		CHECK(base->GetZPos() == Approx(0.0).epsilon(1e-5));
		CHECK(base->GetAlpha() == Approx(0.0).epsilon(1e-5));
		CHECK(base->GetBeta() == Approx(0.0).epsilon(1e-5));
		CHECK(base->GetGamma() == Approx(0.0).epsilon(1e-5));

		// Get/Set
		base->SetXPos(1.2);
		base->SetYPos(11.2);
		base->SetZPos(-21.2);
		CHECK(base->GetXPos() == Approx(1.2).epsilon(1e-5));
		CHECK(base->GetYPos() == Approx(11.2).epsilon(1e-5));
		CHECK(base->GetZPos() == Approx(-21.2).epsilon(1e-5));
		base->SetAlpha(1.2);
		base->SetBeta(11.2);
		base->SetGamma(-21.2);
		CHECK(base->GetAlpha() == Approx(1.2).epsilon(1e-5));
		CHECK(base->GetBeta() == Approx(11.2).epsilon(1e-5));
		CHECK(base->GetGamma() == Approx(-21.2).epsilon(1e-5));
	}
	SECTION("测试旋转角度")
	{
		auto a = PI / 3;
		auto b = PI / 5;
		auto g = PI / 4;
		base->SetAlpha(a);
		base->SetBeta(b);
		base->SetGamma(g);
		auto trans = base->GetTransfromMatrix();
		vector<double> result = {
		cos(b)*cos(g),-cos(a)*sin(g) + sin(a)*sin(b)*cos(g),sin(a)*sin(g) + cos(a)*sin(b)*cos(g),0,
		cos(b)*sin(g),cos(a)*cos(g) + sin(a)*sin(b)*sin(g),-sin(a)*cos(g) + cos(a)*sin(b)*sin(g),0,
		-sin(b),sin(a)*cos(b),cos(a)*cos(b),0,
			0,0,0,1
		};
		CHECK_MAT_EQUAL(trans, result);
	}
}







////TEST_CASE("test for lwMPRBase", "[single-file]")
////{
////	shared_ptr<lwMPRBase> base = make_shared<lwMPRBase>();
////
////	SECTION("AXIAL VIEW")
////	{
////		base->SetView(lwMPRBase::AXIAL);
////		CHECK(base->GetView() == lwMPRBase::AXIAL);
////
////		CHECK(base->GetXPos() == Approx(0.0).epsilon(1e-5));
////		CHECK(base->GetYPos() == Approx(0.0).epsilon(1e-5));
////		CHECK(base->GetZPos() == Approx(0.0).epsilon(1e-5));
////
////		base->SetXPos(0.6);
////		base->SetYPos(-0.6);
////
////		CHECK(base->GetXPos() == Approx(0.6).epsilon(1e-5));
////		CHECK(base->GetYPos() == Approx(-0.6).epsilon(1e-5));
////
////		base->SetZPos(9.6);
////		CHECK(base->GetZPos() == Approx(9.6).epsilon(1e-5));
////
////		CHECK_THAT(base->GetXAxis(), Equals(vector<double>{1, 0, 0}));
////		CHECK_THAT(base->GetYAxis(), Equals(vector<double>{0, 1, 0}));
////		CHECK_THAT(base->GetZAxis(), Equals(vector<double>{0, 0, 1}));
////
////		//CHECK_THAT(base->GetHoriVector(), Equals(vector<double>{1, 0, 0}));
////		//CHECK_THAT(base->GetVertVector(), Equals(vector<double>{0, 1, 0}));
////	}
////	SECTION("CORONAL VIEW")
////	{
////		base->SetView(lwMPRBase::CORONAL);
////		CHECK(base->GetView() == lwMPRBase::CORONAL);
////
////		CHECK(base->GetXPos() == Approx(0.0).epsilon(1e-5));
////		CHECK(base->GetYPos() == Approx(0.0).epsilon(1e-5));
////		CHECK(base->GetZPos() == Approx(0.0).epsilon(1e-5));
////
////		base->SetXPos(0.6);
////		CHECK(base->GetXPos() == Approx(0.6).epsilon(1e-5));
////
////		CHECK(base->GetYPos() == Approx(0.0).epsilon(1e-5));
////
////		base->SetZPos(9.6);
////		CHECK(base->GetZPos() == Approx(9.6).epsilon(1e-5));
////
////		CHECK_THAT(base->GetXAxis(), Equals(vector<double>{1, 0, 0}));
////		CHECK_THAT(base->GetYAxis(), Equals(vector<double>{0, 1, 0}));
////		CHECK_THAT(base->GetZAxis(), Equals(vector<double>{0, 0, 1}));
////
////		base->SetYAxis(vector<double>{1, 1, 1});
////		CHECK_THAT(base->GetYAxis(), Equals(vector<double>{1, 1, 1}));
////
////		//CHECK_THAT(base->GetHoriVector(), Equals(vector<double>{1, 0, 0}));
////		//CHECK_THAT(base->GetVertVector(), Equals(vector<double>{0, 0, 1}));
////	}
////	SECTION("SAGITTAL VIEW")
////	{
////		base->SetView(lwMPRBase::SAGITTAL);
////		CHECK(base->GetView() == lwMPRBase::SAGITTAL);
////
////		CHECK(base->GetXPos() == Approx(0.0).epsilon(1e-5));
////		CHECK(base->GetYPos() == Approx(0.0).epsilon(1e-5));
////		CHECK(base->GetZPos() == Approx(0.0).epsilon(1e-5));
////
////		base->SetXPos(0.6);
////		CHECK(base->GetXPos() == Approx(0.6).epsilon(1e-5));
////
////		base->SetYPos(-0.6);
////		CHECK(base->GetYPos() == Approx(-0.6).epsilon(1e-5));
////
////		CHECK(base->GetZPos() == Approx(0.0).epsilon(1e-5));
////
////		CHECK_THAT(base->GetXAxis(), Equals(vector<double>{1, 0, 0}));
////		CHECK_THAT(base->GetYAxis(), Equals(vector<double>{0, 1, 0}));
////		CHECK_THAT(base->GetZAxis(), Equals(vector<double>{0, 0, 1}));
////
////		base->SetYAxis(vector<double>{1, 1, 1});
////		CHECK_THAT(base->GetYAxis(), Equals(vector<double>{1, 1, 1}));
////
////		//CHECK_THAT(base->GetHoriVector(), Equals(vector<double>{0, 1, 0}));
////		//CHECK_THAT(base->GetVertVector(), Equals(vector<double>{0, 0, 1}));
////	}
////}
//
//
//TEST_CASE("test for lwUtils", "[single-file]")
//{
//	vector<double> v{ 3,4,0 };
//	lwUtils::Normalize(v);
//	CHECK_THAT(v, Equals(vector<double>{3.0 / 5, 4.0 / 5, 0}));
//
//	vector<double> v1{ 1,0,0 };
//	vector<double> v2{ 0,1,0 };
//
//	v = lwUtils::CrossProduct(v1, v2);
//	CHECK_THAT(v, Equals(vector<double>{0, 0, 1}));
//
//	v = lwUtils::CrossProduct(v2, v1);
//	CHECK_THAT(v, Equals(vector<double>{0, 0, -1}));
//}
//
//
//TEST_CASE("test slice sync for lwMPRLogic", "[single-file]")
//{
//	shared_ptr<lwMPRLogic> viewer1 = make_shared<lwMPRLogic>();
//	viewer1->SetView(lwMPRBase::AXIAL);
//
//	shared_ptr<lwMPRLogic> viewer2 = make_shared<lwMPRLogic>();
//	viewer2->SetView(lwMPRBase::CORONAL);
//
//	shared_ptr<lwMPRLogic> viewer3 = make_shared<lwMPRLogic>();
//	viewer3->SetView(lwMPRBase::SAGITTAL);
//
//	viewer1->SyncViewer(viewer2.get());
//	viewer2->SyncViewer(viewer3.get());
//	viewer3->SyncViewer(viewer1.get());
//
//	viewer1->UpdateSlice(11);
//	CHECK(viewer1->GetZPos() == Approx(11).epsilon(1e-6));
//	CHECK(viewer2->GetZPos() == Approx(11).epsilon(1e-6));
//	CHECK(viewer3->GetZPos() == Approx(11).epsilon(1e-6));
//
//	viewer2->UpdateSlice(22);
//	CHECK(viewer1->GetYPos() == Approx(22).epsilon(1e-6));
//	CHECK(viewer2->GetYPos() == Approx(22).epsilon(1e-6));
//	CHECK(viewer3->GetYPos() == Approx(22).epsilon(1e-6));
//
//	viewer3->UpdateSlice(33);
//	CHECK(viewer1->GetXPos() == Approx(33).epsilon(1e-6));
//	CHECK(viewer2->GetXPos() == Approx(33).epsilon(1e-6));
//	CHECK(viewer3->GetXPos() == Approx(33).epsilon(1e-6));
//}
//
//TEST_CASE("test position sync for lwMPRLogic", "[single-file]")
//{
//	shared_ptr<lwMPRLogic> viewer1 = make_shared<lwMPRLogic>();
//	viewer1->SetView(lwMPRBase::AXIAL);
//
//	shared_ptr<lwMPRLogic> viewer2 = make_shared<lwMPRLogic>();
//	viewer2->SetView(lwMPRBase::CORONAL);
//
//	shared_ptr<lwMPRLogic> viewer3 = make_shared<lwMPRLogic>();
//	viewer3->SetView(lwMPRBase::SAGITTAL);
//
//	viewer1->SyncViewer(viewer2.get());
//	viewer2->SyncViewer(viewer3.get());
//	viewer3->SyncViewer(viewer1.get());
//
//	viewer1->UpdatePosition(11, 22);
//	CHECK(viewer1->GetXPos() == Approx(11).epsilon(1e-6));
//	CHECK(viewer1->GetYPos() == Approx(22).epsilon(1e-6));
//	CHECK(viewer2->GetXPos() == Approx(11).epsilon(1e-6));
//	CHECK(viewer2->GetYPos() == Approx(22).epsilon(1e-6));
//	CHECK(viewer3->GetXPos() == Approx(11).epsilon(1e-6));
//	CHECK(viewer3->GetYPos() == Approx(22).epsilon(1e-6));
//
//	viewer2->UpdatePosition(33, 44);
//	CHECK(viewer1->GetXPos() == Approx(33).epsilon(1e-6));
//	CHECK(viewer1->GetZPos() == Approx(44).epsilon(1e-6));
//	CHECK(viewer2->GetXPos() == Approx(33).epsilon(1e-6));
//	CHECK(viewer2->GetZPos() == Approx(44).epsilon(1e-6));
//	CHECK(viewer3->GetXPos() == Approx(33).epsilon(1e-6));
//	CHECK(viewer3->GetZPos() == Approx(44).epsilon(1e-6));
//}
//
////TEST_CASE("test vx/vy sync for lwMPRLogic", "[single-file]")
////{
////	shared_ptr<lwMPRLogic> viewer1 = make_shared<lwMPRLogic>();
////	viewer1->SetView(lwMPRBase::AXIAL);
////
////	shared_ptr<lwMPRLogic> viewer2 = make_shared<lwMPRLogic>();
////	viewer2->SetView(lwMPRBase::CORONAL);
////
////	shared_ptr<lwMPRLogic> viewer3 = make_shared<lwMPRLogic>();
////	viewer3->SetView(lwMPRBase::SAGITTAL);
////
////	viewer1->SyncViewer(viewer2.get());
////	viewer2->SyncViewer(viewer3.get());
////	viewer3->SyncViewer(viewer1.get());
////
////	CHECK_THAT(viewer1->GetHoriVector(), Equals(vector<double>{1, 0, 0}));
////	CHECK_THAT(viewer1->GetVertVector(), Equals(vector<double>{0, 1, 0}));
////	CHECK_THAT(viewer2->GetHoriVector(), Equals(vector<double>{1, 0, 0}));
////	CHECK_THAT(viewer2->GetVertVector(), Equals(vector<double>{0, 0, 1}));
////	CHECK_THAT(viewer3->GetHoriVector(), Equals(vector<double>{0, 1, 0}));
////	CHECK_THAT(viewer3->GetVertVector(), Equals(vector<double>{0, 0, 1}));
////
////	viewer1->UpdateHoriVector(vector<double>{.6, .8, 0});
////	CHECK_THAT(viewer1->GetVertVector(), Equals(vector<double>{-0.8, 0.6, 0}));
////
////	CHECK_THAT(viewer1->GetXAxis(), Equals(vector<double>{1, 0, 0}));
////	CHECK_THAT(viewer1->GetYAxis(), Equals(vector<double>{0, 1, 0}));
////	CHECK_THAT(viewer1->GetZAxis(), Equals(vector<double>{0, 0, 1}));
////
////	CHECK_THAT(viewer2->GetXAxis(), Equals(vector<double>{0.6, 0.8, 0}));
////	CHECK_THAT(viewer2->GetYAxis(), Equals(vector<double>{-0.8, 0.6, 0}));
////	CHECK_THAT(viewer2->GetZAxis(), Equals(vector<double>{0, 0, 1}));
////
////	CHECK_THAT(viewer3->GetXAxis(), Equals(vector<double>{.6, .8, 0}));
////	CHECK_THAT(viewer3->GetYAxis(), Equals(vector<double>{-0.8, 0.6, 0}));
////	CHECK_THAT(viewer3->GetZAxis(), Equals(vector<double>{0, 0, 1}));
////
////	CHECK_THAT(viewer1->GetHoriVector(), Equals(vector<double>{.6, .8, 0}));
////	CHECK_THAT(viewer1->GetVertVector(), Equals(vector<double>{-0.8, 0.6, 0}));
////	CHECK_THAT(viewer2->GetHoriVector(), Equals(vector<double>{0.6, 0.8, 0}));
////	CHECK_THAT(viewer2->GetVertVector(), Equals(vector<double>{0, 0, 1}));
////	CHECK_THAT(viewer3->GetHoriVector(), Equals(vector<double>{-0.8, 0.6, 0}));
////	CHECK_THAT(viewer3->GetVertVector(), Equals(vector<double>{0, 0, 1}));
////
////	viewer3->UpdateVertVector(vector<double>{0, 0.6, 0.8});			// => Z
////	CHECK_THAT(viewer3->GetHoriVector(), Equals(vector<double>{-0.64, 0.48, -0.36}));	// =>Y
////
////	CHECK_THAT(viewer3->GetXAxis(), Equals(vector<double>{.6, .8, 0}));
////	CHECK_THAT(viewer3->GetYAxis(), Equals(vector<double>{-0.8, 0.6, 0}));
////	CHECK_THAT(viewer3->GetZAxis(), Equals(vector<double>{0, 0, 1}));
////
////	CHECK_THAT(viewer1->GetXAxis(), Equals(vector<double>{1, 0, 0}));
////	//CHECK_THAT(viewer1->GetYAxis(), Equals(vector<double>{0, 0, 1}));
////	CHECK_THAT(viewer1->GetZAxis(), Equals(vector<double>{0, 0.6, 0.8}));
////
////	CHECK_THAT(viewer2->GetXAxis(), Equals(vector<double>{0, 1, 0}));
////	CHECK_THAT(viewer2->GetYAxis(), Equals(vector<double>{-0.64, 0.48, -0.36}));
////	//CHECK_THAT(viewer2->GetZAxis(), Equals(vector<double>{0, 0, 1}));
////}
