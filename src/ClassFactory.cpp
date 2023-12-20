/*----- PROTECTED REGION ID(TestDeviceLunin::ClassFactory.cpp) ENABLED START -----*/
/* clang-format on */
//=============================================================================
//
// file :        ClassFactory.cpp
//
// description : C++ source for the class_factory method of the DServer
//               device class. This method is responsible for the creation of
//               all class singleton for a device server. It is called
//               at device server startup.
//
// project :     Lunin title
//
// This file is part of Tango device class.
//
// Tango is free software: you can redistribute it and/or modify
// it under the terms of the MIT licence.
//
//
//
//=============================================================================
//                This file is generated by POGO
//        (Program Obviously used to Generate tango Object)
//=============================================================================

#include <tango/tango.h>
#include "TestDeviceLuninClass.h"

//	Add class header files if needed


/**
 *	Create TestDeviceLunin Class singleton and store it in DServer object.
 */

void Tango::DServer::class_factory()
{
	//	Add method class init if needed
	add_class(TestDeviceLunin_ns::TestDeviceLuninClass::init("TestDeviceLunin"));
}
/* clang-format off */
/*----- PROTECTED REGION END -----*/	//	TestDeviceLunin::ClassFactory.cpp