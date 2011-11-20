
var dtl  = require('dtl');
var diff = new dtl.Diff([1,2,3], [1,2,5]);
diff.compose();
diff.composeUnifiedHunks();

var correct_lcs = [1,2];

var correct_ses = [ 
    { ' ' : 1 },
    { ' ' : 2 },
    { '-' : 3 },
    { '+' : 5 } 
];

var correct_unihunks = [
    {
        a: 1,
        b: 3,
        c: 1,
        d: 3,
        common_prev: [ 
            { ' ': 1 }, 
            { ' ': 2 }
        ],
        change: [ 
            { '-': 3 },
            { '+': 5 }
        ],
        common_after: [

        ] 
    }
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

exports['unihunks'] = 
    function (test) {
        test.deepEqual(correct_unihunks, diff.uniHunks());
    test.done();
    };
