/**
 * Created by xavier on 7/2/16.
 */


var SocialActions = SocialActions || {};
SocialActions.vote = SocialActions.vote || {};

SocialActions.vote.VoteBigView = function(domElement){
    this.$domElement = $(domElement);
    this.$votes = this.$domElement.find('.votes');
    this.$text = this.$domElement.find('.text');
    U.Listeners.call(this);
    var nid = this.$votes.attr('data-nid');
    this.URL = '/node/' + nid + '/social/vote';
    SocialActions.vote.VoteBig.addEventListener('VoteCasted', this, this.addVote);
    this.getAndSetVote();
};

SocialActions.vote.VoteBigView.prototype = Object.create(U.Listeners.prototype);

SocialActions.vote.VoteBigView.prototype.getAndSetVote = function(){
    var self = this;
    jQuery.ajax({
        method: 'GET',
        url: this.URL,
        success: function(data){
            window.data = data = JSON.parse(data);
            self.votes = data[0];
            self.votes = typeof self.votes == 'undefined'?
                0 : parseInt(self.votes[Object.keys(self.votes)[0]]);
            self.setVote();
        }
    })
};

SocialActions.vote.VoteBigView.prototype.setVote = function(){
    this.$votes.text(this.votes);
    this.$text.text(this.votes == 1? Drupal.t('vote') : Drupal.t('votes'));
};

SocialActions.vote.VoteBigView.prototype.addVote = function(param){
    if(param.status == 'successful'){
        ++this.votes;
        this.setVote();
    }

};