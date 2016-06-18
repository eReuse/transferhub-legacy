
/**
 * Created by Xavier on 10/03/2015.
 */
var LabelPersonalize = LabelPersonalize || {};

LabelPersonalize.Range = function(domElement, master){
    this.$domElement = $(domElement);
    this.master = master;
    this.init();
};

LabelPersonalize.Range.prototype = {
    init: function(){
        var selfEvent = this.getOwnEvent();
        this.master.setEvent(selfEvent,this.setValue,this);
        //var sibling = jQuery.parseHTML("<span class='range_value'></span>");
        var sibling = document.createElement('span');
        sibling.setAttribute('class','range_value');
        this.$domElement.after(sibling);
        this.$sibling = $(sibling);
        this.setValue(this.master.getValue(selfEvent));
    },
    getOwnEvent: function(){
        switch(this.$domElement.attr('id')){
            case 'horizontal': return this.master.EVENTS.HORIZONTAL_SPACING;
            case 'vertical': return this.master.EVENTS.VERTICAL_SPACING;
            case 'width': return this.master.EVENTS.WIDTH;
            case 'height': return this.master.EVENTS.HEIGHT;
        }
    },
    setValue: function (value) {
        this.$sibling.text(value + 'mm');
    }
};