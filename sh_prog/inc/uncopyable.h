#ifndef UNCOPYABLE_H_
#define UNCOPYABLE_H_

namespace alexei_prog_snob {

class uncopyable_class {
protected:                  // allow construction
    uncopyable_class() {}   // and destruction of 
    ~uncopyable_class() {}  // derived objects... 
private:                    // but prevent copying
    uncopyable_class(const uncopyable_class&);
    uncopyable_class& operator=(const uncopyable_class&);
};

} // end namespace alexei_prog_snob

#endif /* UNCOPYABLE_H_ */