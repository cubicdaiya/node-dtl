#ifndef NODE_DTLA
#define NODE_DTLA

#include <v8.h>
#include <node.h>
#include <vector>
#include <string>

#include <dtl.hpp>

using std::vector;
using std::string;

using namespace v8;
using namespace node;

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
    DtlOperandMerge,
    DtlOperandMergedSequence,
    DtlOperandDestruct
};

#endif // NODE_DTL
