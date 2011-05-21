
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

exports['intdiff'] = 
    function (test) {
        test.equal(diff.editdistance(), 2);
        test.deepEqual(diff.lcs(), correct_lcs);
        test.deepEqual(correct_ses, diff.ses());
        test.done();
    };
