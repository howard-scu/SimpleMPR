#define CATCH_CONFIG_MAIN
#include <catch2\catch.hpp>

#include "lwMPRLogic2.h"

using Catch::Matchers::Equals;

TEST_CASE("TEST VIEW GET/SET", "[single-file]")
{
	shared_ptr<lwMPRLogic2> viewer = make_shared<lwMPRLogic2>();
	
	// default
	CHECK(viewer->GetView() == lwMPRLogic2::AXIAL);
	
	// set view
	viewer->SetView(lwMPRLogic2::CORONAL);
	CHECK(viewer->GetView() == lwMPRLogic2::CORONAL);

	// set view
	viewer->SetView(lwMPRLogic2::SAGITTAL);
	CHECK(viewer->GetView() == lwMPRLogic2::SAGITTAL);
}

TEST_CASE("TEST POSITION GET/SET", "[single-file]")
{
	shared_ptr<lwMPRLogic2> viewer = make_shared<lwMPRLogic2>();

	// default
	CHECK(viewer->GetXPosition() == Approx(0.0).epsilon(1e-5));
	CHECK(viewer->GetYPosition() == Approx(0.0).epsilon(1e-5));
	CHECK(viewer->GetZPosition() == Approx(0.0).epsilon(1e-5));

	// set view
	viewer->SetXPosition(5);
	CHECK(viewer->GetXPosition() == Approx(5.0).epsilon(1e-5));

	viewer->SetYPosition(-5);
	CHECK(viewer->GetYPosition() == Approx(-5.0).epsilon(1e-5));

	viewer->SetZPosition(88);
	CHECK(viewer->GetZPosition() == Approx(88.0).epsilon(1e-5));
}

TEST_CASE("TEST VX/VY SET", "[single-file]")
{
	shared_ptr<lwMPRLogic2> viewer = make_shared<lwMPRLogic2>();

	viewer->UpdateVX(vector<double>{ 0, 1, 0 });
	CHECK_THAT(viewer->GetVY(), Equals(vector<double>{-1, 0, 0}));

	viewer->UpdateVY(vector<double>{ 1, 0, 0 });
	CHECK_THAT(viewer->GetVX(), Equals(vector<double>{0, -1, 0}));
}