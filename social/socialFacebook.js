/**
 * Created by Xavier on 08/04/2015.
 */

var Social = Social || {};

/**
 * Listeners:
 * - TriedLoggin: Triggered when has been an attemp to login.
 *   - 1st parm: boolean indicating is loggin has been successful or not
 *   - 2nd param: if 1st param is true, facebook_id
 * @constructor
 */
Social.Facebook = function(){
    U.Listeners.call(this);
    this.facebookId = null;
    var self = this;
    this.setTypeOfListeners(['TriedLogin']);
    window.fbAsyncInit = function() {
        // init the FB JS SDK
        FB.init({
            appId      : 'add the app Id',                        // App ID from the app dashboard
            status     : true,                                 // Check Facebook Login status
            xfbml      : true                                  // Look for social plugins on the page
        });
        //FB.Event.subscribe('edge.create', page_like_callback)
        //Is the user already logged in?
        FB.getLoginStatus(function(response){self.loginResponse(response)});
    };
    (function(d, s, id){
        var js, fjs = d.getElementsByTagName(s)[0];
        if (d.getElementById(id)) {return}
        js = d.createElement(s);
        js.id = id;
        js.src = "//connect.facebook.net/en_US/all.js";
        fjs.parentNode.insertBefore(js, fjs);
    }(document, 'script', 'facebook-jssdk'));
    Social.Facebook = this;
};
Social.Facebook.prototype = Object.create(U.Listeners.prototype);

Social.Facebook.prototype.loginResponse = function(response){
        if(response.status === 'connected') {
            this.facebookId = response.authResponse.userID;
            console.log('Logged in in Facebook');
            this.triggerListeners('TriedLogin', {success: true, facebookId: this.facebookId})
        }
        else this.triggerListeners('TriedLogin', {success: false})
};
/**
 * Tries to perform a login in Facebook.
 */
Social.Facebook.prototype.login = function(){
        var self = this;
        FB.login(function(response){self.loginResponse(response)})
};
Social.Facebook.prototype.getFacebookId = function(){
    return this.facebookId;
};

new Social.Facebook();

