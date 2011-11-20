#include <iostream>
#include <string>

#include "dtl.h"
#include "Dtl.h"
#include "Dtl3.h"

extern "C" void
init (Handle<Object> target)
{
    HandleScope scope;
    Local<FunctionTemplate> t_diff = FunctionTemplate::New(Dtl::New);
    t_diff->InstanceTemplate()->SetInternalFieldCount(1);
    t_diff->SetClassName(String::NewSymbol("dtl"));
    
    NODE_SET_PROTOTYPE_METHOD(t_diff, "compose",             Dtl::Compose);
    NODE_SET_PROTOTYPE_METHOD(t_diff, "composeUnifiedHunks", Dtl::ComposeUnifiedHunks);
    NODE_SET_PROTOTYPE_METHOD(t_diff, "editdistance",        Dtl::Editdistance);
    NODE_SET_PROTOTYPE_METHOD(t_diff, "lcs",                 Dtl::Lcs);
    NODE_SET_PROTOTYPE_METHOD(t_diff, "ses",                 Dtl::Ses);
    NODE_SET_PROTOTYPE_METHOD(t_diff, "sesString",           Dtl::SesString);
    NODE_SET_PROTOTYPE_METHOD(t_diff, "uniHunks",            Dtl::UniHunks);
    NODE_SET_PROTOTYPE_METHOD(t_diff, "uniHunksString",      Dtl::UniHunksString);
    NODE_SET_PROTOTYPE_METHOD(t_diff, "printSES",            Dtl::PrintSes);
    NODE_SET_PROTOTYPE_METHOD(t_diff, "printUnifiedFormat",  Dtl::PrintUnifiedFormat);

    target->Set(String::New("Diff"), t_diff->GetFunction());

    Local<FunctionTemplate> t_diff3 = FunctionTemplate::New(Dtl3::New);
    t_diff3->InstanceTemplate()->SetInternalFieldCount(1);
    t_diff3->SetClassName(String::NewSymbol("dtl3"));

    NODE_SET_PROTOTYPE_METHOD(t_diff3, "compose",        Dtl3::Compose);
    NODE_SET_PROTOTYPE_METHOD(t_diff3, "merge",          Dtl3::Merge);
    NODE_SET_PROTOTYPE_METHOD(t_diff3, "mergedsequence", Dtl3::MergedSequence);

    target->Set(String::New("Diff3"), t_diff3->GetFunction());

}

NODE_MODULE(dtl, init);
