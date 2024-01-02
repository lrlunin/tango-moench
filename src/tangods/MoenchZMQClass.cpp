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

	//	Attribute : filename
	filenameAttrib	*filename = new filenameAttrib();
	Tango::UserDefaultAttrProp	filename_prop;
	//	description	not set for filename
	//	label	not set for filename
	//	unit	not set for filename
	//	standard_unit	not set for filename
	//	display_unit	not set for filename
	//	format	not set for filename
	//	max_value	not set for filename
	//	min_value	not set for filename
	//	max_alarm	not set for filename
	//	min_alarm	not set for filename
	//	max_warning	not set for filename
	//	min_warning	not set for filename
	//	delta_t	not set for filename
	//	delta_val	not set for filename
	filename->set_default_properties(filename_prop);
	//	Not Polled
	filename->set_disp_level(Tango::OPERATOR);
	//	Not Memorized
	att_list.push_back(filename);

	//	Attribute : file_root_path
	file_root_pathAttrib	*file_root_path = new file_root_pathAttrib();
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
	// file_root_path->set_memorized();
	// file_root_path->set_memorized_init(false);
	att_list.push_back(file_root_path);

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
	att_list.push_back(counting_img);


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