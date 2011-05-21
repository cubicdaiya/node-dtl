
var dtl  = require('dtl');
var diff = new dtl.Diff("abc", "abd");
diff.compose();
diff.composeUnifiedHunks();

var correct_ses = [ 
    { ' ' : 'a' },
    { ' ' : 'b' },
    { '-' : 'c' },
    { '+' : 'd' } 
];

exports['strdiff'] = 
	function (test) {
            test.equal(diff.editdistance(), 2);
	    test.equal(diff.lcs(), "ab");
	    test.deepEqual(correct_ses, diff.ses());
            test.done();
	};
