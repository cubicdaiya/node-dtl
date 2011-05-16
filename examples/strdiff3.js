

if (process.argv.length < 5) {
    console.log("few arugments.");
    process.exit();
}

var dtl   = require('dtl')
var a     = process.argv[2];
var b     = process.argv[3];
var c     = process.argv[4];
var diff3 = new dtl.Diff3(a, b, c);
diff3.compose();
if (diff3.merge()) {
    console.log("Merged Sequence:" + diff3.mergedsequence());
} else {
    console.log("conflicted.");
}
