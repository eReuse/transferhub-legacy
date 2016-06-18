/**
 * Created by Xavier on 27/12/2014.
 */
/**
 * Class Popup.
 *
 * Every instance of this class is tied to a single popup, and controls it's creation, animation,
 * hiding/showing and the events that occurs when one of the popup inner elements is triggered.
 *
 * Create the popup like this:
 * <ul>
 * <li>var myPopUpObject = Popup.prototype.createPopup(html,father);
 * Where html is the html given in Server's theme(...) (and passed through drupal.properties for example)
 * and father the father you want the popup append to.</li>
 * <li> var myPopUpObject = Popup.prototype.createPopupFromDom(id);
 * Given an already existing html given in Server's theme(..).</li>
 * </ul>
 * The popup object is tied to it's HTML DOM via the attribute data-popup and is given as the return of createPopup().
 * As it ties it to the DOM, you must use this after DOM has been loaded.
 *
 * You can add custom elements to trigger overriding the method getTriggerElementsName().
 * All the triggered elements, as default, will try to execute a method of this class called
 * triggered_identifierName where identifierName is the class HTML (but unique inside the popup) that has triggered the
 * event.
 *
 * @param id string Unique id of the popup.
 * @constructor
 */
function Popup(id){
    this.ACCEPT = 'cancel';
    this.CANCEL = 'accept';
    this.CROSS = 'cross';
    this.id = id;
    this.popup = new ClassAnimation2('#'+id,false,'invisible no_display at_top rotated',false,500,null);
}

Popup.prototype = {

    /**
     * Creates the popup.
     *
     * Adds the html to the DOM and initializes a javascript object, tiding it to the latter DOM element.
     * @param html string HTML output of theme_popup or children themes.
     * @param father string CSS selector to prepend the popup to.
     * @returns Popup The same tied DOM object that controls the popup.
     */
    createPopup : function (html,father) {
        $(father).prepend(html);
        var id = $(html).attr('id');
        return Popup.createPopupFromDom(id);
    },

    /**
     * Creates the popup.
     *
     * Differentiates from createPopup() in that createPopupFromDom doesn't add the HTML popup to the DOM.
     * @param id string Id HTML attribute to get the Popup.
     * @returns Popup The same tied DOM object that controls the popup.
     */
    createPopupFromDom: function(id){
        var popup = document.getElementById(id);
        popup['data-popup'] = new Popup(id);
        popup['data-popup']._init();
        return popup['data-popup'];
    },

    /**
     * Shows the popup with an animation.
     */
    show: function(){
        this.popup.ret();
    },

    /**
     * Hides the popup with an animation.
     */
    hide: function(){
        this.popup.go();
    },

    change: function(){
        this.popup.trigger();
    },


    /**
     * Adds the html in the webpage, so it can be shown.
     *
     * You need to execute this function before showing or hiding it.
     *
     * The webpage must be loaded.
     */
    _init: function(){
        this.popup.bind();
        this._triggerInnerElements();
    },

    /**
     * Gets an inner element. The name is one member of the class of the element looking for.
     *
     * As convection, it is supposed that this class is unique in the elements of the popup.
     * @param name String Name of a class member of the element to look for.
     * @returns {*} Jquery element.
     */
    getInnerElement: function(name){
        return $('#'+this.id+' .'+name);
    },

    existsInnerElement: function(name){
        return this.getInnerElement(name).length;
    },

    getInnerTriggerElementsName: function(){
        return [this.ACCEPT, this.CANCEL, this.CROSS];
    },

    /**
     * Adds the trigger to all the innerElements in @see getTriggerElementsName
     * @private
     */
    _triggerInnerElements: function(){
        this.getInnerTriggerElementsName().forEach(this._triggerInnerElement,this);
    },

    /**
     * Adds the trigger to an element of the popup.
     * @param name String Name of a class member of the element to look for.
     * @private
     */
    _triggerInnerElement: function(name){
        var self = this;
        if(this.existsInnerElement(name)){
            this.getInnerElement(name).click(function(){
                self.triggered(name);
            });
        }
    },

    /**
     * This method is called when any element of the popup is triggered.
     *
     * You can override it to execute a method you want all the triggers do.
     * @param name String Name of a class member of the element to look for.
     */
    triggered: function(name){
        this['triggered_'+name]();
    },

    triggered_accept: function(){
        this.hide();
    },

    triggered_cancel: function(){
        this.hide();
    },

    triggered_cross: function(){
        this.hide();
    }
};
