
var a    = [1,2,3,4,5,6,7,8,9,10];
var b    = [2,9,8,5,1,10,4,3,7,6];
var dtl  = require('dtl');
var diff = new dtl.Diff(a, b);

diff.compose();
console.log("editdistance:" + diff.editdistance());
diff.printSES();
console.log("Unified Diff:");
diff.composeUnifiedHunks();
diff.printUnifiedFormat();

