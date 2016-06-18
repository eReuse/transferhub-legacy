/**
 * Created by Xavier on 06/04/2015.
 */

var SocialActions = SocialActions || {};
SocialActions.vote = SocialActions.vote || {};

SocialActions.vote.VoteSmall = function(domElement){
    SocialActions.vote.elements = SocialActions.Vote.elements || {};
    SocialActions.vote.elements.small = SocialActions.Vote.elements.small || [];
    SocialActions.vote.elements.small.push(this);
    SocialActions.vote.Vote.call(this,domElement);
};

SocialActions.vote.VoteSmall.prototype = Object.create(SocialActions.vote.Vote.prototype);
SocialActions.vote.VoteSmall.prototype.constructor = SocialActions.vote.VoteSmall;

SocialActions.vote.VoteSmall.prototype.init = function(){
    this.smallVoterPopUp = this.SmallVoterPopUp.prototype.createPopupFromDom(this.$popups + 'small_voter');
    this.smallVoterPopUp.addEventListener('voteWithFacebook',this.votedFacebook);
    this.smallVoterPopUp.addEventListener('voteWithSite',this.votedSite);

    SocialActions.vote.Vote.prototype.init.call(this);
};

SocialActions.vote.VoteSmall.prototype.showVotingButtons = function(){
    this.hideAll();
    this.smallVoter.show();
};

SocialActions.vote.VoteSmall.prototype.votedFacebook = function(){
    this.hideAll();
};





SocialActions.vote.SmallVoterPopUp = function(id){
  Popup.call(this,id);
};
SocialActions.vote.SmallVoterPopUp.prototype = Object.create(Popup.vote.Vote.prototype);
SocialActions.vote.SmallVoterPopUp.prototype.constructor = SocialActions.vote.SmallVoterPopUp;
SocialActions.vote.SmallVoterPopUp.prototype.getInnerTriggerElementsName = function(){
  return ['cross','facebookButton','siteButton'];
};
SocialActions.vote.SmallVoterPopUp.prototype.triggered_facebookButton = function () {
    this.triggerListeners('votedFacebook');
};
SocialActions.vote.SmallVoterPopUp.prototype.triggered_siteButton = function () {
    this.triggerListeners('votedSite');
};

