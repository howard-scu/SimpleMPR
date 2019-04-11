#define CATCH_CONFIG_MAIN
#include <catch2\catch.hpp>

#include "lwMPRBase.h"
#include "lwUtils.h"
#include "lwMPRLogic.h"

using Catch::Matchers::Equals;

TEST_CASE("test for lwMPRBase", "[single-file]")
{
	shared_ptr<lwMPRBase> base = make_shared<lwMPRBase>();

	SECTION("AXIAL VIEW")
	{
		base->SetView(lwMPRBase::AXIAL);
		CHECK(base->GetView() == lwMPRBase::AXIAL);

		CHECK(base->GetXPos() == Approx(0.0).epsilon(1e-5));
		CHECK(base->GetYPos() == Approx(0.0).epsilon(1e-5));
		CHECK(base->GetZPos() == Approx(0.0).epsilon(1e-5));

		base->SetXPos(0.6);
		base->SetYPos(-0.6);

		CHECK(base->GetXPos() == Approx(0.6).epsilon(1e-5));
		CHECK(base->GetYPos() == Approx(-0.6).epsilon(1e-5));

		base->SetZPos(9.6);
		CHECK(base->GetZPos() == Approx(9.6).epsilon(1e-5));

		CHECK_THAT(base->GetXAxis(), Equals(vector<double>{1, 0, 0}));
		CHECK_THAT(base->GetYAxis(), Equals(vector<double>{0, 1, 0}));
		CHECK_THAT(base->GetZAxis(), Equals(vector<double>{0, 0, 1}));

		CHECK_THAT(base->GetHoriVector(), Equals(vector<double>{1, 0, 0}));
		CHECK_THAT(base->GetVertVector(), Equals(vector<double>{0, 1, 0}));
	}
	SECTION("CORONAL VIEW")
	{
		base->SetView(lwMPRBase::CORONAL);
		CHECK(base->GetView() == lwMPRBase::CORONAL);

		CHECK(base->GetXPos() == Approx(0.0).epsilon(1e-5));
		CHECK(base->GetYPos() == Approx(0.0).epsilon(1e-5));
		CHECK(base->GetZPos() == Approx(0.0).epsilon(1e-5));

		base->SetXPos(0.6);
		CHECK(base->GetXPos() == Approx(0.6).epsilon(1e-5));

		CHECK(base->GetYPos() == Approx(0.0).epsilon(1e-5));

		base->SetZPos(9.6);
		CHECK(base->GetZPos() == Approx(9.6).epsilon(1e-5));

		CHECK_THAT(base->GetXAxis(), Equals(vector<double>{1, 0, 0}));
		CHECK_THAT(base->GetYAxis(), Equals(vector<double>{0, 1, 0}));
		CHECK_THAT(base->GetZAxis(), Equals(vector<double>{0, 0, 1}));

		base->SetYAxis(vector<double>{1, 1, 1});
		CHECK_THAT(base->GetYAxis(), Equals(vector<double>{1, 1, 1}));

		CHECK_THAT(base->GetHoriVector(), Equals(vector<double>{1, 0, 0}));
		CHECK_THAT(base->GetVertVector(), Equals(vector<double>{0, 0, 1}));
	}
	SECTION("SAGITTAL VIEW")
	{
		base->SetView(lwMPRBase::SAGITTAL);
		CHECK(base->GetView() == lwMPRBase::SAGITTAL);

		CHECK(base->GetXPos() == Approx(0.0).epsilon(1e-5));
		CHECK(base->GetYPos() == Approx(0.0).epsilon(1e-5));
		CHECK(base->GetZPos() == Approx(0.0).epsilon(1e-5));

		base->SetXPos(0.6);
		CHECK(base->GetXPos() == Approx(0.6).epsilon(1e-5));

		base->SetYPos(-0.6);
		CHECK(base->GetYPos() == Approx(-0.6).epsilon(1e-5));

		CHECK(base->GetZPos() == Approx(0.0).epsilon(1e-5));

		CHECK_THAT(base->GetXAxis(), Equals(vector<double>{1, 0, 0}));
		CHECK_THAT(base->GetYAxis(), Equals(vector<double>{0, 1, 0}));
		CHECK_THAT(base->GetZAxis(), Equals(vector<double>{0, 0, 1}));

		base->SetYAxis(vector<double>{1, 1, 1});
		CHECK_THAT(base->GetYAxis(), Equals(vector<double>{1, 1, 1}));

		CHECK_THAT(base->GetHoriVector(), Equals(vector<double>{0, 1, 0}));
		CHECK_THAT(base->GetVertVector(), Equals(vector<double>{0, 0, 1}));
	}
}


TEST_CASE("test for lwUtils", "[single-file]")
{
	vector<double> v{ 3,4,0 };
	lwUtils::Normalize(v);
	CHECK_THAT(v, Equals(vector<double>{3.0 / 5, 4.0 / 5, 0}));

	vector<double> v1{ 1,0,0 };
	vector<double> v2{ 0,1,0 };

	v = lwUtils::CrossProduct(v1, v2);
	CHECK_THAT(v, Equals(vector<double>{0, 0, 1}));

	v = lwUtils::CrossProduct(v2, v1);
	CHECK_THAT(v, Equals(vector<double>{0, 0, -1}));
}


TEST_CASE("test slice sync for lwMPRLogic", "[single-file]")
{
	shared_ptr<lwMPRLogic> viewer1 = make_shared<lwMPRLogic>();
	viewer1->SetView(lwMPRBase::AXIAL);

	shared_ptr<lwMPRLogic> viewer2 = make_shared<lwMPRLogic>();
	viewer2->SetView(lwMPRBase::SAGITTAL);

	// 同步方式待修改
	viewer1->SyncViewer(viewer2.get());
	viewer2->SyncViewer(viewer1.get());

	viewer1->UpdateSlice(22);
	CHECK(viewer2->GetZPos() == Approx(22).epsilon(1e-6));

	viewer2->UpdateSlice(11.2);
	CHECK(viewer1->GetXPos() == Approx(11.2).epsilon(1e-6));
}

TEST_CASE("test position sync for lwMPRLogic", "[single-file]")
{
	shared_ptr<lwMPRLogic> viewer1 = make_shared<lwMPRLogic>();
	viewer1->SetView(lwMPRBase::AXIAL);

	shared_ptr<lwMPRLogic> viewer2 = make_shared<lwMPRLogic>();
	viewer2->SetView(lwMPRBase::SAGITTAL);

	// 同步方式待修改
	viewer1->SyncViewer(viewer2.get());
	viewer2->SyncViewer(viewer1.get());

	viewer1->UpdatePosition(12, 21);
	CHECK(viewer2->GetXPos() == Approx(12).epsilon(1e-6));
	CHECK(viewer2->GetYPos() == Approx(21).epsilon(1e-6));

	viewer2->UpdatePosition(31, 14);
	CHECK(viewer1->GetYPos() == Approx(31).epsilon(1e-6));
	CHECK(viewer1->GetZPos() == Approx(14).epsilon(1e-6));
}

TEST_CASE("test vx/vy sync for lwMPRLogic", "[single-file]")
{
	shared_ptr<lwMPRLogic> viewer1 = make_shared<lwMPRLogic>();
	viewer1->SetView(lwMPRBase::AXIAL);

	shared_ptr<lwMPRLogic> viewer2 = make_shared<lwMPRLogic>();
	viewer2->SetView(lwMPRBase::CORONAL);

	// 同步方式待修改
	viewer1->SyncViewer(viewer2.get());

	viewer1->UpdateHoriVector(vector<double>{0, 1, 0});
	CHECK_THAT(viewer1->GetVertVector(), Equals(vector<double>{-1, 0, 0}));
	CHECK_THAT(viewer2->GetXAxis(), Equals(vector<double>{0, 1, 0}));
	CHECK_THAT(viewer2->GetYAxis(), Equals(vector<double>{-1, 0, 0}));

	viewer1->UpdateVertVector(vector<double>{0, 1, 0});
	CHECK_THAT(viewer1->GetHoriVector(), Equals(vector<double>{1, 0, 0}));
	CHECK_THAT(viewer2->GetXAxis(), Equals(vector<double>{1, 0, 0}));
	CHECK_THAT(viewer2->GetYAxis(), Equals(vector<double>{0, 1, 0}));
}
