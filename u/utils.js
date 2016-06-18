/**
 * Created by Xavier on 08/04/2015.
 */
var U = U || {};
U.Listeners = function(){};

U.Listeners.prototype.setTypeOfListeners = function(types){
    this.u_listeners = {};
    for(var i = 0; i < types.length; i++)
        this.u_listeners[types[i]] = []
};

U.Listeners.prototype.addEventListener = function(type,that,listener){
    this.u_listeners[type].push({that: that, listener:listener})
};
U.Listeners.prototype.triggerListeners = function(type,params){
    for(var i = 0; i < this.u_listeners[type].length; i++)
        this.u_listeners[type][i].listener.call(this.u_listeners[type][i].that,params)
};
/**
 * Deltes the first instance of the listener in type
 * @param type
 * @param listener
 */
U.Listeners.prototype.deleteEventListener = function(type,listener){
    for(var i = 0; i < this.u_listeners[type].length; i++)
        if(this.u_listeners[type][i].listener == listener)
            this.u_listeners[type].splice(i,1)
};