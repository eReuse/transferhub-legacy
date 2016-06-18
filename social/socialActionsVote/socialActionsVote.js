/**
 * Created by Xavier on 06/04/2015.
 */

var SocialActions = SocialActions || {};
SocialActions.vote = SocialActions.vote || {};

/**
 * Listeners:
 * - userHasAlreadyVoted. Triggered at the page load to know if user voted before.
 *   - Boolean. Indicates if user has voted or not.
 * - voteWithFacebook. User wants to vote using Facebook account.
 * - VoteWithWebsite. User wants to vote using Site account.
 * - voteCasted. The vote has been casted. It has 2 parameters:
 *  - status
 *      - successful
 *      - fbInOtherAccount
 *      - votedTwice
 *  - typeOfVote
 *      - facebook
 *      - site
 * - FacebookCancelled
 *
 * @param domElement
 * @constructor
 */
SocialActions.vote.Vote = function(domElement){
    U.Listeners.call(this);
    this.domElement = domElement;
    this.$domElement = $(domElement);
    this.nid = $(domElement).find('.socialActionsVote').attr('data-nid');
    this.URL = '/node/' + this.nid + '/social/vote';
    this.URL2 = '/node/' + this.nid + '/social/vote';
    this.uid = Drupal.settings.social.uid;
    this.setTypeOfListeners(['UserHasAlreadyVoted','VoteWithFacebook','VoteCasted']);
    Social.Facebook.addEventListener('TriedLogin',this,this.hasUserAlreadyVoted);
    this.addEventListener('UserHasAlreadyVoted',this,this.initUi);
    this.addEventListener('VoteCasted',this,this.voteCasted);
    this.alreadyVotedA = new ClassAnimation2(this.$domElement.find('.already_voted')[0],false,'no_display invisible',false,500,0);
    this.$popups = this.$domElement.find('.popups');
    $(document).load(this.init())
};

SocialActions.vote.Vote.prototype = Object.create(U.Listeners.prototype);
SocialActions.vote.Vote.prototype.init = function(){
    this.alreadyVotedA.bind();
    var self = this;
    this.$domElement.find('#facebook_voter').click(function(){self.voteWithFacebook()});
    this.$domElement.find('#website_voter').click(function(){self.voteWithWebsite()});
    this.errorPopUp = Popup.prototype.createPopupFromDom(this.$popups.find('[id*=error]').attr('id'));
};
SocialActions.vote.Vote.prototype.getContent = function(){
    return this.$domElement.children('.content')[0]
};
SocialActions.vote.Vote.prototype.hasUserAlreadyVoted = function(params){
    var logged_in = params.success;
    if(!logged_in && Drupal.settings.social.userIsAnonymous){
        this.triggerListeners('UserHasAlreadyVoted',false);
        return
    }
    var self = this;
    var facebookId = params.facebookId;
    if(typeof facebookId  == 'undefined') facebookId = null;
    jQuery.ajax({
        method: 'GET',
        url: this.URL,
        data: {has_user_voted: true, facebook_id: facebookId},
        success: function (data) {
            data = JSON.parse(data);
            self.triggerListeners('UserHasAlreadyVoted', data);
        },
        error: function (textStatus, errorThrown) {
            throw Error('Error: ' + textStatus + ', ' + errorThrown);
        }
    });
};
SocialActions.vote.Vote.prototype.initUi = function(userHasVoted){
    if(userHasVoted) this.alreadyVotedA.ret();
    else this.showVotingButtons()
};
SocialActions.vote.Vote.prototype.showVotingButtons = function(){
    throw Error('You need to override this')
};
SocialActions.vote.Vote.prototype.hideAll = function(){
    this.alreadyVotedA.go();
    this.errorPopUp.hide();
    this.$domElement.find('.voter').hide(0);
};
SocialActions.vote.Vote.prototype.voteWithWebsite = function(){
    if(Drupal.settings.social.userIsAnonymous) alert(Drupal.t('Login or register with !site or vote with your Facebook.',{'!site':Drupal.settings.social.siteName}));
    else this.vote('site')
};
SocialActions.vote.Vote.prototype.voteWithFacebook = function() {
        if (Social.Facebook.facebookId != null) this.vote('facebook', Social.Facebook.facebookId);
        else{
            Social.Facebook.deleteEventListener('TriedLogin',this.hasUserAlreadyVoted);
            Social.Facebook.addEventListener('TriedLogin',this,this.voteWithFacebookAfterRequest);
            Social.Facebook.login();
        }
};
SocialActions.vote.Vote.prototype.voteWithFacebookAfterRequest = function(params){
        if(params.success) this.vote('facebook', params.facebookId);
        else this.showErrorPopUp(Drupal.t('You need to login and accept the application to vote.'));
        Social.Facebook.deleteEventListener('TriedLogin',this.voteWithFacebookAfterRequest);    //We remove ourselves
};
SocialActions.vote.Vote.prototype.showErrorPopUp = function(message){
        this.$popups.find('[id*=error] .message').text(message);
        this.errorPopUp.show()
};
SocialActions.vote.Vote.prototype.vote = function(typeOfVote, facebookId){
        var self = this;
        if(typeof facebookId  == 'undefined') facebookId = null;
        $.ajax({
            type: 'POST',
            url: self.URL2,
            data: {facebook_id: facebookId},
            success: function(data, textStatus){
                var status = textStatus=="success"? 'successful' : (textStatus == 403)? 'fbInOtherAccount' : 'votedTwice';
                self.triggerListeners('VoteCasted',{status: status, typeOfVote: typeOfVote})
            },
            error: function(data, textStatus, errorThrown){
                if(data.status == 409)
                    self.triggerListeners('VoteCasted', {status: 'fbInOtherAccount', typeOfVote: typeOfVote});
                else
                    self.triggerListeners('VoteCasted', {status: 'error', typeOfVote: typeOfVote});
            }
        })
};
SocialActions.vote.Vote.prototype.voteCasted = function(params){
        this.hideAll();
        if(params.status == 'successful') this.alreadyVotedA.ret();
        else if(params.status == 'fbInOtherAccount') this.showErrorPopUp(Drupal.t('This facebook account has been already used to vote with another Reutiltiza.cat account, and they are linked. Log out from Facebook o Reutilitza.cat'));
        else if(params.status == 'votedTwice') this.showErrorPopUp(Drupal.t('You cannot vote twice.'));
        else if(params.status == 'error') this.showErrorPopUp(Drupal.t('There has been an error. Please email to: x.bustamante@ereuse.org'))
};