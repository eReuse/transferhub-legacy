/**
 * Created by Xavier on 27/12/2014.
 */
/**
 * Class Fullscreen (popup).
 *
 * Generates a popup that impacts on user, making all the screen darker.
 *
 * You can extend and override this to change behaviour or implement custom one.
 *
 * @see PHP theme_fullscreen() for more info.
 * @see Popup for more info.
 *
 * @param id string Unique id of the popup.
 */
function Fullscreen(id){
    Popup.call(this,id);
    this.father = 'body';
    this.OFFSET = 'offset';
    this.OFFSET_ID = 'fullscreen_offset';
}

Fullscreen.prototype = Object.create(Popup.prototype);

Fullscreen.prototype.offsetCreated = false;

Fullscreen.prototype.constructor = Fullscreen;

Fullscreen.prototype.createPopupFromDom = function(id){
    var popup = document.getElementById(id);
    popup['data-popup'] = new Fullscreen(id);
    popup['data-popup']._init();
    return popup['data-popup'];
};

Fullscreen.prototype.show = function(){
    this.getOffset().addClass('fullscreen-offset-full');
    Popup.prototype.show.call(this);
};

Fullscreen.prototype.hide = function(){
    this.getOffset().removeClass('fullscreen-offset-full');
    Popup.prototype.hide.call(this);
};

Fullscreen.prototype.change = function(){
    this.getOffset().toggleClass('fullscreen-offset-full');
    Popup.prototype.change.call(this);
};

Fullscreen.prototype.createPopup = function (html,father) {
    $(father).prepend(html);
    var id = $(html).attr('id');
    return Fullscreen.createPopupFromDom(id);
};

Fullscreen.prototype._init = function(){
    if(!this.offsetCreated) {
        $('body').prepend(this.getOffsetHtml());
        var self = this;
        this.getOffset().click(function(){
           self.triggered_offset();
        });
        this.offsetCreated = true;
    }
    Popup.prototype._init.call(this);
};

Fullscreen.prototype.triggered_offset = function(){
    var $actualFullscreen = this.getVisibleFullscreen();
    var actualFullscreen = $actualFullscreen[0];
    actualFullscreen['data-popup'].hide();
};

Fullscreen.prototype.getVisibleFullscreen = function(){
    var $actualFullscreen = $('.fullscreen:not(.no_display)');
    if($actualFullscreen.length > 1) throw 'There are more than one fullscreen active';
    else if($actualFullscreen.length == 0) throw 'There is no any fullscreen active';
    return $actualFullscreen;
};

Fullscreen.prototype.getOffsetHtml = function(){
    return '<div id="'+this.OFFSET_ID+'"/>'
};

Fullscreen.prototype.getOffset = function(){
    return $('#'+this.OFFSET_ID);
};