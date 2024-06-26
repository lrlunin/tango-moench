/*----- PROTECTED REGION ID(MoenchZMQ::ClassFactory.cpp) ENABLED START -----*/
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
// project :     MoenchZMQ processor
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
#include "MoenchZMQClass.h"

//	Add class header files if needed


/**
 *	Create MoenchZMQ Class singleton and store it in DServer object.
 */

void Tango::DServer::class_factory()
{
	//	Add method class init if needed
	add_class(MoenchZMQ_ns::MoenchZMQClass::init("MoenchZMQ"));
}
/* clang-format off */
/*----- PROTECTED REGION END -----*/	//	MoenchZMQ::ClassFactory.cpp
