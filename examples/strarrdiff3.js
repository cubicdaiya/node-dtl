
var dtl   = require('dtl')
var a     = ["cubicdaiya", "bokko", "bokkkko"];
var b     = ["bokkko",     "bokko", "bokkkko"];
var c     = ["bokkko",     "bokko", "cubicdaiya"];
var diff3 = new dtl.Diff3(a, b, c);
diff3.compose();
if (diff3.merge()) {
    console.log("Merged Sequence:" + diff3.mergedsequence());
} else {
    console.log("conflicted.");
}
