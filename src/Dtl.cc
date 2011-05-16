
#include "Dtl.h"

Handle<Value> Dtl::New(const Arguments& args)
{
    HandleScope scope;
    if (args.Length() < 2) {
        return ThrowException(Exception::Error(String::New("Few arguments.")));
    }
    
    if (args[0]->IsString() && args[1]->IsString()) {
        Dtl *dtl = new Dtl(string(*String::Utf8Value(args[0]->ToString())),
                           string(*String::Utf8Value(args[1]->ToString())));
        dtl->setType(DtlTypeString);
        dtl->Wrap(args.This());
        return args.This();
    } else if (args[0]->IsArray() && args[1]->IsArray()) {
        Local<Array> a0 = Local<Array>::Cast(args[0]);
        Local<Array> a1 = Local<Array>::Cast(args[1]);
        Local<Value> val;
        if (a0->Length() == 0 && a1->Length() == 0) {
            Dtl *dtl = new Dtl("", "");
            dtl->setType(DtlTypeString);
            dtl->Wrap(args.This());
            return args.This();
        } else if (a0->Length() != 0 && a1->Length() == 0) {
            val = a0->Get(Integer::New(0));
        } else {
            val = a1->Get(Integer::New(0));
        }

        if (val->IsInt32()) {
            vector<int> seq0, seq1;
            for (int i=0;i<a0->Length();++i) {
                seq0.push_back(a0->Get(Integer::New(i))->Int32Value());
            }
            for (int i=0;i<a1->Length();++i) {
                seq1.push_back(a1->Get(Integer::New(i))->Int32Value());
            }
            Dtl *dtl = new Dtl(seq0, seq1);
            dtl->setType(DtlTypeIntArray);
            dtl->Wrap(args.This());
            return args.This();
        } else {
            vector<string> seq0, seq1;
            for (int i=0;i<a0->Length();++i) {
                seq0.push_back(string(*String::Utf8Value(a0->Get(Integer::New(i))->ToString())));
            }
            for (int i=0;i<a1->Length();++i) {
                seq1.push_back(string(*String::Utf8Value(a1->Get(Integer::New(i))->ToString())));
            }
            Dtl *dtl = new Dtl(seq0, seq1);
            dtl->setType(DtlTypeStringArray);
            dtl->Wrap(args.This());
            return args.This();
        }
    }
    return ThrowException(Exception::Error(String::New("Invalid arguments.")));
}

Handle<Value> Dtl::Compose(const Arguments& args)
{
    HandleScope scope;
    Dtl *dtl = ObjectWrap::Unwrap<Dtl>(args.This());
    dtl->run(DtlOperandCompose);
    return Undefined();
}

Handle<Value> Dtl::ComposeUnifiedHunks(const Arguments& args)
{
    HandleScope scope;
    Dtl *dtl = ObjectWrap::Unwrap<Dtl>(args.This());
    dtl->run(DtlOperandComposeUnifiedHunks);
    return Undefined();
}

Handle<Value> Dtl::Editdistance(const Arguments& args)
{
    HandleScope scope;
    Dtl *dtl = ObjectWrap::Unwrap<Dtl>(args.This());
    long long ed;
    if (dtl->getType() == DtlTypeStringArray) {
        ed = dtl->vsdiff->getEditDistance();
    } else if (dtl->getType() == DtlTypeIntArray) {
        ed = dtl->vidiff->getEditDistance();
    } else {
        ed = dtl->sdiff->getEditDistance();
    }
    return scope.Close(Integer::New(ed));
}

Handle<Value> Dtl::PrintSes(const Arguments& args)
{
    HandleScope scope;
    Dtl *dtl = ObjectWrap::Unwrap<Dtl>(args.This());
    dtl->run(DtlOperandPrintSes);
    return Undefined();
}

Handle<Value> Dtl::PrintUnifiedFormat(const Arguments& args)
{
    HandleScope scope;
    Dtl *dtl = ObjectWrap::Unwrap<Dtl>(args.This());
    dtl->run(DtlOperandPrintUnifiedFormat);
    return Undefined();
}

void Dtl::setType(enum arg_type_t t)
{
    type = t;
}

enum arg_type_t Dtl::getType()
{
    return type;
}

void Dtl::run(enum op_t op)
{
    switch (op) {
    case DtlOperandCompose:
        if (getType() == DtlTypeStringArray) {
            vsdiff->compose();
        } else if (getType() == DtlTypeIntArray) {
            vidiff->compose();
        } else {
            sdiff->compose();
        }
        break;
    case DtlOperandComposeUnifiedHunks:
        if (getType() == DtlTypeStringArray) {
            vsdiff->composeUnifiedHunks();
        } else if (getType() == DtlTypeIntArray) {
            vidiff->composeUnifiedHunks();
        } else {
            sdiff->composeUnifiedHunks();
        }
        break;
    case DtlOperandPrintSes:
        if (getType() == DtlTypeStringArray) {
            vsdiff->printSES();
        } else if (getType() == DtlTypeIntArray) {
            vidiff->printSES();
        } else {
            sdiff->printSES();
        }
        break;
    case DtlOperandPrintUnifiedFormat:
        if (getType() == DtlTypeStringArray) {
            vsdiff->printUnifiedFormat();
        } else if (getType() == DtlTypeIntArray) {
            vidiff->printUnifiedFormat();
        } else {
            sdiff->printUnifiedFormat();
        }
        break;
    case DtlOperandDestruct:
        if (getType() == DtlTypeStringArray) {
            delete vsdiff;
        } else if (getType() == DtlTypeIntArray) {
            delete vidiff;
        } else {
            delete sdiff;
        }
        break;
    default :
        break;
    }
}
