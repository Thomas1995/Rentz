#include "common.h"
#include <fcntl.h>
#include <unistd.h>

int Common::inc(int &x) {
	x++;
	if(x >= MAX_BUFF)
		x -= MAX_BUFF;
	return x;
}

Common::Common():
  at(0),
  sfd(-1) {

  }

Common::Common(int sfd):
  at(0),
  sfd(sfd) {
    fcntl(sfd, F_SETFL, O_NONBLOCK);
    //set the fd to be non blocking
  }

std::vector<uint8_t> Common::readFrame() {

	int n;

	while((n = read(sfd, buff + at, MAX_BUFF - at)) != 0 && flags.size() < 2) {
    if(n == -1)
      continue;
    debug("Read %d bytes\n", n);

    int cr = at;
    for(int i = 0; i < n; ++i, inc(cr)) {
      if(buff[cr] == FLAG)
        flags.push_back(cr);
    }

		at += n;
		if(at >= MAX_BUFF)
			at -= MAX_BUFF;
	}

	if(flags.size() < 2) {
		debug("The client has closed the connection\n");
		exit(1);
		//TODO
		//add disconnect handling
	}

	assert(flags.size() == 2);

	inc(flags[1]);
	//flags[1] refers to the
	//past the flag byte

	std::vector<uint8_t> frame;

	const int cnt = (flags[1] > flags[0]) ? flags[1] - flags[0] : MAX_BUFF - flags[0] + flags[1];

	frame.reserve(cnt);

	for(int i = flags[0]; i != flags[1]; inc(i)) {
    if(buff[i] == ESC) {
      inc(i);
      buff[i] ^= MAGIC;
    }
		frame.push_back(buff[i]);
		buff[i] = 0;
	}

	flags.clear();

	frame.shrink_to_fit();
	return frame;
}
event Common::readEvent() {
	event ret;
	ret.init(readFrame().data());
	return ret;
}
