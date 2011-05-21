
var dtl  = require('dtl');
var diff = new dtl.Diff("abc", "abd");
diff.compose();
diff.composeUnifiedHunks();

var correct_lcs = "ab";

var correct_ses = [ 
    { ' ' : 'a' },
    { ' ' : 'b' },
    { '-' : 'c' },
    { '+' : 'd' } 
];

exports['editdistance'] = 
    function (test) {
        test.equal(diff.editdistance(), 2);
	test.done();
    };
exports['lcs'] = 
    function (test) {
        test.deepEqual(diff.lcs(), correct_lcs);
	test.done();
    };

exports['ses'] = 
    function (test) {
        test.deepEqual(correct_ses, diff.ses());
	test.done();
    };
