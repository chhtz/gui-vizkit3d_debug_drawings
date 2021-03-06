#include "CommandDispatcherFactory.hpp"
#include "StandaloneDispatcher.hpp"
#include "ExistingWidgetDispatcher.hpp"

#ifdef USE_PORTS
  #include "PortDispatcher.hpp"
#endif

#include <stdexcept>

namespace vizkit3dDebugDrawings
{

thread_local std::shared_ptr<ICommandDispatcher> CommandDispatcherFactory::dispatcher = nullptr;
    
#ifdef USE_PORTS
void CommandDispatcherFactory::createPortDispatcher(RTT::TaskContext* taskContext)
{
    if(instanceExists())
    {
        throw std::runtime_error("vizkit3d_debug_drawings: dispatcher already created");
    }
    dispatcher.reset(new PortDispatcher(taskContext));
}
#endif

void CommandDispatcherFactory::createStandaloneDispatcher()
{
    if(instanceExists())
    {
        throw std::runtime_error("vizkit3d_debug_drawings: dispatcher already created");
    }
    dispatcher.reset(new StandaloneDispatcher());
}


void CommandDispatcherFactory::createWidgetDispatcher(vizkit3d::Vizkit3DWidget* widget)
{
    if(instanceExists())
    {
        throw std::runtime_error("vizkit3d_debug_drawings: dispatcher already created");
    }
    dispatcher.reset(new ExistingWidgetDispatcher(widget));
}

std::shared_ptr<ICommandDispatcher> CommandDispatcherFactory::getThreadLocalInstance()
{
    if(dispatcher)
    {
        return dispatcher;
    }
    throw std::runtime_error("vizkit3d_debug_drawings: Dispatcher not created.\n Are you invoking debug drawing methods from a different thread?");
}

bool CommandDispatcherFactory::instanceExists()
{
    return dispatcher != nullptr;
}


}