#ifndef NODE_DTL
#define NODE_DTL

#include <v8.h>
#include <node.h>
#include <vector>
#include <string>
#include <algorithm>

#include <dtl.hpp>

using std::vector;
using std::string;
using std::pair;

using dtl::Diff;
using dtl::Diff3;
using dtl::elemInfo;
using dtl::SES_ADD;
using dtl::SES_COMMON;
using dtl::SES_DELETE;
using dtl::uniHunk;

//using namespace v8;
using v8::Handle;
using v8::HandleScope;
using v8::Local;
using v8::Object;
using v8::Array;
using v8::Value;
using v8::String;
using v8::Integer;
using v8::Boolean;
using v8::Exception;
using v8::Arguments;
using v8::Undefined;
using v8::FunctionTemplate;


using node::ObjectWrap;

enum arg_type_t {
    DtlTypeString,
    DtlTypeStringArray,
    DtlTypeIntArray
};

enum op_t {
    DtlOperandCompose,
    DtlOperandComposeUnifiedHunks,
    DtlOperandEditdistrance,
    DtlOperandSesString,
    DtlOperandUniHunksString,
    DtlOperandPrintSes,
    DtlOperandPrintUnifiedFormat,
    DtlOperandMerge,
    DtlOperandMergedSequence,
    DtlOperandDestruct
};

#endif // NODE_DTL
