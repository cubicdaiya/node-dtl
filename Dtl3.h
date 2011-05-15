#ifndef NODE_DTL3_CLASS_H
#define NODE_DTL3_CLASS_H

#include "dtl.h"

class Dtl3 : ObjectWrap
{
public:
    typedef vector<string> strVec;
    typedef vector<int>    intVec;
    Dtl3(const string& a, const string& b, const string& c)
        : sdiff3(new dtl::Diff3< char, string >(a, b, c))
    {
        // do nothing
    }
    
    Dtl3(const strVec& a, const strVec& b, const strVec& c)
        : vsdiff3(new dtl::Diff3< string, strVec >(a, b, c))
    {
        // do nothing
    }
    
    Dtl3(const intVec& a, const intVec& b, const intVec& c)
        : vidiff3(new dtl::Diff3< int, intVec >(a, b, c))
    {
        // do nothing
    }
    
    ~Dtl3()
    {
        run(DtlOperandDestruct);
    }
    static Handle<Value> New(const Arguments& args);
    static Handle<Value> Compose(const Arguments& args);
    static Handle<Value> Merge(const Arguments& args);
    static Handle<Value> MergedSequence(const Arguments& args);
    void setType(enum arg_type_t type);
    enum arg_type_t getType();
    void run(enum op_t);
private:
    enum arg_type_t type;
    dtl::Diff3<char,   string > *sdiff3;
    dtl::Diff3<string, strVec > *vsdiff3;
    dtl::Diff3<int,    intVec > *vidiff3;
};

#endif // NODE_DTL3_CLASS_H
