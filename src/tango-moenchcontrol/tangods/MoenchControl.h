/*----- PROTECTED REGION ID(MoenchControl.h) ENABLED START -----*/
/* clang-format on */
//=============================================================================
//
// file :        MoenchControl.h
//
// description : Include file for the MoenchControl class
//
// project :     Tango device for control of MOENCH detector
//
// This file is part of Tango device class.
//
// Tango is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// Tango is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with Tango.  If not, see <http://www.gnu.org/licenses/>.
//
//
//
//=============================================================================
//                This file is generated by POGO
//        (Program Obviously used to Generate tango Object)
//=============================================================================


#ifndef MoenchControl_H
#define MoenchControl_H

#include <tango/tango.h>

/* clang-format off */
#include "sls/Receiver.h"
#include "sls/Detector.h"
#include "sls/sls_detector_defs.h"
/*----- PROTECTED REGION END -----*/	//	MoenchControl.h

#ifdef TANGO_LOG
	// cppTango after c934adea (Merge branch 'remove-cout-definition' into 'main', 2022-05-23)
	// nothing to do
#else
	// cppTango 9.3-backports and older
	#define TANGO_LOG       cout
	#define TANGO_LOG_INFO  cout2
	#define TANGO_LOG_DEBUG cout3
#endif // TANGO_LOG

/**
 *  MoenchControl class description:
 *    
 */


namespace MoenchControl_ns
{
enum class _timing_modeEnum : short {
	_AUTO_TIMING,
	_TRIGGER_EXPOSURE,
} ;
using floatsec = std::chrono::duration<float>; 
typedef slsDetectorDefs::timingMode timing_modeEnum;

enum class _gain_modeEnum : short {
	_G1_HIGHGAIN,
	_G1_LOWGAIN,
	_G2_HIGHCAP_HIGHGAIN,
	_G2_HIGHCAP_LOWGAIN,
	_G2_LOWCAP_HIGHGAIN,
	_G2_LOWCAP_LOWGAIN,
	_G4_HIGHGAIN,
	_G4_LOWGAIN,
} ;
typedef slsDetectorDefs::gainMode gain_modeEnum;

enum class _rx_discard_policyEnum : short {
	_NO_DISCARD,
	_DISCARD_EMPTY_FRAMES,
	_DISCARD_PARTIAL_FRAMES,
} ;
typedef slsDetectorDefs::frameDiscardPolicy rx_discard_policyEnum;

enum class _detector_statusEnum : short {
	_IDLE,
	_ERROR,
	_WAITING,
	_RUN_FINISHED,
	_TRANSMITTING,
	_RUNNING,
	_STOPPED,
} ;
typedef slsDetectorDefs::runStatus detector_statusEnum;

/*----- PROTECTED REGION ID(MoenchControl::Additional Class Declarations) ENABLED START -----*/
/* clang-format on */
//	Additional Class Declarations
/* clang-format off */
/*----- PROTECTED REGION END -----*/	//	MoenchControl::Additional Class Declarations

class MoenchControl : public TANGO_BASE_CLASS
{

/*----- PROTECTED REGION ID(MoenchControl::Data Members) ENABLED START -----*/
/* clang-format on */
private:
	std::unique_ptr<sls::Receiver> receiver_ptr;
	std::unique_ptr<sls::Detector> detector_ptr;
/* clang-format off */
/*----- PROTECTED REGION END -----*/	//	MoenchControl::Data Members

//	Device property data members
public:
	//	SLS_RECEIVER_PORT:	port for slsReceiver, default: 1954
	Tango::DevLong64	sLS_RECEIVER_PORT;
	//	PROCESSING_RX_IP:	ip of 10gbe ``PC <-> detector`` lane of PC,
	//  must match the config,
	//  default: 192.168.2.200
	std::string	pROCESSING_RX_IP;
	//	PROCESSING_RX_PORT:	port for 10gbe ``PC <-> detector`` lane of PC,
	//  must match the config,
	//  default: 50003
	std::string	pROCESSING_RX_PORT;
	//	CONTROL_TX_IP:	ip for 1gbe lane (lab local network) of PC,
	//  must match the config,
	//  default: 192.168.1.118
	std::string	cONTROL_TX_IP;
	//	CONTROL_TX_PORT:	port for 1gbe (lab local network) lane of PC,
	//  must match the config,
	//  default: 50001
	Tango::DevLong64	cONTROL_TX_PORT;
	//	MOENCHZMQ_DEVICE:	FQDN of Moenchzmq TangoDS,
	//  default: rsxs/moenchZmq/bchip286
	std::string	mOENCHZMQ_DEVICE;
	//	DETECTOR_CONFIG_PATH:	Path to the config file for the detector,
	//  default: /home/moench/.../moench03.config
	std::string	dETECTOR_CONFIG_PATH;

	bool	mandatoryNotDefined;

//	Attribute data members
public:
	Tango::DevFloat	*attr_exposure_read;
	Tango::DevFloat	*attr_delay_read;
	timing_modeEnum	*attr_timing_mode_read;
	Tango::DevLong64	*attr_triggers_read;
	Tango::DevLong64	*attr_frames_read;
	Tango::DevLong64	*attr_high_voltage_read;
	gain_modeEnum	*attr_gain_mode_read;
	Tango::DevFloat	*attr_period_read;
	Tango::DevString	*attr_zmq_rx_ip_read;
	Tango::DevUShort	*attr_zmq_rx_port_read;
	rx_discard_policyEnum	*attr_rx_discard_policy_read;
	Tango::DevString	*attr_rx_hostname_read;
	Tango::DevLong64	*attr_rx_tcp_port_read;
	detector_statusEnum	*attr_detector_status_read;
	Tango::DevBoolean	*attr_rx_zmq_data_stream_read;

//	Constructors and destructors
public:
	/**
	 * Constructs a newly device object.
	 *
	 *	@param cl	Class.
	 *	@param s 	Device Name
	 */
	MoenchControl(Tango::DeviceClass *cl,std::string &s);
	/**
	 * Constructs a newly device object.
	 *
	 *	@param cl	Class.
	 *	@param s 	Device Name
	 */
	MoenchControl(Tango::DeviceClass *cl,const char *s);
	/**
	 * Constructs a newly device object.
	 *
	 *	@param cl	Class.
	 *	@param s 	Device name
	 *	@param d	Device description.
	 */
	MoenchControl(Tango::DeviceClass *cl,const char *s,const char *d);
	/**
	 * The device object destructor.
	 */
	~MoenchControl();


//	Miscellaneous methods
public:
	/*
	 *	will be called at device destruction or at init command.
	 */
	void delete_device();
	/*
	 *	Initialize the device
	 */
	virtual void init_device();
	/*
	 *	Read the device properties from database
	 */
	void get_device_property();
	/*
	 *	Always executed method before execution command method.
	 */
	virtual void always_executed_hook();

	/*
	 *	Check if mandatory property has been set
	 */
	 void check_mandatory_property(Tango::DbDatum &class_prop, Tango::DbDatum &dev_prop);

//	Attribute methods
public:
	//--------------------------------------------------------
	/*
	 *	Method      : MoenchControl::read_attr_hardware()
	 * Description:  Hardware acquisition for attributes.
	 */
	//--------------------------------------------------------
	virtual void read_attr_hardware(std::vector<long> &attr_list);
	//--------------------------------------------------------
	/*
	 *	Method      : MoenchControl::write_attr_hardware()
	 * Description:  Hardware writing for attributes.
	 */
	//--------------------------------------------------------
	virtual void write_attr_hardware(std::vector<long> &attr_list);

/**
 *	Attribute exposure related methods
 *
 *
 *	Data type:  Tango::DevFloat
 *	Attr type:	Scalar
 */
	virtual void read_exposure(Tango::Attribute &attr);
	virtual void write_exposure(Tango::WAttribute &attr);
	virtual bool is_exposure_allowed(Tango::AttReqType type);
/**
 *	Attribute delay related methods
 *
 *
 *	Data type:  Tango::DevFloat
 *	Attr type:	Scalar
 */
	virtual void read_delay(Tango::Attribute &attr);
	virtual void write_delay(Tango::WAttribute &attr);
	virtual bool is_delay_allowed(Tango::AttReqType type);
/**
 *	Attribute timing_mode related methods
 *
 *
 *	Data type:  Tango::DevEnum
 *	Attr type:	Scalar
 */
	virtual void read_timing_mode(Tango::Attribute &attr);
	virtual void write_timing_mode(Tango::WAttribute &attr);
	virtual bool is_timing_mode_allowed(Tango::AttReqType type);
/**
 *	Attribute triggers related methods
 *
 *
 *	Data type:  Tango::DevLong64
 *	Attr type:	Scalar
 */
	virtual void read_triggers(Tango::Attribute &attr);
	virtual void write_triggers(Tango::WAttribute &attr);
	virtual bool is_triggers_allowed(Tango::AttReqType type);
/**
 *	Attribute frames related methods
 *
 *
 *	Data type:  Tango::DevLong64
 *	Attr type:	Scalar
 */
	virtual void read_frames(Tango::Attribute &attr);
	virtual void write_frames(Tango::WAttribute &attr);
	virtual bool is_frames_allowed(Tango::AttReqType type);
/**
 *	Attribute high_voltage related methods
 *
 *
 *	Data type:  Tango::DevLong64
 *	Attr type:	Scalar
 */
	virtual void read_high_voltage(Tango::Attribute &attr);
	virtual void write_high_voltage(Tango::WAttribute &attr);
	virtual bool is_high_voltage_allowed(Tango::AttReqType type);
/**
 *	Attribute gain_mode related methods
 *
 *
 *	Data type:  Tango::DevEnum
 *	Attr type:	Scalar
 */
	virtual void read_gain_mode(Tango::Attribute &attr);
	virtual void write_gain_mode(Tango::WAttribute &attr);
	virtual bool is_gain_mode_allowed(Tango::AttReqType type);
/**
 *	Attribute period related methods
 *
 *
 *	Data type:  Tango::DevFloat
 *	Attr type:	Scalar
 */
	virtual void read_period(Tango::Attribute &attr);
	virtual void write_period(Tango::WAttribute &attr);
	virtual bool is_period_allowed(Tango::AttReqType type);
/**
 *	Attribute zmq_rx_ip related methods
 *
 *
 *	Data type:  Tango::DevString
 *	Attr type:	Scalar
 */
	virtual void read_zmq_rx_ip(Tango::Attribute &attr);
	virtual void write_zmq_rx_ip(Tango::WAttribute &attr);
	virtual bool is_zmq_rx_ip_allowed(Tango::AttReqType type);
/**
 *	Attribute zmq_rx_port related methods
 *
 *
 *	Data type:  Tango::DevUShort
 *	Attr type:	Scalar
 */
	virtual void read_zmq_rx_port(Tango::Attribute &attr);
	virtual void write_zmq_rx_port(Tango::WAttribute &attr);
	virtual bool is_zmq_rx_port_allowed(Tango::AttReqType type);
/**
 *	Attribute rx_discard_policy related methods
 *
 *
 *	Data type:  Tango::DevEnum
 *	Attr type:	Scalar
 */
	virtual void read_rx_discard_policy(Tango::Attribute &attr);
	virtual void write_rx_discard_policy(Tango::WAttribute &attr);
	virtual bool is_rx_discard_policy_allowed(Tango::AttReqType type);
/**
 *	Attribute rx_hostname related methods
 *
 *
 *	Data type:  Tango::DevString
 *	Attr type:	Scalar
 */
	virtual void read_rx_hostname(Tango::Attribute &attr);
	virtual void write_rx_hostname(Tango::WAttribute &attr);
	virtual bool is_rx_hostname_allowed(Tango::AttReqType type);
/**
 *	Attribute rx_tcp_port related methods
 *
 *
 *	Data type:  Tango::DevLong64
 *	Attr type:	Scalar
 */
	virtual void read_rx_tcp_port(Tango::Attribute &attr);
	virtual void write_rx_tcp_port(Tango::WAttribute &attr);
	virtual bool is_rx_tcp_port_allowed(Tango::AttReqType type);
/**
 *	Attribute detector_status related methods
 *
 *
 *	Data type:  Tango::DevEnum
 *	Attr type:	Scalar
 */
	virtual void read_detector_status(Tango::Attribute &attr);
	virtual bool is_detector_status_allowed(Tango::AttReqType type);
/**
 *	Attribute rx_zmq_data_stream related methods
 *
 *
 *	Data type:  Tango::DevBoolean
 *	Attr type:	Scalar
 */
	virtual void read_rx_zmq_data_stream(Tango::Attribute &attr);
	virtual void write_rx_zmq_data_stream(Tango::WAttribute &attr);
	virtual bool is_rx_zmq_data_stream_allowed(Tango::AttReqType type);


	//--------------------------------------------------------
	/**
	 *	Method      : MoenchControl::add_dynamic_attributes()
	 * Description:  Add dynamic attributes if any.
	 */
	//--------------------------------------------------------
	void add_dynamic_attributes();




//	Command related methods
public:
	/**
	 *	Command start_acquire related method
	 *
	 *
	 */
	virtual void start_acquire();
	virtual bool is_start_acquire_allowed(const CORBA::Any &any);
	/**
	 *	Command stop_acquire related method
	 *
	 *
	 */
	virtual void stop_acquire();
	virtual bool is_stop_acquire_allowed(const CORBA::Any &any);

	virtual void check_stop_in_backgroud();


	//--------------------------------------------------------
	/**
	 *	Method      : MoenchControl::add_dynamic_commands()
	 * Description:  Add dynamic commands if any.
	 */
	//--------------------------------------------------------
	void add_dynamic_commands();

/*----- PROTECTED REGION ID(MoenchControl::Additional Method prototypes) ENABLED START -----*/
/* clang-format on */
//	Additional Method prototypes
/* clang-format off */
/*----- PROTECTED REGION END -----*/	//	MoenchControl::Additional Method prototypes
};

/*----- PROTECTED REGION ID(MoenchControl::Additional Classes Definitions) ENABLED START -----*/
/* clang-format on */
//	Additional Classes Definitions
/* clang-format off */
/*----- PROTECTED REGION END -----*/	//	MoenchControl::Additional Classes Definitions

}	//	End of namespace

#endif   //	MoenchControl_H