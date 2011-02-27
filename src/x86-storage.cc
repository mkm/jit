#include "x86-storage.hh"

namespace X86 {
  StackManager::StackManager() :
    _lastIndex(0),
    _stackIndices()
  {

  }

  int StackManager::stackIndex(const std::string& name) {
    std::map<std::string, int>::const_iterator it = _stackIndices.find(name);
    if (it == _stackIndices.end()) {
      _lastIndex -= 4;
      _stackIndices[name] = _lastIndex;
      return _lastIndex;
    } else {
      return (*it).second;
    }
  }

  int StackManager::stackSpace() {
    return -_lastIndex;
  }
}
