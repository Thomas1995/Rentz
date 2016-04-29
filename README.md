# Rentz

Communication protocol:

Server accepts client's connection.

Client sends his name.

Server sends the client's index.

Client waits for a request event(defined in event.h).

After the client processes an event, a response or acknowledgement is mandatory.
The response event should have the same type as the request.
