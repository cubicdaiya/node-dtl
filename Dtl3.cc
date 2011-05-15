
#include "Dtl3.h"

Handle<Value> Dtl3::New(const Arguments& args)
{
    HandleScope scope;
    if (args.Length() < 3) {
        return ThrowException(Exception::Error(String::New("Few arguments.")));
    }
    
    if (args[0]->IsString() && args[1]->IsString() && args[2]->IsString()) {
        Dtl3 *dtl3 = new Dtl3(string(*String::Utf8Value(args[0]->ToString())),
                              string(*String::Utf8Value(args[1]->ToString())),
                              string(*String::Utf8Value(args[2]->ToString())));
        dtl3->setType(DtlTypeString);
        dtl3->Wrap(args.This());
        return args.This();
    } else if (args[0]->IsArray() && args[1]->IsArray() && args[2]->IsArray()) {
        Local<Array> a0 = Local<Array>::Cast(args[0]);
        Local<Array> a1 = Local<Array>::Cast(args[1]);
        Local<Array> a2 = Local<Array>::Cast(args[2]);
        Local<Value> val;
        if (a0->Length() == 0 && a1->Length() == 0 && a2->Length() == 0) {
            Dtl3 *dtl3 = new Dtl3("", "", "");
            dtl3->setType(DtlTypeString);
            dtl3->Wrap(args.This());
            return args.This();
        } else if (a0->Length() != 0 && a1->Length() == 0 && a2->Length() == 0) {
            val = a0->Get(Integer::New(0));
        } else if (a0->Length() == 0 && a1->Length() != 0 && a2->Length() == 0) {
            val = a1->Get(Integer::New(0));
        } else {
            val = a2->Get(Integer::New(0));
        }

        if (val->IsInt32()) {
            vector<int> seq0, seq1, seq2;
            for (int i=0;i<a0->Length();++i) {
                seq0.push_back(a0->Get(Integer::New(i))->Int32Value());
            }
            for (int i=0;i<a1->Length();++i) {
                seq1.push_back(a1->Get(Integer::New(i))->Int32Value());
            }
            for (int i=0;i<a1->Length();++i) {
                seq2.push_back(a2->Get(Integer::New(i))->Int32Value());
            }
            Dtl3 *dtl3 = new Dtl3(seq0, seq1, seq2);
            dtl3->setType(DtlTypeIntArray);
            dtl3->Wrap(args.This());
            return args.This();
        } else {
            vector<string> seq0, seq1, seq2;
            for (int i=0;i<a0->Length();++i) {
                seq0.push_back(string(*String::Utf8Value(a0->Get(Integer::New(i))->ToString())));
            }
            for (int i=0;i<a1->Length();++i) {
                seq1.push_back(string(*String::Utf8Value(a1->Get(Integer::New(i))->ToString())));
            }
            for (int i=0;i<a1->Length();++i) {
                seq2.push_back(string(*String::Utf8Value(a2->Get(Integer::New(i))->ToString())));
            }
            Dtl3 *dtl3 = new Dtl3(seq0, seq1, seq2);
            dtl3->setType(DtlTypeStringArray);
            dtl3->Wrap(args.This());
            return args.This();
        }
    }
    return ThrowException(Exception::Error(String::New("Invalid arguments.")));
}

Handle<Value> Dtl3::Compose(const Arguments& args)
{
    HandleScope scope;
    Dtl3 *dtl3 = ObjectWrap::Unwrap<Dtl3>(args.This());
    dtl3->run(DtlOperandCompose);
    return Undefined();
}

Handle<Value> Dtl3::Merge(const Arguments& args)
{
    HandleScope scope;
    Dtl3 *dtl3 = ObjectWrap::Unwrap<Dtl3>(args.This());
    bool ret;
    if (dtl3->getType() == DtlTypeStringArray) {
        ret = dtl3->vsdiff3->merge();
    } else if (dtl3->getType() == DtlTypeIntArray) {
        ret = dtl3->vidiff3->merge();
    } else {
        ret = dtl3->sdiff3->merge();
    }
    return scope.Close(Boolean::New(ret));
}

Handle<Value> Dtl3::MergedSequence(const Arguments& args)
{
    HandleScope scope;
    Dtl3 *dtl3 = ObjectWrap::Unwrap<Dtl3>(args.This());
    if (dtl3->getType() == DtlTypeStringArray) {
        vector<string> seq = dtl3->vsdiff3->getMergedSequence();
        Local<Array> ret = Array::New(seq.size());
        for (int i=0;i<seq.size();++i) {
            Local<Object> obj = Object::New();
            ret->Set(String::New(seq[i].c_str()), obj);
        }
        return scope.Close(ret);
    } else if (dtl3->getType() == DtlTypeIntArray) {
        vector<int> seq = dtl3->vidiff3->getMergedSequence();
        Local<Array> ret = Array::New(seq.size());
        for (int i=0;i<seq.size();++i) {
            Local<Object> obj = Object::New();
            ret->Set(Integer::New(seq[i]), obj);
        }
        return scope.Close(ret);
    } else {
        string seq = dtl3->sdiff3->getMergedSequence();
        return scope.Close(String::New(seq.c_str()));
    }
}

void Dtl3::setType(enum arg_type_t t)
{
    type = t;
}

enum arg_type_t Dtl3::getType()
{
    return type;
}

void Dtl3::run(enum op_t op)
{
    switch (op) {
    case DtlOperandCompose:
        if (getType() == DtlTypeStringArray) {
            vsdiff3->compose();
        } else if (getType() == DtlTypeIntArray) {
            vidiff3->compose();
        } else {
            sdiff3->compose();
        }
        break;
    case DtlOperandMerge:
        break;
    case DtlOperandMergedSequence:
        if (getType() == DtlTypeStringArray) {
            vsdiff3->getMergedSequence();
        } else if (getType() == DtlTypeIntArray) {
            vidiff3->getMergedSequence();
        } else {
            sdiff3->getMergedSequence();
        }
        break;
    case DtlOperandDestruct:
        if (getType() == DtlTypeStringArray) {
            delete vsdiff3;
        } else if (getType() == DtlTypeIntArray) {
            delete vidiff3;
        } else {
            delete sdiff3;
        }
        break;
    default :
        break;
    }
}
