 /**
 * Created by Xavier on 06/04/2015.
 */

var SocialActions = SocialActions || {};
SocialActions.vote = SocialActions.vote || {};

SocialActions.vote.VoteBig = function(domElement){
    SocialActions.vote.Vote.call(this,domElement);
    SocialActions.vote.VoteBig = this
};
SocialActions.vote.VoteBig.prototype = Object.create(SocialActions.vote.Vote.prototype);
SocialActions.vote.VoteBig.prototype.showVotingButtons =  function(){
    this.$domElement.find('.voter').show(0);
};
$(document).ready(function(){
    var $elem = $('#block-socialActionsVote-socialActionsVote_big');
    if($elem.length > 0) new SocialActions.vote.VoteBig($elem[0]);
    var $elem2 = $('#block-socialActionsVote-socialActionsVote_big_view');
    if($elem2.length > 0)
    new SocialActions.vote.VoteBigView($elem2[0]);
});