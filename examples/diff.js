var dtl = require('dtl')

var a    = null;
var b    = null;
var diff = null;
if (process.argv[2] === "int") {
	a = [1,2,3,4,5,6,7,8,9,10];
    b = [2,9,8,5,1,10,4,3,7,6];
} else if (process.argv[2] === "string") {
    a = ["bokko", "bokkko", "bokkkko"];
    b = ["bokkko", "bokko", "cubicdaiya"];
} else {
    a = process.argv[2];
	b = process.argv[3];
}

var diff = new dtl.Diff(a, b);
diff.compose();
console.log("editdistance:" + diff.editdistance());
//console.log("LCS:" + diff.lcs());
diff.printSES();
console.log("Unified Diff:");
diff.composeUnifiedHunks();
diff.printUnifiedFormat();
