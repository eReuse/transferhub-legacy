/**
 * Created by Xavier on 11/03/2015.
 */

var LabelMassive = LabelMassive || {};
/**
 * @see http://tjvantoll.com/2012/06/15/detecting-print-requests-with-javascript/
 * @constructor
 */
LabelMassive.Print = function(){
    var CLASS = 'labelMassivePrintNoDisplay';
    var beforePrint = function() {
        $('*').addClass(CLASS);
        $labels = $('#labels');
        //$labels.find().concat($labels.parents().concat($labels)).removeClass(CLASS);
        $labels.removeClass(CLASS);
        $labels.find('*').removeClass(CLASS);
        $labels.parents('*').removeClass(CLASS);
        console.log('Functionality to run before printing.');
    };
    var afterPrint = function() {
        $('*').removeClass(CLASS);
        console.log('Functionality to run after printing');
    };

    if (window.matchMedia) {
        var mediaQueryList = window.matchMedia('print');
        mediaQueryList.addListener(function(mql) {
            if (mql.matches) {
                beforePrint();
            } else {
                afterPrint();
            }
        });
    }

    window.onbeforeprint = beforePrint;
    window.onafterprint = afterPrint;
};

$(document).ready(function(){
   LabelMassive.Print();
});