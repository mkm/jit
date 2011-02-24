#ifndef X86_STORAGE_H
#define X86_STORAGE_H

#include <string>
#include <map>

namespace X86 {
  class StackManager {
  public:
    StackManager();

    int stackIndex(std::string&);
    int stackSpace();

  private:
    int _lastIndex;
    std::map<std::string, int> _stackIndices;
  };
}

#endif
