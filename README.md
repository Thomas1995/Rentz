## About the software:

### Communication protocol:

Server accepts client's connection.

Server asks for client's name
Client sends his name.

Server sends the client's index.
Client responds with an acknowledgement.

Client waits for a request event(defined in event.h).

After the client processes an event, a response or acknowledgement is mandatory.
Furthermore, response event should have the same type as the request.


## About the game:

###Introduction

[Rentz] is an American version of the Romanian card game Renț. Rentz is mainly a Trick-taking game with a collection of mini-games. The object of each mini-game is to either avoid taking "tricks" or score points. The game can be played by three to six players, each of which is dealt 8 cards from a standard playing card deck at the start of each hand.

[Rentz]: <https://en.wikipedia.org/wiki/Rentz_Card_Game>

###Rules

A dealer is picked at random to start the game.

The dealer deals 8 cards to each player then picks the mini-game. He can pick the mini-game before dealing cards, resulting in playing NV mode. The last mini-game for each player is always in NV mode. Note: A mini-game can only be chosen once per dealer.

The mini game is played until all cards are played or the mini-game is otherwise ended.

"Trick-taking" mini-games are played when the dealer plays a card. The other players then play cards of the same suit in a counter-clockwise fashion. When each player has played a card, the player who played the highest card of the initial suit takes the "trick". Note: if a player does not have a card of the initial suit, he must lay a card of any suit.

The dealer then shuffles, re-deals 8 cards to each player and picks a different mini-game until all mini-games have been played, at which time the dealer is changed.

After all four players have dealt all mini-games, scores are compared. The player with the most points wins.

###Mini-games

**Acool**: -10 points per trick taken.

**Whist**: +10 points per trick taken.

**Diamonds**: -20 points per Diamond taken.

**Queens**: -30 points per Queen taken.

**King of Hearts**: -100 points if the King of Hearts is played. The mini-game is ended once the King of Hearts is taken in a trick.

**Ten of Club**: +100 points if the Ten of Club is played. The mini-game is ended once the Ten of Club is taken in a trick. 

**Totals**: It sums up the points taken in Acool, Diamonds, Queens and King of Hearts.

If the player chooses to play the NV mode, then the score is doubled that round for each player.
