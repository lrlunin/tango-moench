#include "MoenchZMQ.h"
#include "../backend/FileWriter.hpp"
#include "../backend/HDFWriter.hpp"
#include "MoenchZMQClass.h"
#include "data.hpp"

//================================================================
//  The following table gives the correspondence
//  between command and method names.
//
//  Command name    |  Method name
//================================================================
//  State           |  Inherited (no method)
//  Status          |  Inherited (no method)
//  start_receiver  |  start_receiver
//  stop_receiver   |  stop_receiver
//  abort_receiver  |  abort_receiver
//  reset_pedestal  |  reset_pedestal
//================================================================

//================================================================
//  Attributes managed are:
//================================================================
//  file_index        |  Tango::DevULong	Scalar
//  filename          |  Tango::DevString	Scalar
//  file_root_path    |  Tango::DevString	Scalar
//  normalize         |  Tango::DevBoolean	Scalar
//  threshold         |  Tango::DevDouble	Scalar
//  counting_sigma    |  Tango::DevFloat	Scalar
//  process_pedestal  |  Tango::DevBoolean	Scalar
//  analog_img        |  Tango::DevFloat	Image  ( max = 400 x 400)
//  counting_img      |  Tango::DevFloat	Image  ( max = 400 x 400)
//================================================================

namespace MoenchZMQ_ns {
//--------------------------------------------------------
/**
 *	Method      : MoenchZMQ::MoenchZMQ()
 * Description:  Constructors for a Tango device
 *                implementing the classMoenchZMQ
 */
//--------------------------------------------------------
MoenchZMQ::MoenchZMQ(Tango::DeviceClass *cl, std::string &s)
    : TANGO_BASE_CLASS(cl, s.c_str()) {
  init_device();
}

//--------------------------------------------------------
MoenchZMQ::MoenchZMQ(Tango::DeviceClass *cl, const char *s)
    : TANGO_BASE_CLASS(cl, s) {
  init_device();
}

//--------------------------------------------------------
MoenchZMQ::MoenchZMQ(Tango::DeviceClass *cl, const char *s, const char *d)
    : TANGO_BASE_CLASS(cl, s, d) {
  init_device();
}

//--------------------------------------------------------
MoenchZMQ::~MoenchZMQ() { delete_device(); }

//--------------------------------------------------------
/**
 *	Method      : MoenchZMQ::delete_device()
 * Description:  will be called at device destruction or at init command
 */
//--------------------------------------------------------
void MoenchZMQ::delete_device() {
  DEBUG_STREAM << "MoenchZMQ::delete_device() " << device_name << std::endl;
  delete zmq_listener_ptr->comp_backend_ptr;
  delete zmq_listener_ptr;
  delete file_writer_ptr;
  delete[] attr_file_index_read;
  delete[] attr_file_name_read;
  delete[] attr_session_directory_read;
  delete[] attr_normalize_read;
  delete[] attr_update_pedestal_period_read;
  delete[] attr_threshold_read;
  delete[] attr_counting_sigma_read;
  delete[] attr_process_pedestal_read;
  delete[] attr_analog_img_read;
  delete[] attr_counting_img_read;
  delete[] attr_analog_img_pumped_read;
  delete[] attr_counting_img_pumped_read;
  delete[] attr_split_pumped_read;
}

//--------------------------------------------------------
/**
 *	Method      : MoenchZMQ::init_device()
 * Description:  will be called at device initialization.
 */
//--------------------------------------------------------
void MoenchZMQ::init_device() {
  DEBUG_STREAM << "MoenchZMQ::init_device() create device " << device_name
               << std::endl;
  //	Initialization before get_device_property() call
  //	Get the device properties from database
  set_state(Tango::INIT);
  get_device_property();

  file_writer_ptr = new HDFWriter(SAVE_ROOT_PATH);
  zmq_listener_ptr = new ZMQListener(ZMQ_RX_IP, ZMQ_RX_PORT);
  zmq_listener_ptr->comp_backend_ptr = new CPUComputationBackend(
      file_writer_ptr, PEDESTAL_BUFFER_LENGTH, THREAD_AMOUNT);

  attr_file_index_read = new Tango::DevULong[1];
  attr_file_name_read = new Tango::DevString[1];
  attr_session_directory_read = new Tango::DevString[1];
  attr_acquired_frames_read = new Tango::DevLong[1];
  attr_normalize_read = new Tango::DevBoolean[1];
  attr_update_pedestal_period_read = new Tango::DevLong[1];
  attr_threshold_read = new Tango::DevDouble[1];
  attr_counting_sigma_read = new Tango::DevFloat[1];
  attr_process_pedestal_read = new Tango::DevBoolean[1];
  attr_split_pumped_read = new Tango::DevBoolean[1];
  attr_analog_img_read = new Tango::DevFloat[400 * 400];
  attr_analog_img_pumped_read = new Tango::DevFloat[400 * 400];
  attr_counting_img_read = new Tango::DevFloat[400 * 400];
  attr_counting_img_pumped_read = new Tango::DevFloat[400 * 400];
  attr_individual_frame_buffer_capacity_read = new Tango::DevULong[1];
  //	No longer if mandatory property not set.
  if (mandatoryNotDefined)
    return;
  *attr_normalize_read = false;
  load_images_previews();
  set_state(Tango::ON);
}

//--------------------------------------------------------
/**
 *	Method      : MoenchZMQ::get_device_property()
 * Description:  Read database to initialize property data members.
 */
//--------------------------------------------------------
void MoenchZMQ::get_device_property() {
  //	Initialize property data members
  ZMQ_RX_IP = "127.0.0.1";
  ZMQ_RX_PORT = 50003;
  SAVE_ROOT_PATH = "/home/data";
  THREAD_AMOUNT = 2;
  PEDESTAL_BUFFER_LENGTH = 5000;
  mandatoryNotDefined = false;
  Tango::DbData dev_prop{ Tango::DbDatum("ZMQ_RX_IP"),
                          Tango::DbDatum("ZMQ_RX_PORT"),
                          Tango::DbDatum("SAVE_ROOT_PATH"),
                          Tango::DbDatum("THREAD_AMOUNT"),
                          Tango::DbDatum("PEDESTAL_BUFFER_LENGTH") };
  get_db_device()->get_property(dev_prop);
  // if any of the properties is empty, mark the device as not initialized
  for (auto &prop : dev_prop) {
    if (!prop.is_empty()) {
      if (prop.name == "ZMQ_RX_IP") {
        prop >> ZMQ_RX_IP;
      } else if (prop.name == "ZMQ_RX_PORT") {
        prop >> ZMQ_RX_PORT;
      } else if (prop.name == "SAVE_ROOT_PATH") {
        prop >> SAVE_ROOT_PATH;
      } else if (prop.name == "THREAD_AMOUNT") {
        prop >> THREAD_AMOUNT;
      } else if (prop.name == "PEDESTAL_BUFFER_LENGTH") {
        prop >> PEDESTAL_BUFFER_LENGTH;
      } else
        DEBUG_STREAM << "Not defined, use default value for " << prop.name
                     << std::endl;
    }
  }
  DEBUG_STREAM << "ZMQ_RX_IP: " << ZMQ_RX_IP << std::endl;
  DEBUG_STREAM << "ZMQ_RX_PORT: " << ZMQ_RX_PORT << std::endl;
  DEBUG_STREAM << "SAVE_ROOT_PATH: " << SAVE_ROOT_PATH << std::endl;
  DEBUG_STREAM << "THREAD_AMOUNT: " << THREAD_AMOUNT << std::endl;
  DEBUG_STREAM << "PEDESTAL_BUFFER_LENGTH: " << PEDESTAL_BUFFER_LENGTH
               << std::endl;
}

void MoenchZMQ::load_images_previews() {
  std::copy(ANALOG_UNPUMPED,
            ANALOG_UNPUMPED
                + counting_imgAttrib::X_DATA_SIZE
                      * counting_imgAttrib::Y_DATA_SIZE,
            attr_analog_img_read);
  std::copy(ANALOG_PUMPED,
            ANALOG_PUMPED
                + counting_imgAttrib::X_DATA_SIZE
                      * counting_imgAttrib::Y_DATA_SIZE,
            attr_analog_img_pumped_read);
  std::copy(COUNTING_UNPUMPED,
            COUNTING_UNPUMPED
                + counting_imgAttrib::X_DATA_SIZE
                      * counting_imgAttrib::Y_DATA_SIZE,
            attr_counting_img_read);
  std::copy(COUNTING_PUMPED,
            COUNTING_PUMPED
                + counting_imgAttrib::X_DATA_SIZE
                      * counting_imgAttrib::Y_DATA_SIZE,
            attr_counting_img_pumped_read);
}

//--------------------------------------------------------
/**
 *	Method      : MoenchZMQ::check_mandatory_property()
 * Description:  For mandatory properties check if defined in database.
 */
//--------------------------------------------------------
void MoenchZMQ::check_mandatory_property(Tango::DbDatum &class_prop,
                                         Tango::DbDatum &dev_prop) {
  //	Check if all properties are empty
  if (class_prop.is_empty() && dev_prop.is_empty()) {
    TangoSys_OMemStream tms;
    tms << std::endl << "Property \'" << dev_prop.name;
    if (Tango::Util::instance()->_UseDb == true)
      tms << "\' is mandatory but not defined in database";
    else
      tms << "\' is mandatory but cannot be defined without database";
    append_status(tms.str());
    mandatoryNotDefined = true;

    std::cerr << tms.str() << " for " << device_name << std::endl;
  }
}

//--------------------------------------------------------
/**
 *	Method      : MoenchZMQ::always_executed_hook()
 * Description:  method always executed before any command is executed
 */
//--------------------------------------------------------
void MoenchZMQ::always_executed_hook() {
  DEBUG_STREAM << "MoenchZMQ::always_executed_hook()  " << device_name
               << std::endl;
  if (mandatoryNotDefined) {
    Tango::Except::throw_exception(
        (const char *)"PROPERTY_NOT_SET", get_status().c_str(),
        (const char *)"MoenchZMQ::always_executed_hook()");
  }
}

//--------------------------------------------------------
/**
 *	Method      : MoenchZMQ::read_attr_hardware()
 * Description:  Hardware acquisition for attributes
 */
//--------------------------------------------------------
void MoenchZMQ::read_attr_hardware(
    TANGO_UNUSED(std::vector<long> &attr_list)) {
  DEBUG_STREAM << "MoenchZMQ::read_attr_hardware(std::vector<long> "
                  "&attr_list) entering... "
               << std::endl;
}

//--------------------------------------------------------
/**
 *	Method      : MoenchZMQ::write_attr_hardware()
 * Description:  Hardware writing for attributes
 */
//--------------------------------------------------------
void MoenchZMQ::write_attr_hardware(
    TANGO_UNUSED(std::vector<long> &attr_list)) {
  DEBUG_STREAM << "MoenchZMQ::write_attr_hardware(std::vector<long> "
                  "&attr_list) entering... "
               << std::endl;
}

//--------------------------------------------------------
/**
 *	Read attribute file_index related method
 *
 *
 *	Data type:	Tango::DevULong
 *	Attr type:	Scalar
 */
//--------------------------------------------------------
void MoenchZMQ::read_file_index(Tango::Attribute &attr) {
  DEBUG_STREAM
      << "MoenchZMQ::read_file_index(Tango::Attribute &attr) entering... "
      << std::endl;
  //	Set the attribute value
  *attr_file_index_read = file_writer_ptr->file_index;
  attr.set_value(attr_file_index_read);
}

//--------------------------------------------------------
/**
 *	Write attribute file_index related method
 *
 *
 *	Data type:	Tango::DevULong
 *	Attr type:	Scalar
 */
//--------------------------------------------------------
void MoenchZMQ::write_file_index(Tango::WAttribute &attr) {
  DEBUG_STREAM
      << "MoenchZMQ::write_file_index(Tango::WAttribute &attr) entering... "
      << std::endl;
  //	Retrieve write value
  Tango::DevULong w_val;
  attr.get_write_value(w_val);
  *attr_file_index_read = w_val;
  file_writer_ptr->file_index = w_val;
}

//--------------------------------------------------------
/**
 *	Read attribute filename related method
 *
 *
 *	Data type:	Tango::DevString
 *	Attr type:	Scalar
 */
//--------------------------------------------------------
void MoenchZMQ::read_file_name(Tango::Attribute &attr) {
  DEBUG_STREAM
      << "MoenchZMQ::read_filename(Tango::Attribute &attr) entering... "
      << std::endl;
  //	Set the attribute value
  *attr_file_name_read = Tango::string_dup(file_writer_ptr->file_name);
  attr.set_value(attr_file_name_read);
}

//--------------------------------------------------------
/**
 *	Write attribute filename related method
 *
 *
 *	Data type:	Tango::DevString
 *	Attr type:	Scalar
 */
//--------------------------------------------------------
void MoenchZMQ::write_file_name(Tango::WAttribute &attr) {
  DEBUG_STREAM
      << "MoenchZMQ::write_filename(Tango::WAttribute &attr) entering... "
      << std::endl;
  //	Retrieve write value
  Tango::DevString w_val;
  attr.get_write_value(w_val);
  *attr_file_name_read = w_val;
  file_writer_ptr->file_name = w_val;
}

//--------------------------------------------------------
/**
 *	Read attribute file_root_path related method
 *
 *
 *	Data type:	Tango::DevString
 *	Attr type:	Scalar
 */
//--------------------------------------------------------
void MoenchZMQ::read_session_directory(Tango::Attribute &attr) {
  DEBUG_STREAM << "MoenchZMQ::read_session_directory(Tango::Attribute &attr) "
                  "entering... "
               << std::endl;
  //	Set the attribute value
  *attr_session_directory_read
      = Tango::string_dup(file_writer_ptr->session_directory);
  attr.set_value(attr_session_directory_read);
}

//--------------------------------------------------------
/**
 *	Write attribute file_root_path related method
 *
 *
 *	Data type:	Tango::DevString
 *	Attr type:	Scalar
 */
//--------------------------------------------------------
void MoenchZMQ::write_session_directory(Tango::WAttribute &attr) {
  DEBUG_STREAM << "MoenchZMQ::write_session_directory(Tango::WAttribute "
                  "&attr) entering... "
               << std::endl;
  //	Retrieve write value
  Tango::DevString w_val;
  attr.get_write_value(w_val);
  *attr_session_directory_read = w_val;
  file_writer_ptr->session_directory = w_val;
}

//--------------------------------------------------------
/**
 *	Read attribute normalize related method
 *
 *
 *	Data type:	Tango::DevBoolean
 *	Attr type:	Scalar
 */
//--------------------------------------------------------
void MoenchZMQ::read_normalize(Tango::Attribute &attr) {
  DEBUG_STREAM
      << "MoenchZMQ::read_normalize(Tango::Attribute &attr) entering... "
      << std::endl;
  //	Set the attribute value
  attr.set_value(attr_normalize_read);
}

//--------------------------------------------------------
/**
 *	Write attribute normalize related method
 *
 *
 *	Data type:	Tango::DevBoolean
 *	Attr type:	Scalar
 */
//--------------------------------------------------------
void MoenchZMQ::write_normalize(Tango::WAttribute &attr) {
  DEBUG_STREAM
      << "MoenchZMQ::write_normalize(Tango::WAttribute &attr) entering... "
      << std::endl;
  //	Retrieve write value
  Tango::DevBoolean w_val;
  attr.get_write_value(w_val);
  //	Add your own code
}

void MoenchZMQ::read_update_pedestal_period(Tango::Attribute &attr) {
  DEBUG_STREAM
      << "MoenchZMQ::read_update_pedestal(Tango::Attribute &attr) entering... "
      << std::endl;
  //	Set the attribute value
  *attr_update_pedestal_period_read
      = zmq_listener_ptr->comp_backend_ptr->updatePedestalPeriod;
  attr.set_value(attr_update_pedestal_period_read);
}

void MoenchZMQ::write_update_pedestal_period(Tango::WAttribute &attr) {
  DEBUG_STREAM << "MoenchZMQ::write_update_pedestal(Tango::WAttribute &attr) "
                  "entering... "
               << std::endl;
  //	Retrieve write value
  Tango::DevLong w_val;
  attr.get_write_value(w_val);
  *attr_update_pedestal_period_read = w_val;
  zmq_listener_ptr->comp_backend_ptr->updatePedestalPeriod = w_val;
}

void MoenchZMQ::write_threshold(Tango::WAttribute &attr) {
  DEBUG_STREAM
      << "MoenchZMQ::write_threshold(Tango::WAttribute &attr) entering... "
      << std::endl;
  //	Retrieve write value
  Tango::DevDouble w_val;
  attr.get_write_value(w_val);
  *attr_threshold_read = w_val;
}

//--------------------------------------------------------
/**
 *	Read attribute threshold related method
 *
 *
 *	Data type:	Tango::DevDouble
 *	Attr type:	Scalar
 */
//--------------------------------------------------------
void MoenchZMQ::read_threshold(Tango::Attribute &attr) {
  DEBUG_STREAM
      << "MoenchZMQ::read_threshold(Tango::Attribute &attr) entering... "
      << std::endl;
  //	Set the attribute value
  attr.set_value(attr_threshold_read);
}

//--------------------------------------------------------
/**
 *	Read attribute counting_sigma related method
 *
 *
 *	Data type:	Tango::DevDouble
 *	Attr type:	Scalar
 */
//--------------------------------------------------------
void MoenchZMQ::read_counting_sigma(Tango::Attribute &attr) {
  DEBUG_STREAM
      << "MoenchZMQ::read_counting_sigma(Tango::Attribute &attr) entering... "
      << std::endl;
  //	Set the attribute value
  *attr_counting_sigma_read
      = zmq_listener_ptr->comp_backend_ptr->counting_sigma.load();
  attr.set_value(attr_counting_sigma_read);
}

//--------------------------------------------------------
/**
 *	Read attribute analog_img_pumped related method
 *
 *
 *	Data type:	Tango::DevFloat
 *	Attr type:	Image max = 400 x 400
 */
//--------------------------------------------------------
void MoenchZMQ::read_analog_img_pumped(Tango::Attribute &attr) {
  DEBUG_STREAM << "MoenchZMQ::read_analog_img_pumped(Tango::Attribute &attr) "
                  "entering... "
               << std::endl;
  //	Set the attribute value
  attr.set_value(attr_analog_img_pumped_read,
                 analog_img_pumpedAttrib::X_DATA_SIZE,
                 analog_img_pumpedAttrib::Y_DATA_SIZE);
}

//--------------------------------------------------------
/**
 *	Read attribute counting_img_pumped related method
 *
 *
 *	Data type:	Tango::DevFloat
 *	Attr type:	Image max = 400 x 400
 */
//--------------------------------------------------------
void MoenchZMQ::read_counting_img_pumped(Tango::Attribute &attr) {
  DEBUG_STREAM << "MoenchZMQ::read_counting_img_pumped(Tango::Attribute "
                  "&attr) entering... "
               << std::endl;
  //	Set the attribute value
  attr.set_value(attr_counting_img_pumped_read,
                 counting_img_pumpedAttrib::X_DATA_SIZE,
                 counting_img_pumpedAttrib::Y_DATA_SIZE);
}

//--------------------------------------------------------
/**
 *	Write attribute counting_sigma related method
 *
 *
 *	Data type:	Tango::DevDouble
 *	Attr type:	Scalar
 */
//--------------------------------------------------------
void MoenchZMQ::write_counting_sigma(Tango::WAttribute &attr) {
  DEBUG_STREAM << "MoenchZMQ::write_counting_sigma(Tango::WAttribute &attr) "
                  "entering... "
               << std::endl;
  //	Retrieve write value
  Tango::DevFloat w_val;
  attr.get_write_value(w_val);
  *attr_counting_sigma_read = w_val;
  zmq_listener_ptr->comp_backend_ptr->counting_sigma = w_val;
}

//--------------------------------------------------------
/**
 *	Read attribute process_pedestal related method
 *
 *
 *	Data type:	Tango::DevBoolean
 *	Attr type:	Scalar
 */
//--------------------------------------------------------
void MoenchZMQ::read_process_pedestal(Tango::Attribute &attr) {
  DEBUG_STREAM << "MoenchZMQ::read_process_pedestal(Tango::Attribute &attr) "
                  "entering... "
               << std::endl;
  //	Set the attribute value
  *attr_process_pedestal_read = zmq_listener_ptr->comp_backend_ptr->isPedestal;
  attr.set_value(attr_process_pedestal_read);
}

//--------------------------------------------------------
/**
 *	Read attribute split_pumped related method
 *
 *
 *	Data type:	Tango::DevBoolean
 *	Attr type:	Scalar
 */
//--------------------------------------------------------
void MoenchZMQ::read_split_pumped(Tango::Attribute &attr) {
  DEBUG_STREAM
      << "MoenchZMQ::read_split_pumped(Tango::Attribute &attr) entering... "
      << std::endl;
  //	Set the attribute value
  *attr_split_pumped_read = zmq_listener_ptr->comp_backend_ptr->isSplitPumped;
  attr.set_value(attr_split_pumped_read);
}

//--------------------------------------------------------
/**
 *	Read attribute acquired_frames related method
 *
 *
 *	Data type:	Tango::DevLong
 *	Attr type:	Scalar
 */
//--------------------------------------------------------
void MoenchZMQ::read_acquired_frames(Tango::Attribute &attr) {
  DEBUG_STREAM
      << "MoenchZMQ::read_acquired_frames(Tango::Attribute &attr) entering... "
      << std::endl;
  //	Set the attribute value
  *attr_acquired_frames_read = zmq_listener_ptr->received_frames_amount.load();
  attr.set_value(attr_acquired_frames_read);
}

//--------------------------------------------------------
//--------------------------------------------------------
/**
 *	Write attribute split_pumped related method
 *
 *
 *	Data type:	Tango::DevBoolean
 *	Attr type:	Scalar
 */
//--------------------------------------------------------
void MoenchZMQ::write_split_pumped(Tango::WAttribute &attr) {
  DEBUG_STREAM
      << "MoenchZMQ::write_split_pumped(Tango::WAttribute &attr) entering... "
      << std::endl;
  //	Retrieve write value
  Tango::DevBoolean w_val;
  attr.get_write_value(w_val);
  *attr_split_pumped_read = w_val;
  zmq_listener_ptr->comp_backend_ptr->isSplitPumped = w_val;
}

void MoenchZMQ::write_process_pedestal(Tango::WAttribute &attr) {
  Tango::DevBoolean w_val;
  attr.get_write_value(w_val);

  *attr_process_pedestal_read = w_val;
  zmq_listener_ptr->comp_backend_ptr->isPedestal = w_val;
}

//--------------------------------------------------------
/**
 *	Read attribute analog_img related method
 *
 *
 *	Data type:	Tango::DevFloat
 *	Attr type:	Image max = 400 x 400
 */
//--------------------------------------------------------
void MoenchZMQ::read_analog_img(Tango::Attribute &attr) {
  DEBUG_STREAM
      << "MoenchZMQ::read_analog_img(Tango::Attribute &attr) entering... "
      << std::endl;
  //	Set the attribute value
  attr.set_value(attr_analog_img_read, analog_imgAttrib::X_DATA_SIZE,
                 analog_imgAttrib::Y_DATA_SIZE);
  // push_change_event("analog_img");
}

//----------------------------------------------------	----
/**
 *	Read attribute counting_img related method
 *
 *
 *	Data type:	Tango::DevFloat
 *	Attr type:	Image max = 400 x 400
 */
//--------------------------------------------------------
void MoenchZMQ::read_counting_img(Tango::Attribute &attr) {
  DEBUG_STREAM
      << "MoenchZMQ::read_counting_img(Tango::Attribute &attr) entering... "
      << std::endl;
  //	Set the attribute value
  attr.set_value(attr_counting_img_read, counting_imgAttrib::X_DATA_SIZE,
                 counting_imgAttrib::Y_DATA_SIZE);
}

void MoenchZMQ::write_individual_frame_buffer_capacity(
    Tango::WAttribute &attr) {
  DEBUG_STREAM << "MoenchZMQ::write_individual_frame_buffer_capacity(Tango::"
                  "WAttribute &attr) entering... "
               << std::endl;
  //	Retrieve write value
  Tango::DevULong w_val;
  attr.get_write_value(w_val);
  *attr_individual_frame_buffer_capacity_read = w_val;
  zmq_listener_ptr->comp_backend_ptr->individual_frame_buffer_capacity = w_val;
}

void MoenchZMQ::read_individual_frame_buffer_capacity(Tango::Attribute &attr) {
  DEBUG_STREAM << "MoenchZMQ::read_individual_frame_buffer_capacity(Tango::"
                  "Attribute &attr) entering... "
               << std::endl;
  size_t capacity
      = zmq_listener_ptr->comp_backend_ptr->individual_frame_buffer_capacity;
  *attr_individual_frame_buffer_capacity_read
      = static_cast<Tango::DevULong>(capacity);
  attr.set_value(attr_individual_frame_buffer_capacity_read);
}

//--------------------------------------------------------
/**
 *	Method      : MoenchZMQ::add_dynamic_attributes()
 * Description:  Create the dynamic attributes if any
 *                for specified device.
 */
//--------------------------------------------------------
void MoenchZMQ::add_dynamic_attributes() {
  //	Add your own code to create and add dynamic attributes if any
}

//--------------------------------------------------------
/**
 *	Command start_receiver related method
 *
 *
 */
//--------------------------------------------------------
void MoenchZMQ::start_receiver() {
  DEBUG_STREAM << "MoenchZMQ::start_receiver()  - " << device_name
               << std::endl;

  //	Add your own code
  zmq_listener_ptr->start_receive();
  set_state(Tango::RUNNING);
}

//--------------------------------------------------------
/**
 *	Command stop_receiver related method
 *
 *
 */
//--------------------------------------------------------
void MoenchZMQ::stop_receiver() {
  DEBUG_STREAM << "MoenchZMQ::stop_receiver()  - " << device_name << std::endl;

  // wrap blocking function into lambda and then run a separate thread for it
  std::thread([&] {
    zmq_listener_ptr->stop_receive();
    copy_image_buffers();
    push_images_change();
    set_state(Tango::ON);
  }).detach();
}

//--------------------------------------------------------
/**
 *	Command abort_receiver related method
 *
 *
 */
//--------------------------------------------------------
void MoenchZMQ::abort_receiver() {
  DEBUG_STREAM << "MoenchZMQ::abort_receiver()  - " << device_name
               << std::endl;

  //	Add your own code
}

//--------------------------------------------------------
/**
 *	Command reset_pedestal related method
 *
 *
 */
//--------------------------------------------------------
void MoenchZMQ::reset_pedestal()

{
  DEBUG_STREAM << "MoenchZMQ::reset_pedestal()  - " << device_name
               << std::endl;
  zmq_listener_ptr->comp_backend_ptr->resetPedestalAndRMS();
}

//--------------------------------------------------------
/**
 *	Command push_images_change related method
 *
 *
 */
//--------------------------------------------------------
void MoenchZMQ::push_images_change() {
  DEBUG_STREAM << "MoenchZMQ::push_images_change()  - " << device_name
               << std::endl;
  push_change_event("analog_img", attr_analog_img_read,
                    analog_imgAttrib::X_DATA_SIZE,
                    analog_imgAttrib::Y_DATA_SIZE);
  push_change_event("counting_img", attr_counting_img_read,
                    counting_imgAttrib::X_DATA_SIZE,
                    counting_imgAttrib::Y_DATA_SIZE);
  push_change_event("analog_img_pumped", attr_analog_img_pumped_read,
                    analog_img_pumpedAttrib::X_DATA_SIZE,
                    analog_img_pumpedAttrib::Y_DATA_SIZE);
  push_change_event("counting_img_pumped", attr_counting_img_pumped_read,
                    counting_img_pumpedAttrib::X_DATA_SIZE,
                    counting_img_pumpedAttrib::Y_DATA_SIZE);
}

void MoenchZMQ::copy_image_buffers() {
  zmq_listener_ptr->comp_backend_ptr->analog_sum
      .copy_to_buffer<Tango::DevFloat *>(attr_analog_img_read);
  zmq_listener_ptr->comp_backend_ptr->analog_sum_pumped
      .copy_to_buffer<Tango::DevFloat *>(attr_analog_img_pumped_read);
  zmq_listener_ptr->comp_backend_ptr->counting_sum
      .copy_to_buffer<Tango::DevFloat *>(attr_counting_img_read);
  zmq_listener_ptr->comp_backend_ptr->counting_sum_pumped
      .copy_to_buffer<Tango::DevFloat *>(attr_counting_img_pumped_read);
}

//--------------------------------------------------------
/**
 *	Method      : MoenchZMQ::add_dynamic_commands()
 * Description:  Create the dynamic commands if any
 *                for specified device.
 */
//--------------------------------------------------------
void MoenchZMQ::add_dynamic_commands() {
  //	Add your own code to create and add dynamic commands if any
}

//	Additional Methods
} //	namespace
