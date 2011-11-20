
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

var correct_unihunks = [
    {
        a: 1,
        b: 3,
        c: 1,
        d: 3,
        common_prev: [ 
            { ' ': 'a' }, 
            { ' ': 'b' }
        ],
        change: [ 
            { '-': 'c' }, 
            { '+': 'd' }
        ],
        common_after: [
        ]
    }
]

exports['editdistance'] = 
    function (test) {
        test.equal(diff.editdistance(), 2);
    test.done();
    };

exports['lcs'] = 
    function (test) {
        test.equal(diff.lcs(), correct_lcs);
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
