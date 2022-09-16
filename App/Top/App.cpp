
#include <Os/Log.hpp>
#include <App/Top/AppTopologyAc.hpp>
#include "App.hpp"
App::TopologyState state;
// Enable the console logging provided by Os::Log
Os::Log logger;


namespace Ref {
    void Initialize(const char *hostname, uint32_t port_number) {

        state = App::TopologyState(hostname, port_number);
        App::setup(state);
        
    }
    void Deinitialize() {

    }
    void run_one_cycle() {
    
        App::blockDrv.callIsr();
        Os::Task::delay(1000); //1Hz
    }
}