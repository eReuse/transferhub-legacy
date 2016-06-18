/**
 * Created by Xavier on 09/03/2015.
 */



$(document).ready(function(){
    var $master = $('#labelPersonalize');
    var instance = new LabelPersonalize.Master($master);
    LabelPersonalize.label = [];
    $('.label').each(function(index,element){

        LabelPersonalize.label.push(new LabelPersonalize.Label(element, instance, index));
    });
    LabelPersonalize.range = [];
   $master.find('input[type=range]').each(function(index,element){

        LabelPersonalize.range.push(new LabelPersonalize.Range(element, instance));
   });
});