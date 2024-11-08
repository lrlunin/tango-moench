#include "MoenchZMQClass.h"
#include <tango/tango.h>

void Tango::DServer::class_factory() {
  //	Add method class init if needed
  add_class(MoenchZMQ_ns::MoenchZMQClass::init("MoenchZMQ"));
}
