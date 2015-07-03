
#include "webcrawler.h"
#include "SimpleHTMLParser.h"

// Add your implementation here
WebCrawler::WebCrawler(int maxUrls, int nInitialURls,  const char ** initialURLs)
{
	// Allocate space for _urlArray
	_headURL = 0;
	_urlArray = new URLRecord[maxUrls];
	// insert the initialURls
	for (int i = 0; i < nInitialURls; i++) {
		_urlArray -> _url = strdup(initialURLs[i]);
		_urlArray -> _description = " ";
	}
	// Update _maxUrls, _headURL and _tailURL
	_maxUrls = maxUrls;
	_tailURL = nInitialURls;
}
void WebCrawler::crawl()

{

  //while (_headURL <_tailURL) {
    //Fetch the next URL in _headURL

    //Increment _headURL

    //If the document is not text/html 

    //      continue;

    //Get the first 500 characters (at most) of the document without tags. Add this 
     //  description to theURL record for this URL.

    //Find all the hyperlinks of this document and add them to the
      //_urlArray and _urlToUrlRecord if they are not already in the
      //_urlToUrlRecord. Only insert up to _maxURL entries.

    //For each word in the document without tags, add the index of this URL to
      //a URLRecordList in the _wordToURLRecordList table if the URL is not already there.
  //while
}

int main () {

return 0;
}
