
var dtl   = require('dtl')
var a     = [1, 2, 3, 4, 5, 6, 7, 3, 9, 10];
var b     = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10];
var c     = [1, 2, 3, 9, 5, 6, 7, 8, 9, 10];
var diff3 = new dtl.Diff3(a, b, c);
diff3.compose();
if (diff3.merge()) {
    console.log("Merged Sequence:" + diff3.mergedsequence());
} else {
    console.log("conflicted.");
}
