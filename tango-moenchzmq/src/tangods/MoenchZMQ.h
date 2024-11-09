#ifndef MoenchZMQ_H
#define MoenchZMQ_H

#include "../backend/FileWriter.hpp"
#include "../backend/ZMQListener.hpp"
#include <tango/tango.h>

#ifdef TANGO_LOG
// cppTango after c934adea (Merge branch 'remove-cout-definition' into 'main',
// 2022-05-23) nothing to do
#else
// cppTango 9.3-backports and older
#define TANGO_LOG cout
#define TANGO_LOG_INFO cout2
#define TANGO_LOG_DEBUG cout3
#endif // TANGO_LOG

/**
 *  MoenchZMQ class description:
 *
 */

namespace MoenchZMQ_ns {

class MoenchZMQ : public TANGO_BASE_CLASS {
  //	Device property data members
public:
  //	ZMQ_IP:
  std::string ZMQ_RX_IP;
  //	ZMQ_PORT:
  Tango::DevULong64 ZMQ_RX_PORT;
  // SAVE_ROOT_PATH
  std::string SAVE_ROOT_PATH;
  // THREAD_AMOUNT
  Tango::DevULong64 THREAD_AMOUNT;
  // PEDESTAL_BUFFER_LENGTH
  Tango::DevFloat PEDESTAL_BUFFER_LENGTH;
  bool mandatoryNotDefined;

  //	Attribute data members
public:
  /*
  Order of the attributes affects the order of their destruction.
  Since the FileWriter is used in the ZMQListener, it must be destroyed after
  the ZMQListener.
  */
  FileWriter *file_writer_ptr;
  ZMQListener *zmq_listener_ptr;
  std::atomic<bool> receiver_is_stopping;
  Tango::DevULong *attr_file_index_read;
  Tango::DevString *attr_file_name_read;
  Tango::DevString *attr_session_directory_read;
  Tango::DevBoolean *attr_normalize_read;
  Tango::DevLong *attr_update_pedestal_period_read;
  Tango::DevDouble *attr_threshold_read;
  Tango::DevFloat *attr_counting_sigma_read;
  Tango::DevBoolean *attr_process_pedestal_read;
  Tango::DevBoolean *attr_save_raw_frames_read;
  Tango::DevBoolean *attr_split_pumped_read;
  Tango::DevLong *attr_acquired_frames_read;
  Tango::DevFloat *attr_analog_img_read;
  Tango::DevFloat *attr_counting_img_read;
  Tango::DevFloat *attr_analog_img_pumped_read;
  Tango::DevFloat *attr_counting_img_pumped_read;
  Tango::DevULong *attr_individual_frame_buffer_capacity_read;
  //	Constructors and destructors
public:
  /**
   * Constructs a newly device object.
   *
   *	@param cl	Class.
   *	@param s 	Device Name
   */
  MoenchZMQ(Tango::DeviceClass *cl, std::string &s);
  /**
   * Constructs a newly device object.
   *
   *	@param cl	Class.
   *	@param s 	Device Name
   */
  MoenchZMQ(Tango::DeviceClass *cl, const char *s);
  /**
   * Constructs a newly device object.
   *
   *	@param cl	Class.
   *	@param s 	Device name
   *	@param d	Device description.
   */
  MoenchZMQ(Tango::DeviceClass *cl, const char *s, const char *d);
  /**
   * The device object destructor.
   */
  ~MoenchZMQ();

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
  void check_mandatory_property(Tango::DbDatum &class_prop,
                                Tango::DbDatum &dev_prop);
  void load_images_previews();
  void copy_image_buffers();
  //	Attribute methods
public:
  //--------------------------------------------------------
  /*
   *	Method      : MoenchZMQ::read_attr_hardware()
   * Description:  Hardware acquisition for attributes.
   */
  //--------------------------------------------------------
  virtual void read_attr_hardware(std::vector<long> &attr_list);
  //--------------------------------------------------------
  /*
   *	Method      : MoenchZMQ::write_attr_hardware()
   * Description:  Hardware writing for attributes.
   */
  //--------------------------------------------------------
  virtual void write_attr_hardware(std::vector<long> &attr_list);

  /**
   *	Attribute file_index related methods
   *
   *
   *	Data type:  Tango::DevULong
   *	Attr type:	Scalar
   */
  virtual void read_file_index(Tango::Attribute &attr);
  virtual void write_file_index(Tango::WAttribute &attr);
  virtual bool is_file_index_allowed(Tango::AttReqType type);
  /**
   *	Attribute filename related methods
   *
   *
   *	Data type:  Tango::DevString
   *	Attr type:	Scalar
   */
  virtual void read_file_name(Tango::Attribute &attr);
  virtual void write_file_name(Tango::WAttribute &attr);
  virtual bool is_file_name_allowed(Tango::AttReqType type);
  /**
   *	Attribute file_root_path related methods
   *
   *
   *	Data type:  Tango::DevString
   *	Attr type:	Scalar
   */
  virtual void read_session_directory(Tango::Attribute &attr);
  virtual void write_session_directory(Tango::WAttribute &attr);
  virtual bool is_session_directory_allowed(Tango::AttReqType type);
  /**
   *	Attribute normalize related methods
   *
   *
   *	Data type:  Tango::DevBoolean
   *	Attr type:	Scalar
   */
  virtual void read_normalize(Tango::Attribute &attr);
  virtual void write_normalize(Tango::WAttribute &attr);
  virtual bool is_normalize_allowed(Tango::AttReqType type);
  /**
   *	Attribute update_pedestal related methods
   *
   *
   *	Data type:  Tango::DevBoolean
   *	Attr type:	Scalar
   */
  virtual void read_update_pedestal_period(Tango::Attribute &attr);
  virtual void write_update_pedestal_period(Tango::WAttribute &attr);
  virtual bool is_update_pedestal_allowed(Tango::AttReqType type);
  /**
   *	Attribute threshold related methods
   *
   *
   *	Data type:  Tango::DevDouble
   *	Attr type:	Scalar
   */
  virtual void read_threshold(Tango::Attribute &attr);
  virtual void write_threshold(Tango::WAttribute &attr);
  virtual bool is_threshold_allowed(Tango::AttReqType type);
  /**
   *	Attribute counting_sigma related methods
   *
   *
   *	Data type:  Tango::DevDouble
   *	Attr type:	Scalar
   */
  virtual void read_counting_sigma(Tango::Attribute &attr);
  virtual void write_counting_sigma(Tango::WAttribute &attr);
  virtual bool is_counting_sigma_allowed(Tango::AttReqType type);
  /**
   *	Attribute process_pedestal related methods
   *
   *
   *	Data type:  Tango::DevBoolean
   *	Attr type:	Scalar
   */
  virtual void read_process_pedestal(Tango::Attribute &attr);
  virtual void write_process_pedestal(Tango::WAttribute &attr);
  virtual bool is_process_pedestal_allowed(Tango::AttReqType type);
  /**
   *	Attribute save_raw_frames related methods
   *
   *
   *	Data type:  Tango::DevBoolean
   *	Attr type:	Scalar
   */
  virtual void read_save_raw_frames(Tango::Attribute &attr);
  virtual void write_save_raw_frames(Tango::WAttribute &attr);
  virtual bool is_save_raw_frames_allowed(Tango::AttReqType type);
  /**
   *	Attribute split_pumped related methods
   *
   *
   *	Data type:  Tango::DevBoolean
   *	Attr type:	Scalar
   */
  virtual void read_split_pumped(Tango::Attribute &attr);
  virtual void write_split_pumped(Tango::WAttribute &attr);
  virtual bool is_split_pumped_allowed(Tango::AttReqType type);
  /**
   *	Attribute acquired_frames related methods
   *
   *
   *	Data type:  Tango::DevLong
   *	Attr type:	Scalar
   */
  virtual void read_acquired_frames(Tango::Attribute &attr);
  virtual bool is_acquired_frames_allowed(Tango::AttReqType type);
  /**
   *	Attribute analog_img related methods
   *
   *
   *	Data type:  Tango::DevFloat
   *	Attr type:	Image max = 400 x 400
   */
  virtual void read_analog_img(Tango::Attribute &attr);
  virtual bool is_analog_img_allowed(Tango::AttReqType type);
  /**
   *	Attribute counting_img related methods
   *
   *
   *	Data type:  Tango::DevFloat
   *	Attr type:	Image max = 400 x 400
   */
  virtual void read_counting_img(Tango::Attribute &attr);
  virtual bool is_counting_img_allowed(Tango::AttReqType type);
  /**
   *	Attribute analog_img_pumped related methods
   *
   *
   *	Data type:  Tango::DevFloat
   *	Attr type:	Image max = 400 x 400
   */
  virtual void read_analog_img_pumped(Tango::Attribute &attr);
  virtual bool is_analog_img_pumped_allowed(Tango::AttReqType type);
  /**
   *	Attribute counting_img_pumped related methods
   *
   *
   *	Data type:  Tango::DevFloat
   *	Attr type:	Image max = 400 x 400
   */
  virtual void read_counting_img_pumped(Tango::Attribute &attr);
  virtual bool is_counting_img_pumped_allowed(Tango::AttReqType type);

  virtual void read_individual_frame_buffer_capacity(Tango::Attribute &attr);
  virtual void write_individual_frame_buffer_capacity(Tango::WAttribute &attr);
  virtual bool
  is_individual_frame_buffer_capacity_allowed(Tango::AttReqType type);

  //--------------------------------------------------------
  /**
   *	Method      : MoenchZMQ::add_dynamic_attributes()
   * Description:  Add dynamic attributes if any.
   */
  //--------------------------------------------------------
  void add_dynamic_attributes();

  //	Command related methods
public:
  /**
   *	Command start_receiver related method
   *
   *
   */
  virtual void start_receiver();
  virtual bool is_start_receiver_allowed(const CORBA::Any &any);
  /**
   *	Command stop_receiver related method
   *
   *
   */
  virtual void stop_receiver();
  virtual bool is_stop_receiver_allowed(const CORBA::Any &any);
  /**
   *	Command abort_receiver related method
   *
   *
   */
  virtual void abort_receiver();
  virtual bool is_abort_receiver_allowed(const CORBA::Any &any);
  /**
   *	Command reset_pedestal related method
   *
   *
   */
  virtual void reset_pedestal();
  virtual bool is_reset_pedestal_allowed(const CORBA::Any &any);
  /**
   *	Command push_images_change related method
   *
   *
   */
  virtual void push_images_change();
  virtual bool is_push_images_change_allowed(const CORBA::Any &any);

  //--------------------------------------------------------
  /**
   *	Method      : MoenchZMQ::add_dynamic_commands()
   * Description:  Add dynamic commands if any.
   */
  //--------------------------------------------------------
  void add_dynamic_commands();

  //	Additional Method prototypes
};

//	Additional Classes Definitions

} //	End of namespace

#endif //	MoenchZMQ_H
