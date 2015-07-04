
#include "webcrawler.h"
#include "SimpleHTMLParser.h"

char *desc = "";
//int count = 0;
// Add your implementation here
WebCrawler::WebCrawler(int maxUrls, int nInitialURls,  const char ** initialURLs)
{
	// Allocate space for _urlArray
	_headURL = 0;
	_urlArray = new URLRecord[maxUrls];
	// insert the initialURls
	for (int i = 0; i < nInitialURls; i++) {
		_urlArray -> _url = strdup(initialURLs[i]);
		_urlArray -> _description = NULL;
	}
	// Update _maxUrls, _headURL and _tailURL
	_maxUrls = maxUrls;
	_tailURL = nInitialURls;
}
void WebCrawler::onContentFound(char c)
{ 
	char *d = &c;
	strcat(desc,d);
	//count++;
	
}
void WebCrawler::onAnchorFound(char * url){
	if(strncmp(url,"http://", strlen("http://"))) {
		_urlArray[_tailURL]._url = strdup(url);
		_tailURL++;
	}
}
void WebCrawler::crawl()

{	
	int n;
	char * buffer;
	while (_headURL <_tailURL) {
		//Fetch the next URL in _headURL
		buffer = fetchHTML(_urlArray[_headURL]._url, &n);

		//Increment _headURL
		
		//If the document is not text/html 
		if(buffer == NULL) {
			_headURL++;
			continue;
		}
		parse(buffer,n);

		//Get the first 500 characters (at most) of the document without tags. Add this 
		//  description to theURL record for this URL.
		_urlArray[_headURL]._description = desc;
		_headURL++;
		//Find all the hyperlinks of this document and add them to the
		//_urlArray and _urlToUrlRecord if they are not already in the
		//_urlToUrlRecord. Only insert up to _maxURL entries.

		//For each word in the document without tags, add the index of this URL to
		//a URLRecordList in the _wordToURLRecordList table if the URL is not already there.
		//while
		//}
	}
}

int main (int argc, char** argv) {

	return 0;
}
