# Rentz

Communication protocol:

Server accepts client's connection.

Server asks for client's name
Client sends his name.

Server sends the client's index.
Client responds with an acknowledgement.

Client waits for a request event(defined in event.h).

After the client processes an event, a response or acknowledgement is mandatory.
Furthermore, response event should have the same type as the request.

Makefile:

If make does not work, type "make -v" and make sure your version is >= 4.1.
