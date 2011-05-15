var dtl = require('dtl')

var a    = null;
var b    = null;
var c    = null;
var diff = null;
if (process.argv[2] === "int") {
    a = [1, 2, 3, 4, 5, 6, 7, 3, 9, 10];
    b = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10];
    c = [1, 2, 3, 9, 5, 6, 7, 8, 9, 10];
} else if (process.argv[2] === "string") {
    a = ["bokkko",     "bokko", "bokkkko"];
    b = ["cubicdaiya", "bokko", "bokkkko"];
    b = ["bokkkko",    "bokko", "cubicdaiya"];
} else {
    a = process.argv[2];
	b = process.argv[3];
	c = process.argv[4];
}

var diff3 = new dtl.Diff3(a, b, c);
diff3.compose();
diff3.merge();
console.log("Merged Sequence:" + diff3.mergedsequence());
