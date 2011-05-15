#ifndef NODE_DTL
#define NODE_DTL

#include <node.h>
#include <v8.h>
#include <string.h>
#include <vector>
#include <string>

using namespace v8; 
using namespace node;

#include <dtl.hpp>

using std::vector;
using std::string;

enum arg_type_t {
    DtlTypeString,
    DtlTypeStringArray,
    DtlTypeIntArray
};

enum op_t {
    DtlOperandCompose,
    DtlOperandComposeUnifiedHunks,
    DtlOperandEditdistrance,
    DtlOperandPrintSes,
    DtlOperandPrintUnifiedFormat,
    DtlOperandDestruct
};

class Dtl : ObjectWrap {
 public:
    Dtl(const string& a, const string& b)
        : sdiff(new dtl::Diff< char, string >(a, b))
    {
        // do nothing
    }
    
    Dtl(const vector<string>& a, const vector<string>& b)
        : vsdiff(new dtl::Diff< string, vector<string> >(a, b))
    {
        // do nothing
    }
    
    Dtl(const vector<int>& a, const vector<int>& b)
        : vidiff(new dtl::Diff< int, vector<int> >(a, b))
    {
        // do nothing
    }
    
    ~Dtl()
    {
        run(DtlOperandDestruct);
    }

    static Handle<Value> New(const Arguments& args);
    static Handle<Value> Compose(const Arguments& args);
    static Handle<Value> ComposeUnifiedHunks(const Arguments& args);
    static Handle<Value> Editdistance(const Arguments& args);
    static Handle<Value> PrintSes(const Arguments& args);
    static Handle<Value> PrintUnifiedFormat(const Arguments& args);
    void setType(enum arg_type_t type);
    enum arg_type_t getType();
    void run(enum op_t, long long *ed = NULL);
private:
    enum arg_type_t type;
    dtl::Diff<char,   string>          *sdiff;
    dtl::Diff<string, vector<string> > *vsdiff;
    dtl::Diff<int,    vector<int> >    *vidiff;
};

#endif // NODE_DTL
