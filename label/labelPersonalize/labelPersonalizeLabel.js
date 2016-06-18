/**
 * Created by Xavier on 06/03/2015.
 */

var LabelPersonalize = LabelPersonalize || {};

LabelPersonalize.Label = function(domElement, master, index){
    this.INDEX_OF_TRIAL_QR = 0;
    this.domElement = domElement;
    this.master = master;
    this.index = index;
    this.init();
};


LabelPersonalize.Label.prototype = {
    init: function(){
        this.master.setEvent(this.master.EVENTS.WIDTH,this.width,this);
        this.master.setEvent(this.master.EVENTS.HEIGHT,this.height,this);
        this.master.setEvent(this.master.EVENTS.HORIZONTAL_SPACING,this.horizontalSpacing,this);
        this.master.setEvent(this.master.EVENTS.VERTICAL_SPACING,this.verticalSpacing,this);
        this.master.setEvent(this.master.EVENTS.LOGO,this.logo,this);
        this.master.setEvent(this.master.EVENTS.BORDER,this.border,this);
        if(this.index != this.INDEX_OF_TRIAL_QR) {
            this.master.setEvent(this.master.EVENTS.LINES_TITLE, this.lines_title, this);
            this.master.setEvent(this.master.EVENTS.LINES_VALUE, this.lines_value, this);
        }
    },
    
    width: function(value){
        this.css('width',value + 'mm')
    },
    height: function(value){this.css('height',value + 'mm')},
    logo: function(value){
        $(this.domElement).find('.logo img').attr('src',value);
    },
    horizontalSpacing: function(value){
        this.css('margin-right',value + 'mm');
    },
    verticalSpacing: function(value){
        this.css('margin-top',value + 'mm');
    },
    lines_title: function(index, value){
        $(this.domElement).find('.title').eq(index).text(value);
    },
    lines_value: function(index, value){
        $(this.domElement).find('.text').eq(index).text($(this.domElement).attr('data-' + value));
    },
    border: function(value){
        if(value) $(this.domElement).css('border','0.7mm dashed grey');
        else $(this.domElement).css('border','none');
    },
    attr: function(type,value){
        $(this.domElement).attr(type,value);
    },
    css: function(name,value){
        $(this.domElement).css(name,value);
    }
};