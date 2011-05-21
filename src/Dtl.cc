
#include "Dtl.h"

#include <sstream>

using std::stringstream;

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
            for (size_t i=0;i<a0->Length();++i) {
                seq0.push_back(a0->Get(Integer::New(i))->Int32Value());
            }
            for (size_t i=0;i<a1->Length();++i) {
                seq1.push_back(a1->Get(Integer::New(i))->Int32Value());
            }
            Dtl *dtl = new Dtl(seq0, seq1);
            dtl->setType(DtlTypeIntArray);
            dtl->Wrap(args.This());
            return args.This();
        } else {
            vector<string> seq0, seq1;
            for (size_t i=0;i<a0->Length();++i) {
                seq0.push_back(string(*String::Utf8Value(a0->Get(Integer::New(i))->ToString())));
            }
            for (size_t i=0;i<a1->Length();++i) {
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
    return dtl->run(DtlOperandCompose, scope);
}

Handle<Value> Dtl::ComposeUnifiedHunks(const Arguments& args)
{
    HandleScope scope;
    Dtl *dtl = ObjectWrap::Unwrap<Dtl>(args.This());
    dtl->run(DtlOperandComposeUnifiedHunks, scope);
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

Handle<Value> Dtl::Lcs(const Arguments& args)
{
    HandleScope scope;
    Dtl *dtl = ObjectWrap::Unwrap<Dtl>(args.This());
    if (dtl->getType() == DtlTypeStringArray) {
        vector<string> lcs_v = dtl->vsdiff->getLcsVec();
        Local<Array> ret = Array::New(lcs_v.size());
        for (size_t i=0;i<lcs_v.size();++i) {
            ret->Set(Integer::New(i), String::New(lcs_v[i].c_str()));
        }
        return scope.Close(ret);
    } else if (dtl->getType() == DtlTypeIntArray) {
        vector<int> lcs_v = dtl->vidiff->getLcsVec();
        Local<Array> ret = Array::New(lcs_v.size());
        for (size_t i=0;i<lcs_v.size();++i) {
            ret->Set(Integer::New(i), Integer::New(lcs_v[i]));
        }
        return scope.Close(ret);
    } else {
        vector<char> lcs_v = dtl->sdiff->getLcsVec();
        string lcs_s(lcs_v.begin(), lcs_v.end());
        return scope.Close(String::New(lcs_s.c_str()));
    }
}

Handle<Value> Dtl::Ses(const Arguments& args)
{
    HandleScope scope;
    Dtl *dtl = ObjectWrap::Unwrap<Dtl>(args.This());

    string mark_add, mark_del, mark_common;
    if (args.Length() == 1) {
        Local<Array> a = Local<Array>::Cast(args[0]);
        mark_add    = string(*String::Utf8Value(a->Get(String::New("add"))->ToString()));
        mark_del    = string(*String::Utf8Value(a->Get(String::New("del"))->ToString()));
        mark_common = string(*String::Utf8Value(a->Get(String::New("common"))->ToString()));
    } else {
        mark_add    = string(SES_MARK_ADD);
        mark_del    = string(SES_MARK_DELETE);
        mark_common = string(SES_MARK_COMMON);
    }

    if (dtl->getType() == DtlTypeStringArray) {
        dtl::Ses< string > ses = dtl->vsdiff->getSes();
        vector< pair< string, elemInfo > > ses_v = ses.getSequence();
        Local<Array> ret = Array::New(ses_v.size());
        for (size_t i=0;i<ses_v.size();++i) {
            Local<Object> e = Object::New();
            switch (ses_v[i].second.type) {
            case SES_ADD:
                e->Set(String::New(mark_add.c_str()), String::New(ses_v[i].first.c_str()));
                break;
            case SES_DELETE:
                e->Set(String::New(mark_del.c_str()), String::New(ses_v[i].first.c_str()));
                break;
            case SES_COMMON:
                e->Set(String::New(mark_common.c_str()), String::New(ses_v[i].first.c_str()));
                break;
            }
            ret->Set(Integer::New(i), e);
        }
        return ret;
    } else if (dtl->getType() == DtlTypeIntArray) {
        dtl::Ses< int > ses = dtl->vidiff->getSes();
        vector< pair< int, elemInfo > > ses_v = ses.getSequence();
        Local<Array> ret = Array::New(ses_v.size());
        for (size_t i=0;i<ses_v.size();++i) {
            Local<Object> e = Object::New();
            switch (ses_v[i].second.type) {
            case SES_ADD:
                e->Set(String::New(mark_add.c_str()), Integer::New(ses_v[i].first));
                break;
            case SES_DELETE:
                e->Set(String::New(mark_del.c_str()), Integer::New(ses_v[i].first));
                break;
            case SES_COMMON:
                e->Set(String::New(mark_common.c_str()), Integer::New(ses_v[i].first));
                break;
            }
            ret->Set(Integer::New(i), e);
        }
        return ret;
    } else {
        dtl::Ses< char > ses = dtl->sdiff->getSes();
        vector< pair< char, elemInfo > > ses_v = ses.getSequence();
        Local<Array> ret = Array::New(ses_v.size());
        for (size_t i=0;i<ses_v.size();++i) {
            Local<Object> e = Object::New();
            char s[2];
            s[0] = ses_v[i].first;
            s[1] = '\0';
            switch (ses_v[i].second.type) {
            case SES_ADD:
                e->Set(String::New(mark_add.c_str()), String::New(s));
                break;
            case SES_DELETE:
                e->Set(String::New(mark_del.c_str()), String::New(s));
                break;
            case SES_COMMON:
                e->Set(String::New(mark_common.c_str()), String::New(s));
                break;
            }
            ret->Set(Integer::New(i), e);
        }
        return ret;
    }
    return Undefined();
}

Handle<Value> Dtl::SesString(const Arguments& args)
{
    HandleScope scope;
    Dtl *dtl = ObjectWrap::Unwrap<Dtl>(args.This());
    return dtl->run(DtlOperandSesString, scope);
}

Handle<Value> Dtl::UniHunksString(const Arguments& args)
{
    HandleScope scope;
    Dtl *dtl = ObjectWrap::Unwrap<Dtl>(args.This());
    return dtl->run(DtlOperandUniHunksString, scope);
}

Handle<Value> Dtl::PrintSes(const Arguments& args)
{
    HandleScope scope;
    Dtl *dtl = ObjectWrap::Unwrap<Dtl>(args.This());
    return dtl->run(DtlOperandPrintSes, scope);
}

Handle<Value> Dtl::PrintUnifiedFormat(const Arguments& args)
{
    HandleScope scope;
    Dtl *dtl = ObjectWrap::Unwrap<Dtl>(args.This());
    return dtl->run(DtlOperandPrintUnifiedFormat, scope);
}

void Dtl::setType(enum arg_type_t t)
{
    type = t;
}

enum arg_type_t Dtl::getType()
{
    return type;
}

Handle<Value> Dtl::run(enum op_t op, HandleScope & scope)
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
    case DtlOperandSesString:
        {
            stringstream os;
            if  (getType() == DtlTypeStringArray) {
                vsdiff->printSES< stringstream >(os);
            } else if (getType() == DtlTypeIntArray) {
                vidiff->printSES< stringstream >(os);
            } else {
                sdiff->printSES< stringstream >(os);
            }
            return scope.Close(String::New(os.str().c_str()));
        }
        break;
    case DtlOperandUniHunksString:
        {
            stringstream os;
            if (getType() == DtlTypeStringArray) {
                vsdiff->printUnifiedFormat< stringstream >(os);
            } else if (getType() == DtlTypeIntArray) {
                vidiff->printUnifiedFormat< stringstream >(os);
            } else {
                sdiff->printUnifiedFormat< stringstream >(os);
            }
            return scope.Close(String::New(os.str().c_str()));
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
    return Undefined();
}
