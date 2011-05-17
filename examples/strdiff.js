
if (process.argv.length < 4) {
    console.log("few arugments.");
    process.exit();
}

var a    = process.argv[2];
var b    = process.argv[3];
var dtl  = require('dtl');
var diff = new dtl.Diff(a, b);

diff.compose();
console.log("editdistance:" + diff.editdistance());
console.log("lcs:" + diff.lcs());
console.log("ses:");
diff.printSES();
console.log("Unified Diff:");
diff.composeUnifiedHunks();
diff.printUnifiedFormat();
