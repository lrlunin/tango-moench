/*----- PROTECTED REGION ID(MoenchZMQStateMachine.cpp) ENABLED START -----*/
/* clang-format on */
//=============================================================================
//
// file :        MoenchZMQStateMachine.cpp
//
// description : State machine file for the MoenchZMQ class
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

#include "MoenchZMQ.h"

/* clang-format off */
/*----- PROTECTED REGION END -----*/	//	MoenchZMQ::MoenchZMQStateMachine.cpp

//================================================================
//  States   |  Description
//================================================================
//  ON       |  
//  RUNNING  |  


namespace MoenchZMQ_ns
{
//=================================================
//		Attributes Allowed Methods
//=================================================

//--------------------------------------------------------
/**
 *	Method      : MoenchZMQ::is_file_index_allowed()
 * Description:  Execution allowed for file_index attribute
 */
//--------------------------------------------------------
bool MoenchZMQ::is_file_index_allowed(TANGO_UNUSED(Tango::AttReqType type))
{
	//	Not any excluded states for file_index attribute in Write access.
	/*----- PROTECTED REGION ID(MoenchZMQ::file_indexStateAllowed_WRITE) ENABLED START -----*/
	/* clang-format on */
	/* clang-format off */
	/*----- PROTECTED REGION END -----*/	//	MoenchZMQ::file_indexStateAllowed_WRITE

	//	Not any excluded states for file_index attribute in read access.
	/*----- PROTECTED REGION ID(MoenchZMQ::file_indexStateAllowed_READ) ENABLED START -----*/
	/* clang-format on */
	/* clang-format off */
	/*----- PROTECTED REGION END -----*/	//	MoenchZMQ::file_indexStateAllowed_READ
	return true;
}

//--------------------------------------------------------
/**
 *	Method      : MoenchZMQ::is_file_name_allowed()
 * Description:  Execution allowed for file_name attribute
 */
//--------------------------------------------------------
bool MoenchZMQ::is_file_name_allowed(TANGO_UNUSED(Tango::AttReqType type))
{
	//	Not any excluded states for file_name attribute in Write access.
	/*----- PROTECTED REGION ID(MoenchZMQ::file_nameStateAllowed_WRITE) ENABLED START -----*/
	/* clang-format on */
	/* clang-format off */
	/*----- PROTECTED REGION END -----*/	//	MoenchZMQ::file_nameStateAllowed_WRITE

	//	Not any excluded states for file_name attribute in read access.
	/*----- PROTECTED REGION ID(MoenchZMQ::file_nameStateAllowed_READ) ENABLED START -----*/
	/* clang-format on */
	/* clang-format off */
	/*----- PROTECTED REGION END -----*/	//	MoenchZMQ::file_nameStateAllowed_READ
	return true;
}

//--------------------------------------------------------
/**
 *	Method      : MoenchZMQ::is_session_directory_allowed()
 * Description:  Execution allowed for file_root_path attribute
 */
//--------------------------------------------------------
bool MoenchZMQ::is_session_directory_allowed(TANGO_UNUSED(Tango::AttReqType type))
{
	//	Not any excluded states for file_root_path attribute in Write access.
	/*----- PROTECTED REGION ID(MoenchZMQ::file_root_pathStateAllowed_WRITE) ENABLED START -----*/
	/* clang-format on */
	/* clang-format off */
	/*----- PROTECTED REGION END -----*/	//	MoenchZMQ::file_root_pathStateAllowed_WRITE

	//	Not any excluded states for file_root_path attribute in read access.
	/*----- PROTECTED REGION ID(MoenchZMQ::file_root_pathStateAllowed_READ) ENABLED START -----*/
	/* clang-format on */
	/* clang-format off */
	/*----- PROTECTED REGION END -----*/	//	MoenchZMQ::file_root_pathStateAllowed_READ
	return true;
}

//--------------------------------------------------------
/**
 *	Method      : MoenchZMQ::is_normalize_allowed()
 * Description:  Execution allowed for normalize attribute
 */
//--------------------------------------------------------
bool MoenchZMQ::is_normalize_allowed(TANGO_UNUSED(Tango::AttReqType type))
{
	//	Not any excluded states for normalize attribute in Write access.
	/*----- PROTECTED REGION ID(MoenchZMQ::normalizeStateAllowed_WRITE) ENABLED START -----*/
	/* clang-format on */
	/* clang-format off */
	/*----- PROTECTED REGION END -----*/	//	MoenchZMQ::normalizeStateAllowed_WRITE

	//	Not any excluded states for normalize attribute in read access.
	/*----- PROTECTED REGION ID(MoenchZMQ::normalizeStateAllowed_READ) ENABLED START -----*/
	/* clang-format on */
	/* clang-format off */
	/*----- PROTECTED REGION END -----*/	//	MoenchZMQ::normalizeStateAllowed_READ
	return true;
}
//--------------------------------------------------------
/**
 *	Method      : MoenchZMQ::is_update_pedestal_allowed()
 * Description:  Execution allowed for update_pedestal attribute
 */
//--------------------------------------------------------
bool MoenchZMQ::is_update_pedestal_allowed(TANGO_UNUSED(Tango::AttReqType type))
{
	//	Not any excluded states for update_pedestal attribute in Write access.
	/*----- PROTECTED REGION ID(MoenchZMQ::normalizeStateAllowed_WRITE) ENABLED START -----*/
	/* clang-format on */
	/* clang-format off */
	/*----- PROTECTED REGION END -----*/	//	MoenchZMQ::normalizeStateAllowed_WRITE

	//	Not any excluded states for normalize attribute in read access.
	/*----- PROTECTED REGION ID(MoenchZMQ::normalizeStateAllowed_READ) ENABLED START -----*/
	/* clang-format on */
	/* clang-format off */
	/*----- PROTECTED REGION END -----*/	//	MoenchZMQ::normalizeStateAllowed_READ
	return true;
}

//--------------------------------------------------------
/**
 *	Method      : MoenchZMQ::is_threshold_allowed()
 * Description:  Execution allowed for threshold attribute
 */
//--------------------------------------------------------
bool MoenchZMQ::is_threshold_allowed(TANGO_UNUSED(Tango::AttReqType type))
{

	//	Not any excluded states for threshold attribute in read access.
	/*----- PROTECTED REGION ID(MoenchZMQ::thresholdStateAllowed_READ) ENABLED START -----*/
	/* clang-format on */
	/* clang-format off */
	/*----- PROTECTED REGION END -----*/	//	MoenchZMQ::thresholdStateAllowed_READ
	return true;
}

//--------------------------------------------------------
/**
 *	Method      : MoenchZMQ::is_counting_sigma_allowed()
 * Description:  Execution allowed for counting_sigma attribute
 */
//--------------------------------------------------------
bool MoenchZMQ::is_counting_sigma_allowed(TANGO_UNUSED(Tango::AttReqType type))
{
	//	Not any excluded states for counting_sigma attribute in Write access.
	/*----- PROTECTED REGION ID(MoenchZMQ::counting_sigmaStateAllowed_WRITE) ENABLED START -----*/
	/* clang-format on */
	/* clang-format off */
	/*----- PROTECTED REGION END -----*/	//	MoenchZMQ::counting_sigmaStateAllowed_WRITE

	//	Not any excluded states for counting_sigma attribute in read access.
	/*----- PROTECTED REGION ID(MoenchZMQ::counting_sigmaStateAllowed_READ) ENABLED START -----*/
	/* clang-format on */
	/* clang-format off */
	/*----- PROTECTED REGION END -----*/	//	MoenchZMQ::counting_sigmaStateAllowed_READ
	return true;
}

//--------------------------------------------------------
/**
 *	Method      : MoenchZMQ::is_live_period_allowed()
 * Description:  Execution allowed for live_period attribute
 */
//--------------------------------------------------------
bool MoenchZMQ::is_live_period_allowed(TANGO_UNUSED(Tango::AttReqType type))
{
	//	Not any excluded states for live_period attribute in Write access.
	/*----- PROTECTED REGION ID(MoenchZMQ::live_periodStateAllowed_WRITE) ENABLED START -----*/
	/* clang-format on */
	/* clang-format off */
	/*----- PROTECTED REGION END -----*/	//	MoenchZMQ::live_periodStateAllowed_WRITE

	//	Not any excluded states for live_period attribute in read access.
	/*----- PROTECTED REGION ID(MoenchZMQ::live_periodStateAllowed_READ) ENABLED START -----*/
	/* clang-format on */
	/* clang-format off */
	/*----- PROTECTED REGION END -----*/	//	MoenchZMQ::live_periodStateAllowed_READ
	return true;
}

//--------------------------------------------------------
/**
 *	Method      : MoenchZMQ::is_process_pedestal_allowed()
 * Description:  Execution allowed for process_pedestal attribute
 */
//--------------------------------------------------------
bool MoenchZMQ::is_process_pedestal_allowed(TANGO_UNUSED(Tango::AttReqType type))
{

	//	Not any excluded states for process_pedestal attribute in read access.
	/*----- PROTECTED REGION ID(MoenchZMQ::process_pedestalStateAllowed_READ) ENABLED START -----*/
	/* clang-format on */
	/* clang-format off */
	/*----- PROTECTED REGION END -----*/	//	MoenchZMQ::process_pedestalStateAllowed_READ
	return true;
}

//--------------------------------------------------------
/**
 *	Method      : MoenchZMQ::is_split_pumped_allowed()
 * Description:  Execution allowed for split_pumped attribute
 */
//--------------------------------------------------------
bool MoenchZMQ::is_split_pumped_allowed(TANGO_UNUSED(Tango::AttReqType type))
{
	//	Not any excluded states for split_pumped attribute in Write access.
	/*----- PROTECTED REGION ID(MoenchZMQ::split_pumpedStateAllowed_WRITE) ENABLED START -----*/
	/* clang-format on */
	/* clang-format off */
	/*----- PROTECTED REGION END -----*/	//	MoenchZMQ::split_pumpedStateAllowed_WRITE

	//	Not any excluded states for split_pumped attribute in read access.
	/*----- PROTECTED REGION ID(MoenchZMQ::split_pumpedStateAllowed_READ) ENABLED START -----*/
	/* clang-format on */
	/* clang-format off */
	/*----- PROTECTED REGION END -----*/	//	MoenchZMQ::split_pumpedStateAllowed_READ
	return true;
}
//--------------------------------------------------------
/**
 *	Method      : MoenchZMQ::is_acquired_frames_allowed()
 * Description:  Execution allowed for acquired_frames attribute
 */
//--------------------------------------------------------
bool MoenchZMQ::is_acquired_frames_allowed(TANGO_UNUSED(Tango::AttReqType type))
{

	//	Not any excluded states for acquired_frames attribute in read access.
	/*----- PROTECTED REGION ID(MoenchZMQ::acquired_framesStateAllowed_READ) ENABLED START -----*/
	/* clang-format on */
	/* clang-format off */
	/*----- PROTECTED REGION END -----*/	//	MoenchZMQ::acquired_framesStateAllowed_READ
	return true;
}

//--------------------------------------------------------
/**
 *	Method      : MoenchZMQ::is_analog_img_allowed()
 * Description:  Execution allowed for analog_img attribute
 */
//--------------------------------------------------------
bool MoenchZMQ::is_analog_img_allowed(TANGO_UNUSED(Tango::AttReqType type))
{

	//	Not any excluded states for analog_img attribute in read access.
	/*----- PROTECTED REGION ID(MoenchZMQ::analog_imgStateAllowed_READ) ENABLED START -----*/
	/* clang-format on */
	/* clang-format off */
	/*----- PROTECTED REGION END -----*/	//	MoenchZMQ::analog_imgStateAllowed_READ
	return true;
}

//--------------------------------------------------------
/**
 *	Method      : MoenchZMQ::is_counting_img_allowed()
 * Description:  Execution allowed for counting_img attribute
 */
//--------------------------------------------------------
bool MoenchZMQ::is_counting_img_allowed(TANGO_UNUSED(Tango::AttReqType type))
{

	//	Not any excluded states for counting_img attribute in read access.
	/*----- PROTECTED REGION ID(MoenchZMQ::counting_imgStateAllowed_READ) ENABLED START -----*/
	/* clang-format on */
	/* clang-format off */
	/*----- PROTECTED REGION END -----*/	//	MoenchZMQ::counting_imgStateAllowed_READ
	return true;
}

//--------------------------------------------------------
/**
 *	Method      : MoenchZMQ::is_analog_img_pumped_allowed()
 * Description:  Execution allowed for analog_img_pumped attribute
 */
//--------------------------------------------------------
bool MoenchZMQ::is_analog_img_pumped_allowed(TANGO_UNUSED(Tango::AttReqType type))
{

	//	Not any excluded states for analog_img_pumped attribute in read access.
	/*----- PROTECTED REGION ID(MoenchZMQ::analog_img_pumpedStateAllowed_READ) ENABLED START -----*/
	/* clang-format on */
	/* clang-format off */
	/*----- PROTECTED REGION END -----*/	//	MoenchZMQ::analog_img_pumpedStateAllowed_READ
	return true;
}

//--------------------------------------------------------
/**
 *	Method      : MoenchZMQ::is_counting_img_pumped_allowed()
 * Description:  Execution allowed for counting_img_pumped attribute
 */
//--------------------------------------------------------
bool MoenchZMQ::is_counting_img_pumped_allowed(TANGO_UNUSED(Tango::AttReqType type))
{

	//	Not any excluded states for counting_img_pumped attribute in read access.
	/*----- PROTECTED REGION ID(MoenchZMQ::counting_img_pumpedStateAllowed_READ) ENABLED START -----*/
	/* clang-format on */
	/* clang-format off */
	/*----- PROTECTED REGION END -----*/	//	MoenchZMQ::counting_img_pumpedStateAllowed_READ
	return true;
}


//=================================================
//		Commands Allowed Methods
//=================================================

//--------------------------------------------------------
/**
 *	Method      : MoenchZMQ::is_start_receiver_allowed()
 * Description:  Execution allowed for start_receiver attribute
 */
//--------------------------------------------------------
bool MoenchZMQ::is_start_receiver_allowed(TANGO_UNUSED(const CORBA::Any &any))
{
	//	Not any excluded states for start_receiver command.
	/*----- PROTECTED REGION ID(MoenchZMQ::start_receiverStateAllowed) ENABLED START -----*/
	/* clang-format on */
	/* clang-format off */
	/*----- PROTECTED REGION END -----*/	//	MoenchZMQ::start_receiverStateAllowed
	return true;
}

//--------------------------------------------------------
/**
 *	Method      : MoenchZMQ::is_stop_receiver_allowed()
 * Description:  Execution allowed for stop_receiver attribute
 */
//--------------------------------------------------------
bool MoenchZMQ::is_stop_receiver_allowed(TANGO_UNUSED(const CORBA::Any &any))
{
	//	Not any excluded states for stop_receiver command.
	/*----- PROTECTED REGION ID(MoenchZMQ::stop_receiverStateAllowed) ENABLED START -----*/
	/* clang-format on */
	/* clang-format off */
	/*----- PROTECTED REGION END -----*/	//	MoenchZMQ::stop_receiverStateAllowed
	return true;
}

//--------------------------------------------------------
/**
 *	Method      : MoenchZMQ::is_abort_receiver_allowed()
 * Description:  Execution allowed for abort_receiver attribute
 */
//--------------------------------------------------------
bool MoenchZMQ::is_abort_receiver_allowed(TANGO_UNUSED(const CORBA::Any &any))
{
	//	Not any excluded states for abort_receiver command.
	/*----- PROTECTED REGION ID(MoenchZMQ::abort_receiverStateAllowed) ENABLED START -----*/
	/* clang-format on */
	/* clang-format off */
	/*----- PROTECTED REGION END -----*/	//	MoenchZMQ::abort_receiverStateAllowed
	return true;
}

//--------------------------------------------------------
/**
 *	Method      : MoenchZMQ::is_reset_pedestal_allowed()
 * Description:  Execution allowed for reset_pedestal attribute
 */
//--------------------------------------------------------
bool MoenchZMQ::is_reset_pedestal_allowed(TANGO_UNUSED(const CORBA::Any &any))
{
	//	Not any excluded states for reset_pedestal command.
	/*----- PROTECTED REGION ID(MoenchZMQ::reset_pedestalStateAllowed) ENABLED START -----*/
	/* clang-format on */
	/* clang-format off */
	/*----- PROTECTED REGION END -----*/	//	MoenchZMQ::reset_pedestalStateAllowed
	return true;
}

//--------------------------------------------------------
/**
 *	Method      : MoenchZMQ::is_push_images_change_allowed()
 * Description:  Execution allowed for push_images_change attribute
 */
//--------------------------------------------------------
bool MoenchZMQ::is_push_images_change_allowed(TANGO_UNUSED(const CORBA::Any &any))
{
	//	Not any excluded states for push_images_change command.
	/*----- PROTECTED REGION ID(MoenchZMQ::push_images_changeStateAllowed) ENABLED START -----*/
	/* clang-format on */
	/* clang-format off */
	/*----- PROTECTED REGION END -----*/	//	MoenchZMQ::push_images_changeStateAllowed
	return true;
}

bool MoenchZMQ::is_individual_frame_buffer_capacity_allowed(TANGO_UNUSED(Tango::AttReqType type))
{
	//	Not any excluded states for individual_frame_buffer_capacity attribute in Write access.
	/*----- PROTECTED REGION ID(MoenchZMQ::individual_frame_buffer_capacityStateAllowed_WRITE) ENABLED START -----*/
	/* clang-format on */
	/* clang-format off */
	/*----- PROTECTED REGION END -----*/	//	MoenchZMQ::individual_frame_buffer_capacityStateAllowed_WRITE

	//	Not any excluded states for individual_frame_buffer_capacity attribute in read access.
	/*----- PROTECTED REGION ID(MoenchZMQ::individual_frame_buffer_capacityStateAllowed_READ) ENABLED START -----*/
	/* clang-format on */
	/* clang-format off */
	/*----- PROTECTED REGION END -----*/	//	MoenchZMQ::individual_frame_buffer_capacityStateAllowed_READ
	return true;
}
/*----- PROTECTED REGION ID(MoenchZMQ::MoenchZMQStateAllowed.AdditionalMethods) ENABLED START -----*/
/* clang-format on */
//	Additional Methods
/* clang-format off */
/*----- PROTECTED REGION END -----*/	//	MoenchZMQ::MoenchZMQStateAllowed.AdditionalMethods

}	//	End of namespace