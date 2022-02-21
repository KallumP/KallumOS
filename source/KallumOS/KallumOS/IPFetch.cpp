#include "IPFetch.h"

#include <WS2tcpip.h>

IPFetch::IPFetch() {

}

IPFetch::IPFetch(olc::PixelGameEngine* _window, Point _position, Point _size) : Process(_window, "IPFetcher", _position, _size) {

	hostName = "google.com";
    FetchIP();
}


void IPFetch::Draw(Point offset) {

	if (display) {

		DrawBoxBar(offset);
		offset.Set(new Point(offset.GetX() + position.GetX(), offset.GetY() + position.GetY() + barHeight));

		window->DrawString(10 + offset.GetX(), 20 + offset.GetY(), hostName, olc::BLACK, 2);
		window->DrawString(10 + offset.GetX(), 40 + offset.GetY(), hostAddress, olc::BLACK, 2);

	}
}
void IPFetch::OnKeyPress(KeyPress* e) {

}
void IPFetch::OnMousePress(MousePress* e, int taskbarHeight) {

}

void IPFetch::FetchIP() {


	addrinfo hints = {}; //hints used to filter what results are found
	hints.ai_family = AF_INET; //v4 address only
	addrinfo* hostinfo = nullptr;

	int result = getaddrinfo(hostAddress.c_str(), NULL, &hints, &hostinfo);
   
	//if the result was 0 (success)
	if (result == 0) {

		sockaddr_in* host_addr = reinterpret_cast<sockaddr_in*>(hostinfo->ai_addr);

		hostAddress =  host_addr->sin_addr.S_un.S_addr;

//		hostAddress
		//inet_ntop(AF_INET, &host_addr->sin_addr, &hostAddress.c_str()[0], 16);
	}


}


