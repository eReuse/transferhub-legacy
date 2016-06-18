/**
 * Created by Xavier on 06/03/2015.
 *
 * Events:
 * - 'horizontal
 */
var LabelPersonalize = LabelPersonalize || {};

LabelPersonalize.Master = function(domElement){
    this.domElement = domElement;
    LabelPersonalize.Master = this;
};

LabelPersonalize.Master.prototype = {
    EVENTS : Object.freeze({
        WIDTH: '#width',
        HEIGHT: '#height',
        HORIZONTAL_SPACING: '#horizontal',
        VERTICAL_SPACING: '#vertical',
        LOGO: '#logo',
        BORDER: '#toggle_border',
        LINES_TITLE: '.line input',
        LINES_VALUE: '.line select'
    }),

    setEvent: function(event,callback,callbackObj){
        switch(event){
            case this.EVENTS.LOGO:
                this.logo(callback,callbackObj);
                break;
            case this.EVENTS.BORDER:
                this.border(callback,callbackObj); break;
            case this.EVENTS.LINES_TITLE:
            case this.EVENTS.LINES_VALUE:
                this.lines(event,callback,callbackObj); break;
            default:
                this.standard(event,callback,callbackObj);
        }
    },
    standard: function(eventName,callback, callbackObj){
        var self = this;
        $(this.domElement).find(eventName).change(
            function(){
                callback.call(callbackObj,self.getValue(eventName));
            });
    },
    border: function(callback, callbackObj){
        var self = this;
        $(this.domElement).find(this.EVENTS.BORDER).change(function(){
           callback.call(callbackObj,self.getValue(self.EVENTS.BORDER));
        });
    },
    lines: function(eventName,callback,callbackObj){
        $(this.domElement).find(eventName).each(function(index,element){
            var i = index;
            $(element).change(function(){
                callback.call(callbackObj,index,$(this).val());
            });
        });
    },
    logo: function(callback, callbackObj){
        $(this.domElement).find('#logo_upload').change(function () {
            if (this.files && this.files[0]) {
                var reader = new FileReader();

                reader.onload = function (e) {
                    callback.call(callbackObj,e.target.result);
                    //$('#blah').attr('src', e.target.result);
                };

                reader.readAsDataURL(this.files[0]);
            }
        });
    },
    /*
    todo LOGO and LINES* need to be implemented
     * @param eventName
     * @returns {*|jQuery}
     */
    getValue: function(event){
        switch(event){
            case this.EVENTS.LOGO:
                throw new Error('Need to implement.');
                break;
            case this.EVENTS.BORDER:
                return $(this.domElement).find(event).is(':checked');
            case this.EVENTS.LINES_TITLE:
            case this.EVENTS.LINES_VALUE:
                throw new Error('Need to implement.');
            default:
                return $(this.domElement).find(event).val();
        }
    }
};
