#include "OpenShmemChecker.h"

using namespace clang;
using namespace ento;

namespace clang{
namespace ento{
/**
 * @brief OpenShmem specific implementation of a get handler
 *
 * @param handler
 * @param Call
 * @param C
 */



// void shmemGetHandler(int handler, const CallEvent &Call, CheckerContext &C) {

//   if (Call.getNumArgs() < 1)
//     return;

//   // TODO: remove the harcoding of variable index;

//   SymbolRef symmetricVariable = Call.getArgSVal(0).getAsSymbol();

//   if (!symmetricVariable)
//     return;

//   // TODO: extract this out of the function
//   ProgramStateRef State = C.getState();

//   const RefState *SS = State->get<CheckerState>(symmetricVariable);

//   if (!SS) {
//     // TODOS: replace couts with bug reports
//     std::cout << ErrorMessages::VARIABLE_NOT_SYMMETRIC;
//     return;
//   }

//   // complain if an access it made to the freed variables
//   if (State->contains<FreedVariables>(symmetricVariable)) {
//     // TODOS: replace couts with bug reports
//     std::cout << ErrorMessages::ACCESS_FREED_VARIABLE;
//     return;
//   }

//   DefaultHandlers::handleReads(handler, Call, C);
// }

/**
 * @brief Provide implementation of routine types
 *
 * @return routineHandlers
 */
 routineHandlers addHandlers() {
  routineHandlers handlers;

  handlers.emplace(OpenShmemConstants::SHMEM_MALLOC,
                   std::make_pair(MEMORY_ALLOC, (Handler)NULL));
  handlers.emplace(OpenShmemConstants::SHMEM_FREE,
                   std::make_pair(MEMORY_DEALLOC, (Handler)NULL));
  handlers.emplace(OpenShmemConstants::SHMEM_BARRIER,
                   std::make_pair(SYNCHRONIZATION, (Handler)NULL));
  handlers.emplace(OpenShmemConstants::SHMEM_PUT,
                   std::make_pair(NON_BLOCKING_WRITE, (Handler)NULL));
  handlers.emplace(OpenShmemConstants::SHMEM_GET,
                   std::make_pair(READ_FROM_MEMORY,  (Handler)NULL));
  handlers.emplace(OpenShmemConstants::SHMEM_FINALIZE,
                   std::make_pair(FINAL_CALL,  (Handler)NULL));

  return handlers;
}
}
}

OpenSHMEMChecker::OpenSHMEMChecker(routineHandlers (*addHandlers)()):PGASChecker((addHandlers)){

}


/**
 * @brief Register the new checker
 *
 * @param mgr
 */
void ento::registerOpenSHMEMChecker(CheckerManager &mgr) {
  mgr.registerChecker<clang::ento::OpenSHMEMChecker, routineHandlers (*)()>(addHandlers);
}

bool ento::shouldRegisterOpenSHMEMChecker(const LangOptions &LO) {
  return true;
}

