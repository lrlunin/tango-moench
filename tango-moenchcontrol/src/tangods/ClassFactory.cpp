#include "MoenchControlClass.h"
#include <tango/tango.h>

//	Add class header files if needed

/**
 *	Create MoenchControl Class singleton and store it in DServer object.
 */

void Tango::DServer::class_factory() {
  //	Add method class init if needed
  add_class(MoenchControl_ns::MoenchControlClass::init("MoenchControl"));
}
