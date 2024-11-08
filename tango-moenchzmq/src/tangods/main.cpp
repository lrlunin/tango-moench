#include <tango/tango.h>

#if defined(ENABLE_CRASH_REPORT)
#include <crashreporting/crash_report.h>
#else
#define DECLARE_CRASH_HANDLER
#define INSTALL_CRASH_HANDLER
#endif

DECLARE_CRASH_HANDLER

int main(int argc, char *argv[]) {
  INSTALL_CRASH_HANDLER
  Tango::Util *tg;
  try {
    // Initialise the device server
    //----------------------------------------
    tg = Tango::Util::init(argc, argv);

    // Create the device server singleton
    //	which will create everything
    //----------------------------------------
    tg->server_init(false);

    // Run the endless loop
    //----------------------------------------
    std::cout << "Ready to accept request" << std::endl;
    tg->server_run();
  } catch (std::bad_alloc &) {
    std::cout << "Can't allocate memory to store device object !!!"
              << std::endl;
    std::cout << "Exiting" << std::endl;
  } catch (CORBA::Exception &e) {
    Tango::Except::print_exception(e);

    std::cout << "Received a CORBA_Exception" << std::endl;
    std::cout << "Exiting" << std::endl;
  }

  if (tg) {
    tg->server_cleanup();
  }
  return (0);
}
