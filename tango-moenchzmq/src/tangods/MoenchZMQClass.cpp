/*----- PROTECTED REGION ID(MoenchZMQClass.cpp) ENABLED START -----*/
/* clang-format on */
//=============================================================================
//
// file :        MoenchZMQClass.cpp
//
// description : C++ source for the MoenchZMQClass.
//               A singleton class derived from DeviceClass.
//               It implements the command and attribute list
//               and all properties and methods required
//               by the MoenchZMQ once per process.
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


#include "MoenchZMQClass.h"
/* clang-format off */
/*----- PROTECTED REGION END -----*/	//	MoenchZMQClass.cpp

//-------------------------------------------------------------------
/**
 *	Create MoenchZMQClass singleton and
 *	return it in a C function for Python usage
 */
//-------------------------------------------------------------------
extern "C" {
#ifdef _TG_WINDOWS_

__declspec(dllexport)

#endif

	Tango::DeviceClass *_create_MoenchZMQ_class(const char *name) {
		return MoenchZMQ_ns::MoenchZMQClass::init(name);
	}
}

namespace MoenchZMQ_ns
{
//===================================================================
//	Initialize pointer for singleton pattern
//===================================================================
MoenchZMQClass *MoenchZMQClass::_instance = NULL;

//===================================================================
//	Class constants
//===================================================================
constexpr long analog_imgAttrib::X_DATA_SIZE;
constexpr long analog_imgAttrib::Y_DATA_SIZE;
constexpr long counting_imgAttrib::X_DATA_SIZE;
constexpr long counting_imgAttrib::Y_DATA_SIZE;
constexpr long analog_img_pumpedAttrib::X_DATA_SIZE;
constexpr long analog_img_pumpedAttrib::Y_DATA_SIZE;
constexpr long counting_img_pumpedAttrib::X_DATA_SIZE;
constexpr long counting_img_pumpedAttrib::Y_DATA_SIZE;
//--------------------------------------------------------
/**
 * method : 		MoenchZMQClass::MoenchZMQClass(std::string &s)
 * description : 	constructor for the MoenchZMQClass
 *
 * @param s	The class name
 */
//--------------------------------------------------------
MoenchZMQClass::MoenchZMQClass(std::string &s):Tango::DeviceClass(s)
{
	TANGO_LOG_INFO << "Entering MoenchZMQClass constructor" << std::endl;
	set_default_property();
	write_class_property();

	/*----- PROTECTED REGION ID(MoenchZMQClass::constructor) ENABLED START -----*/
	/* clang-format on */
	/* clang-format off */
	/*----- PROTECTED REGION END -----*/	//	MoenchZMQClass::constructor

	TANGO_LOG_INFO << "Leaving MoenchZMQClass constructor" << std::endl;
}

//--------------------------------------------------------
/**
 * method : 		MoenchZMQClass::~MoenchZMQClass()
 * description : 	destructor for the MoenchZMQClass
 */
//--------------------------------------------------------
MoenchZMQClass::~MoenchZMQClass()
{
	/*----- PROTECTED REGION ID(MoenchZMQClass::destructor) ENABLED START -----*/
	/* clang-format on */
	/* clang-format off */
	/*----- PROTECTED REGION END -----*/	//	MoenchZMQClass::destructor

	_instance = NULL;
}


//--------------------------------------------------------
/**
 * method : 		MoenchZMQClass::init
 * description : 	Create the object if not already done.
 *                  Otherwise, just return a pointer to the object
 *
 * @param	name	The class name
 */
//--------------------------------------------------------
MoenchZMQClass *MoenchZMQClass::init(const char *name)
{
	if (_instance == NULL)
	{
		try
		{
			std::string s(name);
			_instance = new MoenchZMQClass(s);
		}
		catch (std::bad_alloc &)
		{
			throw;
		}
	}
	return _instance;
}

//--------------------------------------------------------
/**
 * method : 		MoenchZMQClass::instance
 * description : 	Check if object already created,
 *                  and return a pointer to the object
 */
//--------------------------------------------------------
MoenchZMQClass *MoenchZMQClass::instance()
{
	if (_instance == NULL)
	{
		std::cerr << "Class is not initialised !!" << std::endl;
		exit(-1);
	}
	return _instance;
}



//===================================================================
//	Command execution method calls
//===================================================================
//--------------------------------------------------------
/**
 * method : 		start_receiverClass::execute()
 * description : 	method to trigger the execution of the command.
 *
 * @param	device	The device on which the command must be executed
 * @param	in_any	The command input data
 *
 *	returns The command output data (packed in the Any object)
 */
//--------------------------------------------------------
CORBA::Any *start_receiverClass::execute(Tango::DeviceImpl *device, TANGO_UNUSED(const CORBA::Any &in_any))
{
	TANGO_LOG_INFO << "start_receiverClass::execute(): arrived" << std::endl;
	((static_cast<MoenchZMQ *>(device))->start_receiver());
	return new CORBA::Any();
}

//--------------------------------------------------------
/**
 * method : 		stop_receiverClass::execute()
 * description : 	method to trigger the execution of the command.
 *
 * @param	device	The device on which the command must be executed
 * @param	in_any	The command input data
 *
 *	returns The command output data (packed in the Any object)
 */
//--------------------------------------------------------
CORBA::Any *stop_receiverClass::execute(Tango::DeviceImpl *device, TANGO_UNUSED(const CORBA::Any &in_any))
{
	TANGO_LOG_INFO << "stop_receiverClass::execute(): arrived" << std::endl;
	((static_cast<MoenchZMQ *>(device))->stop_receiver());
	return new CORBA::Any();
}

//--------------------------------------------------------
/**
 * method : 		abort_receiverClass::execute()
 * description : 	method to trigger the execution of the command.
 *
 * @param	device	The device on which the command must be executed
 * @param	in_any	The command input data
 *
 *	returns The command output data (packed in the Any object)
 */
//--------------------------------------------------------
CORBA::Any *abort_receiverClass::execute(Tango::DeviceImpl *device, TANGO_UNUSED(const CORBA::Any &in_any))
{
	TANGO_LOG_INFO << "abort_receiverClass::execute(): arrived" << std::endl;
	((static_cast<MoenchZMQ *>(device))->abort_receiver());
	return new CORBA::Any();
}

//--------------------------------------------------------
/**
 * method : 		reset_pedestalClass::execute()
 * description : 	method to trigger the execution of the command.
 *
 * @param	device	The device on which the command must be executed
 * @param	in_any	The command input data
 *
 *	returns The command output data (packed in the Any object)
 */
//--------------------------------------------------------
CORBA::Any *reset_pedestalClass::execute(Tango::DeviceImpl *device, TANGO_UNUSED(const CORBA::Any &in_any))
{
	TANGO_LOG_INFO << "reset_pedestalClass::execute(): arrived" << std::endl;
	((static_cast<MoenchZMQ *>(device))->reset_pedestal());
	return new CORBA::Any();
}
//--------------------------------------------------------
/**
 * method : 		push_images_changeClass::execute()
 * description : 	method to trigger the execution of the command.
 *
 * @param	device	The device on which the command must be executed
 * @param	in_any	The command input data
 *
 *	returns The command output data (packed in the Any object)
 */
//--------------------------------------------------------
CORBA::Any *push_images_changeClass::execute(Tango::DeviceImpl *device, TANGO_UNUSED(const CORBA::Any &in_any))
{
	TANGO_LOG_INFO << "push_images_changeClass::execute(): arrived" << std::endl;
	((static_cast<MoenchZMQ *>(device))->push_images_change());
	return new CORBA::Any();
}


//===================================================================
//	Properties management
//===================================================================
//--------------------------------------------------------
/**
 *	Method      : MoenchZMQClass::get_class_property()
 * Description:  Get the class property for specified name.
 */
//--------------------------------------------------------
Tango::DbDatum MoenchZMQClass::get_class_property(std::string &prop_name)
{
	for (unsigned int i=0 ; i<cl_prop.size() ; i++)
		if (cl_prop[i].name == prop_name)
			return cl_prop[i];
	//	if not found, returns  an empty DbDatum
	return Tango::DbDatum(prop_name);
}

//--------------------------------------------------------
/**
 *	Method      : MoenchZMQClass::get_default_device_property()
 * Description:  Return the default value for device property.
 */
//--------------------------------------------------------
Tango::DbDatum MoenchZMQClass::get_default_device_property(std::string &prop_name)
{
	for (unsigned int i=0 ; i<dev_def_prop.size() ; i++)
		if (dev_def_prop[i].name == prop_name)
			return dev_def_prop[i];
	//	if not found, return  an empty DbDatum
	return Tango::DbDatum(prop_name);
}

//--------------------------------------------------------
/**
 *	Method      : MoenchZMQClass::get_default_class_property()
 * Description:  Return the default value for class property.
 */
//--------------------------------------------------------
Tango::DbDatum MoenchZMQClass::get_default_class_property(std::string &prop_name)
{
	for (unsigned int i=0 ; i<cl_def_prop.size() ; i++)
		if (cl_def_prop[i].name == prop_name)
			return cl_def_prop[i];
	//	if not found, return  an empty DbDatum
	return Tango::DbDatum(prop_name);
}


//--------------------------------------------------------
/**
 *	Method      : MoenchZMQClass::set_default_property()
 * Description:  Set default property (class and device) for wizard.
 *                For each property, add to wizard property name and description.
 *                If default value has been set, add it to wizard property and
 *                store it in a DbDatum.
 */
//--------------------------------------------------------
void MoenchZMQClass::set_default_property()
{
	std::string	prop_name;
	std::string	prop_desc;
	std::string	prop_def;
	std::vector<std::string>	vect_data;

	//	Set Default Class Properties

	//	Set Default device Properties
	prop_name = "ZMQ_RX_IP";
	prop_desc = "";
	prop_def  = "";
	vect_data.clear();
	if (prop_def.length()>0)
	{
		Tango::DbDatum	data(prop_name);
		data << vect_data ;
		dev_def_prop.push_back(data);
		add_wiz_dev_prop(prop_name, prop_desc,  prop_def);
	}
	else
		add_wiz_dev_prop(prop_name, prop_desc);
	prop_name = "ZMQ_RX_PORT";
	prop_desc = "";
	prop_def  = "";
	vect_data.clear();
	if (prop_def.length()>0)
	{
		Tango::DbDatum	data(prop_name);
		data << vect_data ;
		dev_def_prop.push_back(data);
		add_wiz_dev_prop(prop_name, prop_desc,  prop_def);
	}
	else
		add_wiz_dev_prop(prop_name, prop_desc);
}

//--------------------------------------------------------
/**
 *	Method      : MoenchZMQClass::write_class_property()
 * Description:  Set class description fields as property in database
 */
//--------------------------------------------------------
void MoenchZMQClass::write_class_property()
{
//	First time, check if database used
if (Tango::Util::_UseDb == false)
	return;

Tango::DbData	data;
std::string	classname = get_name();
std::string	header;

//	Put title
Tango::DbDatum	title("ProjectTitle");
std::string	str_title("MoenchZMQ processor");
title << str_title;
data.push_back(title);

//	Put Description
Tango::DbDatum	description("Description");
std::vector<std::string>	str_desc;
str_desc.push_back("");
description << str_desc;
data.push_back(description);

//  Put inheritance
Tango::DbDatum	inher_datum("InheritedFrom");
std::vector<std::string> inheritance;
inheritance.push_back("TANGO_BASE_CLASS");
inher_datum << inheritance;
data.push_back(inher_datum);

//	Call database and and values
get_db_class()->put_property(data);
}

//===================================================================
//	Factory methods
//===================================================================

//--------------------------------------------------------
/**
 *	Method      : MoenchZMQClass::device_factory()
 * Description:  Create the device object(s)
 *                and store them in the device list
 */
//--------------------------------------------------------
void MoenchZMQClass::device_factory(const Tango::DevVarStringArray *devlist_ptr)
{
/*----- PROTECTED REGION ID(MoenchZMQClass::device_factory_before) ENABLED START -----*/
/* clang-format on */
//	Add your own code
/* clang-format off */
/*----- PROTECTED REGION END -----*/	//	MoenchZMQClass::device_factory_before

//	Create devices and add it into the device list
for (unsigned long i=0 ; i<devlist_ptr->length() ; i++)
{
	TANGO_LOG_DEBUG << "Device name : " << (*devlist_ptr)[i].in() << std::endl;
	device_list.push_back(new MoenchZMQ(this, (*devlist_ptr)[i]));
}

//	Manage dynamic attributes if any
erase_dynamic_attributes(devlist_ptr, get_class_attr()->get_attr_list());

//	Export devices to the outside world
for (unsigned long i=1 ; i<=devlist_ptr->length() ; i++)
{
	//	Add dynamic attributes if any
	MoenchZMQ *dev = static_cast<MoenchZMQ *>(device_list[device_list.size()-i]);
	dev->add_dynamic_attributes();

	//	Check before if database used.
	if ((Tango::Util::_UseDb == true) && (Tango::Util::_FileDb == false))
		export_device(dev);
	else
		export_device(dev, dev->get_name().c_str());
}

/*----- PROTECTED REGION ID(MoenchZMQClass::device_factory_after) ENABLED START -----*/
/* clang-format on */
//	Add your own code
/* clang-format off */
/*----- PROTECTED REGION END -----*/	//	MoenchZMQClass::device_factory_after
}
//--------------------------------------------------------
/**
 *	Method      : MoenchZMQClass::attribute_factory()
 * Description:  Create the attribute object(s)
 *                and store them in the attribute list
 */
//--------------------------------------------------------
void MoenchZMQClass::attribute_factory(std::vector<Tango::Attr *> &att_list)
{
	/*----- PROTECTED REGION ID(MoenchZMQClass::attribute_factory_before) ENABLED START -----*/
	/* clang-format on */
	//	Add your own code
	/* clang-format off */
	/*----- PROTECTED REGION END -----*/	//	MoenchZMQClass::attribute_factory_before
	//	Attribute : file_index
	file_indexAttrib	*file_index = new file_indexAttrib();
	Tango::UserDefaultAttrProp	file_index_prop;
	//	description	not set for file_index
	//	label	not set for file_index
	//	unit	not set for file_index
	//	standard_unit	not set for file_index
	//	display_unit	not set for file_index
	//	format	not set for file_index
	//	max_value	not set for file_index
	//	min_value	not set for file_index
	//	max_alarm	not set for file_index
	//	min_alarm	not set for file_index
	//	max_warning	not set for file_index
	//	min_warning	not set for file_index
	//	delta_t	not set for file_index
	//	delta_val	not set for file_index
	file_index->set_default_properties(file_index_prop);
	//	Not Polled
	file_index->set_disp_level(Tango::OPERATOR);
	//	Not Memorized
	att_list.push_back(file_index);

	//	Attribute : file_name
	file_nameAttrib	*file_name = new file_nameAttrib();
	Tango::UserDefaultAttrProp	file_name_prop;
	//	description	not set for file_name
	//	label	not set for file_name
	//	unit	not set for file_name
	//	standard_unit	not set for file_name
	//	display_unit	not set for file_name
	//	format	not set for file_name
	//	max_value	not set for file_name
	//	min_value	not set for file_name
	//	max_alarm	not set for file_name
	//	min_alarm	not set for file_name
	//	max_warning	not set for file_name
	//	min_warning	not set for file_name
	//	delta_t	not set for file_name
	//	delta_val	not set for file_name
	file_name->set_default_properties(file_name_prop);
	//	Not Polled
	file_name->set_disp_level(Tango::OPERATOR);
	//	Not Memorized
	att_list.push_back(file_name);

	//	Attribute : file_root_path
	file_session_directoryAttrib	*file_root_path = new file_session_directoryAttrib();
	Tango::UserDefaultAttrProp	file_root_path_prop;
	//	description	not set for file_root_path
	//	label	not set for file_root_path
	//	unit	not set for file_root_path
	//	standard_unit	not set for file_root_path
	//	display_unit	not set for file_root_path
	//	format	not set for file_root_path
	//	max_value	not set for file_root_path
	//	min_value	not set for file_root_path
	//	max_alarm	not set for file_root_path
	//	min_alarm	not set for file_root_path
	//	max_warning	not set for file_root_path
	//	min_warning	not set for file_root_path
	//	delta_t	not set for file_root_path
	//	delta_val	not set for file_root_path
	file_root_path->set_default_properties(file_root_path_prop);
	//	Not Polled
	file_root_path->set_disp_level(Tango::OPERATOR);
	file_root_path->set_memorized();
	file_root_path->set_memorized_init(true);
	att_list.push_back(file_root_path);

	//	Attribute : normalize
	normalizeAttrib	*normalize = new normalizeAttrib();
	Tango::UserDefaultAttrProp	normalize_prop;
	//	description	not set for normalize
	//	label	not set for normalize
	//	unit	not set for normalize
	//	standard_unit	not set for normalize
	//	display_unit	not set for normalize
	//	format	not set for normalize
	//	max_value	not set for normalize
	//	min_value	not set for normalize
	//	max_alarm	not set for normalize
	//	min_alarm	not set for normalize
	//	max_warning	not set for normalize
	//	min_warning	not set for normalize
	//	delta_t	not set for normalize
	//	delta_val	not set for normalize
	normalize->set_default_properties(normalize_prop);
	//	Not Polled
	normalize->set_disp_level(Tango::OPERATOR);
	//	Not Memorized
	att_list.push_back(normalize);

	//	Attribute : normalize
	updatePedestalPeriodAttrib	*updatePedestalPeriod = new updatePedestalPeriodAttrib();
	Tango::UserDefaultAttrProp	updatePedestalPeriod_prop;
	updatePedestalPeriod_prop.set_description("if 0 - not updated, otherwise updated every N frames");
	updatePedestalPeriod_prop.set_label("update pedestal period");
	updatePedestalPeriod_prop.set_unit("frames");
	//	format	not set for normalize
	//	max_value	not set for normalize
	//	min_value	not set for normalize
	//	max_alarm	not set for normalize
	//	min_alarm	not set for normalize
	//	max_warning	not set for normalize
	//	min_warning	not set for normalize
	//	delta_t	not set for normalize
	//	delta_val	not set for normalize
	updatePedestalPeriod->set_default_properties(updatePedestalPeriod_prop);
	//	Not Polled
	updatePedestalPeriod->set_disp_level(Tango::OPERATOR);
	//	Not Memorized
	att_list.push_back(updatePedestalPeriod);

	//	Attribute : threshold
	thresholdAttrib	*threshold = new thresholdAttrib();
	Tango::UserDefaultAttrProp	threshold_prop;
	//	description	not set for threshold
	threshold_prop.set_label("threshold");
	threshold_prop.set_unit("ADU");
	//	standard_unit	not set for threshold
	//	display_unit	not set for threshold
	//	format	not set for threshold
	//	max_value	not set for threshold
	//	min_value	not set for threshold
	//	max_alarm	not set for threshold
	//	min_alarm	not set for threshold
	//	max_warning	not set for threshold
	//	min_warning	not set for threshold
	//	delta_t	not set for threshold
	//	delta_val	not set for threshold
	threshold->set_default_properties(threshold_prop);
	//	Not Polled
	threshold->set_disp_level(Tango::OPERATOR);
	threshold->set_memorized();
	threshold->set_memorized_init(true);
	att_list.push_back(threshold);

	//	Attribute : counting_sigma
	counting_sigmaAttrib	*counting_sigma = new counting_sigmaAttrib();
	Tango::UserDefaultAttrProp	counting_sigma_prop;
	//	description	not set for counting_sigma
	//	label	not set for counting_sigma
	//	unit	not set for counting_sigma
	//	standard_unit	not set for counting_sigma
	//	display_unit	not set for counting_sigma
	//	format	not set for counting_sigma
	//	max_value	not set for counting_sigma
	//	min_value	not set for counting_sigma
	//	max_alarm	not set for counting_sigma
	//	min_alarm	not set for counting_sigma
	//	max_warning	not set for counting_sigma
	//	min_warning	not set for counting_sigma
	//	delta_t	not set for counting_sigma
	//	delta_val	not set for counting_sigma
	counting_sigma->set_default_properties(counting_sigma_prop);
	//	Not Polled
	counting_sigma->set_disp_level(Tango::OPERATOR);
	counting_sigma->set_memorized();
	counting_sigma->set_memorized_init(true);
	att_list.push_back(counting_sigma);

	//	Attribute : live_period
	live_periodAttrib	*live_period = new live_periodAttrib();
	Tango::UserDefaultAttrProp	live_period_prop;
	//	description	not set for live_period
	live_period_prop.set_label("live period");
	live_period_prop.set_unit("frames");
	//	standard_unit	not set for live_period
	//	display_unit	not set for live_period
	//	format	not set for live_period
	//	max_value	not set for live_period
	//	min_value	not set for live_period
	//	max_alarm	not set for live_period
	//	min_alarm	not set for live_period
	//	max_warning	not set for live_period
	//	min_warning	not set for live_period
	//	delta_t	not set for live_period
	//	delta_val	not set for live_period
	live_period->set_default_properties(live_period_prop);
	//	Not Polled
	live_period->set_disp_level(Tango::OPERATOR);
	//	Not Memorized
	att_list.push_back(live_period);

	//	Attribute : process_pedestal
	process_pedestalAttrib	*process_pedestal = new process_pedestalAttrib();
	Tango::UserDefaultAttrProp	process_pedestal_prop;
	//	description	not set for process_pedestal
	//	label	not set for process_pedestal
	//	unit	not set for process_pedestal
	//	standard_unit	not set for process_pedestal
	//	display_unit	not set for process_pedestal
	//	format	not set for process_pedestal
	//	max_value	not set for process_pedestal
	//	min_value	not set for process_pedestal
	//	max_alarm	not set for process_pedestal
	//	min_alarm	not set for process_pedestal
	//	max_warning	not set for process_pedestal
	//	min_warning	not set for process_pedestal
	//	delta_t	not set for process_pedestal
	//	delta_val	not set for process_pedestal
	process_pedestal->set_default_properties(process_pedestal_prop);
	//	Not Polled
	process_pedestal->set_disp_level(Tango::OPERATOR);
	//	Not Memorized
	att_list.push_back(process_pedestal);

	//	Attribute : split_pumped
	split_pumpedAttrib	*split_pumped = new split_pumpedAttrib();
	Tango::UserDefaultAttrProp	split_pumped_prop;
	//	description	not set for split_pumped
	//	label	not set for split_pumped
	//	unit	not set for split_pumped
	//	standard_unit	not set for split_pumped
	//	display_unit	not set for split_pumped
	//	format	not set for split_pumped
	//	max_value	not set for split_pumped
	//	min_value	not set for split_pumped
	//	max_alarm	not set for split_pumped
	//	min_alarm	not set for split_pumped
	//	max_warning	not set for split_pumped
	//	min_warning	not set for split_pumped
	//	delta_t	not set for split_pumped
	//	delta_val	not set for split_pumped
	split_pumped->set_default_properties(split_pumped_prop);
	//	Not Polled
	split_pumped->set_disp_level(Tango::OPERATOR);
	split_pumped->set_memorized();
	split_pumped->set_memorized_init(true);
	att_list.push_back(split_pumped);

	//	Attribute : individual_frame_buffer_capacity
	individual_frame_buffer_capacityAttrib	*individual_frame_buffer_capacity = new individual_frame_buffer_capacityAttrib();
	Tango::UserDefaultAttrProp	individual_frame_buffer_capacity_prop;
	//	description	not set for individual_frame_buffer_capacity
	individual_frame_buffer_capacity_prop.set_label("individual frame buffer capacity");
	//	unit	not set for individual_frame_buffer_capacity
	//	standard_unit	not set for individual_frame_buffer_capacity
	//	display_unit	not set for individual_frame_buffer_capacity
	//	format	not set for individual_frame_buffer_capacity
	//	max_value	not set for individual_frame_buffer_capacity
	individual_frame_buffer_capacity_prop.set_min_value("1");
	//	max_alarm	not set for individual_frame_buffer_capacity
	//	min_alarm	not set for individual_frame_buffer_capacity
	//	max_warning	not set for individual_frame_buffer_capacity
	//	min_warning	not set for individual_frame_buffer_capacity
	//	delta_t	not set for individual_frame_buffer_capacity
	//	delta_val	not set for individual_frame_buffer_capacity
	individual_frame_buffer_capacity->set_default_properties(individual_frame_buffer_capacity_prop);
	//	Not Polled
	individual_frame_buffer_capacity->set_disp_level(Tango::OPERATOR);
	//	Not Memorized
	att_list.push_back(individual_frame_buffer_capacity);

	//	Attribute : acquired_frames
	acquired_framesAttrib	*acquired_frames = new acquired_framesAttrib();
	Tango::UserDefaultAttrProp	acquired_frames_prop;
	//	description	not set for acquired_frames
	//	label	not set for acquired_frames
	//	unit	not set for acquired_frames
	//	standard_unit	not set for acquired_frames
	//	display_unit	not set for acquired_frames
	//	format	not set for acquired_frames
	//	max_value	not set for acquired_frames
	//	min_value	not set for acquired_frames
	//	max_alarm	not set for acquired_frames
	//	min_alarm	not set for acquired_frames
	//	max_warning	not set for acquired_frames
	//	min_warning	not set for acquired_frames
	//	delta_t	not set for acquired_frames
	//	delta_val	not set for acquired_frames
	acquired_frames->set_default_properties(acquired_frames_prop);
	//	Not Polled
	acquired_frames->set_disp_level(Tango::OPERATOR);
	//	Not Memorized
	att_list.push_back(acquired_frames);

	//	Attribute : analog_img
	analog_imgAttrib	*analog_img = new analog_imgAttrib();
	Tango::UserDefaultAttrProp	analog_img_prop;
	//	description	not set for analog_img
	//	label	not set for analog_img
	//	unit	not set for analog_img
	//	standard_unit	not set for analog_img
	//	display_unit	not set for analog_img
	//	format	not set for analog_img
	//	max_value	not set for analog_img
	//	min_value	not set for analog_img
	//	max_alarm	not set for analog_img
	//	min_alarm	not set for analog_img
	//	max_warning	not set for analog_img
	//	min_warning	not set for analog_img
	//	delta_t	not set for analog_img
	//	delta_val	not set for analog_img
	analog_img->set_default_properties(analog_img_prop);
	//	Not Polled
	analog_img->set_disp_level(Tango::OPERATOR);
	analog_img->set_change_event(true, false);
	//	Not Memorized
	att_list.push_back(analog_img);

	//	Attribute : counting_img
	counting_imgAttrib	*counting_img = new counting_imgAttrib();
	Tango::UserDefaultAttrProp	counting_img_prop;
	//	description	not set for counting_img
	//	label	not set for counting_img
	//	unit	not set for counting_img
	//	standard_unit	not set for counting_img
	//	display_unit	not set for counting_img
	//	format	not set for counting_img
	//	max_value	not set for counting_img
	//	min_value	not set for counting_img
	//	max_alarm	not set for counting_img
	//	min_alarm	not set for counting_img
	//	max_warning	not set for counting_img
	//	min_warning	not set for counting_img
	//	delta_t	not set for counting_img
	//	delta_val	not set for counting_img
	counting_img->set_default_properties(counting_img_prop);
	//	Not Polled
	counting_img->set_disp_level(Tango::OPERATOR);
	//	Not Memorized
	counting_img->set_change_event(true, false);
	att_list.push_back(counting_img);

//	Attribute : analog_img_pumped
	analog_img_pumpedAttrib	*analog_img_pumped = new analog_img_pumpedAttrib();
	Tango::UserDefaultAttrProp	analog_img_pumped_prop;
	//	description	not set for analog_img_pumped
	//	label	not set for analog_img_pumped
	//	unit	not set for analog_img_pumped
	//	standard_unit	not set for analog_img_pumped
	//	display_unit	not set for analog_img_pumped
	//	format	not set for analog_img_pumped
	//	max_value	not set for analog_img_pumped
	//	min_value	not set for analog_img_pumped
	//	max_alarm	not set for analog_img_pumped
	//	min_alarm	not set for analog_img_pumped
	//	max_warning	not set for analog_img_pumped
	//	min_warning	not set for analog_img_pumped
	//	delta_t	not set for analog_img_pumped
	//	delta_val	not set for analog_img_pumped
	analog_img_pumped->set_default_properties(analog_img_pumped_prop);
	//	Not Polled
	analog_img_pumped->set_disp_level(Tango::OPERATOR);
	//	Not Memorized
	analog_img_pumped->set_change_event(true, false);
	att_list.push_back(analog_img_pumped);

	//	Attribute : counting_img_pumped
	counting_img_pumpedAttrib	*counting_img_pumped = new counting_img_pumpedAttrib();
	Tango::UserDefaultAttrProp	counting_img_pumped_prop;
	//	description	not set for counting_img_pumped
	//	label	not set for counting_img_pumped
	//	unit	not set for counting_img_pumped
	//	standard_unit	not set for counting_img_pumped
	//	display_unit	not set for counting_img_pumped
	//	format	not set for counting_img_pumped
	//	max_value	not set for counting_img_pumped
	//	min_value	not set for counting_img_pumped
	//	max_alarm	not set for counting_img_pumped
	//	min_alarm	not set for counting_img_pumped
	//	max_warning	not set for counting_img_pumped
	//	min_warning	not set for counting_img_pumped
	//	delta_t	not set for counting_img_pumped
	//	delta_val	not set for counting_img_pumped
	counting_img_pumped->set_default_properties(counting_img_pumped_prop);
	//	Not Polled
	counting_img_pumped->set_disp_level(Tango::OPERATOR);
	//	Not Memorized
	counting_img_pumped->set_change_event(true, false);
	att_list.push_back(counting_img_pumped);

	//	Create a list of static attributes
	create_static_attribute_list(get_class_attr()->get_attr_list());
	/*----- PROTECTED REGION ID(MoenchZMQClass::attribute_factory_after) ENABLED START -----*/
	/* clang-format on */
	//	Add your own code
	/* clang-format off */
	/*----- PROTECTED REGION END -----*/	//	MoenchZMQClass::attribute_factory_after
}
//--------------------------------------------------------
/**
 *	Method      : MoenchZMQClass::pipe_factory()
 * Description:  Create the pipe object(s)
 *                and store them in the pipe list
 */
//--------------------------------------------------------
void MoenchZMQClass::pipe_factory()
{
	/*----- PROTECTED REGION ID(MoenchZMQClass::pipe_factory_before) ENABLED START -----*/
	/* clang-format on */
	//	Add your own code
	/* clang-format off */
	/*----- PROTECTED REGION END -----*/	//	MoenchZMQClass::pipe_factory_before
	/*----- PROTECTED REGION ID(MoenchZMQClass::pipe_factory_after) ENABLED START -----*/
	/* clang-format on */
	//	Add your own code
	/* clang-format off */
	/*----- PROTECTED REGION END -----*/	//	MoenchZMQClass::pipe_factory_after
}
//--------------------------------------------------------
/**
 *	Method      : MoenchZMQClass::command_factory()
 * Description:  Create the command object(s)
 *                and store them in the command list
 */
//--------------------------------------------------------
void MoenchZMQClass::command_factory()
{
	/*----- PROTECTED REGION ID(MoenchZMQClass::command_factory_before) ENABLED START -----*/
	/* clang-format on */
	//	Add your own code
	/* clang-format off */
	/*----- PROTECTED REGION END -----*/	//	MoenchZMQClass::command_factory_before


	//	Command start_receiver
	start_receiverClass	*pstart_receiverCmd =
		new start_receiverClass("start_receiver",
			Tango::DEV_VOID, Tango::DEV_VOID,
			"",
			"",
			Tango::OPERATOR);
	command_list.push_back(pstart_receiverCmd);

	//	Command stop_receiver
	stop_receiverClass	*pstop_receiverCmd =
		new stop_receiverClass("stop_receiver",
			Tango::DEV_VOID, Tango::DEV_VOID,
			"",
			"",
			Tango::OPERATOR);
	command_list.push_back(pstop_receiverCmd);

	//	Command abort_receiver
	abort_receiverClass	*pabort_receiverCmd =
		new abort_receiverClass("abort_receiver",
			Tango::DEV_VOID, Tango::DEV_VOID,
			"",
			"",
			Tango::OPERATOR);
	command_list.push_back(pabort_receiverCmd);

	//	Command reset_pedestal
	reset_pedestalClass	*preset_pedestalCmd =
		new reset_pedestalClass("reset_pedestal",
			Tango::DEV_VOID, Tango::DEV_VOID,
			"",
			"",
			Tango::OPERATOR);
	command_list.push_back(preset_pedestalCmd);

	//	Command push_images_change
	push_images_changeClass	*ppush_images_changeCmd =
		new push_images_changeClass("push_images_change",
			Tango::DEV_VOID, Tango::DEV_VOID,
			"",
			"",
			Tango::EXPERT);
	command_list.push_back(ppush_images_changeCmd);

	/*----- PROTECTED REGION ID(MoenchZMQClass::command_factory_after) ENABLED START -----*/
	/* clang-format on */
	//	Add your own code
	/* clang-format off */
	/*----- PROTECTED REGION END -----*/	//	MoenchZMQClass::command_factory_after
}

//===================================================================
//	Dynamic attributes related methods
//===================================================================

//--------------------------------------------------------
/**
 * method : 		MoenchZMQClass::create_static_attribute_list
 * description : 	Create the a list of static attributes
 *
 * @param	att_list	the created attribute list
 */
//--------------------------------------------------------
void MoenchZMQClass::create_static_attribute_list(std::vector<Tango::Attr *> &att_list)
{
	for (unsigned long i=0 ; i<att_list.size() ; i++)
	{
		std::string att_name(att_list[i]->get_name());
		transform(att_name.begin(), att_name.end(), att_name.begin(), ::tolower);
		defaultAttList.push_back(att_name);
	}

	TANGO_LOG_INFO << defaultAttList.size() << " attributes in default list" << std::endl;

	/*----- PROTECTED REGION ID(MoenchZMQClass::create_static_att_list) ENABLED START -----*/
	/* clang-format on */
	/* clang-format off */
	/*----- PROTECTED REGION END -----*/	//	MoenchZMQClass::create_static_att_list
}


//--------------------------------------------------------
/**
 * method : 		MoenchZMQClass::erase_dynamic_attributes
 * description : 	delete the dynamic attributes if any.
 *
 * @param	devlist_ptr	the device list pointer
 * @param	list of all attributes
 */
//--------------------------------------------------------
void MoenchZMQClass::erase_dynamic_attributes(const Tango::DevVarStringArray *devlist_ptr, std::vector<Tango::Attr *> &att_list)
{
	Tango::Util *tg = Tango::Util::instance();

	for (unsigned long i=0 ; i<devlist_ptr->length() ; i++)
	{
		Tango::DeviceImpl *dev_impl = tg->get_device_by_name(((std::string)(*devlist_ptr)[i]).c_str());
		MoenchZMQ *dev = static_cast<MoenchZMQ *> (dev_impl);

		std::vector<Tango::Attribute *> &dev_att_list = dev->get_device_attr()->get_attribute_list();
		std::vector<Tango::Attribute *>::iterator ite_att;
		for (ite_att=dev_att_list.begin() ; ite_att != dev_att_list.end() ; ++ite_att)
		{
			std::string att_name((*ite_att)->get_name_lower());
			if ((att_name == "state") || (att_name == "status"))
				continue;
			std::vector<std::string>::iterator ite_str = find(defaultAttList.begin(), defaultAttList.end(), att_name);
			if (ite_str == defaultAttList.end())
			{
				TANGO_LOG_INFO << att_name << " is a UNWANTED dynamic attribute for device " << (*devlist_ptr)[i] << std::endl;
				Tango::Attribute &att = dev->get_device_attr()->get_attr_by_name(att_name.c_str());
				dev->remove_attribute(att_list[att.get_attr_idx()], true, false);
				--ite_att;
			}
		}
	}
	/*----- PROTECTED REGION ID(MoenchZMQClass::erase_dynamic_attributes) ENABLED START -----*/
	/* clang-format on */
	/* clang-format off */
	/*----- PROTECTED REGION END -----*/	//	MoenchZMQClass::erase_dynamic_attributes
}

//--------------------------------------------------------
/**
 *	Method      : MoenchZMQClass::get_attr_object_by_name()
 * Description:  returns Tango::Attr * object found by name
 */
//--------------------------------------------------------
Tango::Attr *MoenchZMQClass::get_attr_object_by_name(std::vector<Tango::Attr *> &att_list, std::string attname)
{
	std::vector<Tango::Attr *>::iterator it;
	for (it=att_list.begin() ; it<att_list.end() ; ++it)
		if ((*it)->get_name()==attname)
			return (*it);
	//	Attr does not exist
	return NULL;
}


/*----- PROTECTED REGION ID(MoenchZMQClass::Additional Methods) ENABLED START -----*/
/* clang-format on */
/* clang-format off */
/*----- PROTECTED REGION END -----*/	//	MoenchZMQClass::Additional Methods
} //	namespace