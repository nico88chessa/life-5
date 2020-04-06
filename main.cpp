#include <configure.h>

#include <life/common/logging/Logger.hpp>


int main(MAYBE_UNUSED int argc, MAYBE_UNUSED char** argv) {

    using namespace dvlife;

    traceEnter;

    traceInfo() << "Avvio applicazione " << PROJECT_NAME;
    traceInfo() << "Versione " << PROJECT_VERSION;

    return 0;

}
