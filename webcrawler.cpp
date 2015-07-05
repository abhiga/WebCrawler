
#include "webcrawler.h"
#include "SimpleHTMLParser.h"

char *desc = (char*)malloc(100*sizeof(char));;
int count = 0;
// Add your implementation here
WebCrawler::WebCrawler(int maxUrls, int nInitialURls,  const char ** initialURLs)
{
	// Allocate space for _urlArray
	_headURL = 0;

	_urlArray = new URLRecord[maxUrls];
	// insert the initialURls
	printf("%d\n", nInitialURls);
	for (int i = 0; i < nInitialURls; i++) {
		_urlArray[i]._url = strdup(initialURLs[i]);
		_urlArray[i]._description = "empty";
	}
	// Update _maxUrls, _headURL and _tailURL
	_maxUrls = maxUrls;
	_tailURL = nInitialURls;
	
	_urlToUrlRecord = new HashTableTemplate<int>();
    _wordToURLRecordList = new HashTableTemplate<URLRecordList*>();
}
void WebCrawler::onContentFound(char c)
{ 
	desc[count] = c;
	count++;
	
}
void WebCrawler::onAnchorFound(char * url){
	char *finalurl;	
	char *temp = (char *)malloc(1000*sizeof(char));
	memset(temp,0,1000*sizeof(char));
	bool flag = true;	
	if(_tailURL >= _maxUrls)
		return;
	//check if the absolute URL starts with http
	else if(strncmp(url,"http://", strlen("http://")) == 0) {
		strcpy(temp,url);
	}
	else if(strncmp(url,"//",strlen("//")) == 0) {
		strcpy(temp,"http:");
		strcat(temp,url);
	}
	else if(strncmp(url,"/",strlen("/")) == 0) {
		strcpy(temp, _urlArray[_headURL]._url);
		for(int i = 10; i < strlen(temp); i++) {
			if(temp[i] == '/') {
				temp[i] = '\0';
				break;
			}
		}
		//printf("abhiga\n");
		strcat(temp,url);
		
	}
	/*else if((('a' <= url[0] && url[0] <= 'z')||('A' <= url[0] && url[0] <= 'Z')) && (strncmp(url,"https://",(strlen("https://"))) !=0) && (strncmp(url,"ftp://",(strlen("ftp://"))) !=0)&& (strncmp(url,"mailto:",(strlen("mailto:"))) !=0)) {
		strcpy(temp, _urlArray[_headURL]._url);
		for(int i = strlen(temp)-1; i > 8; i--) {
			if(temp[i] =='/') {
				temp[i+1] = '\0';
				//strcat(temp,"/");
				strcat(temp,url);
				//printf("abhiga\n");	
				break;
			}
		}
	}*/
	for (int i = 0; i< _tailURL; i++) {
			//checking if the URL already exists in URL array
			if(temp[strlen(temp)-1] =='/')
				temp[strlen(temp) - 1] = '\0';
			finalurl = strdup(temp);
			if(strcmp(finalurl, _urlArray[i]._url)==0) {
				flag = false;
				break;
			}
		}
		if(flag) {
			//inserting this absolute URL
			_urlArray[_tailURL]._url = finalurl;
			_urlArray[_tailURL]._description = desc;
			count = 0;
			_tailURL++;
		}
		free(temp);
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
		//_urlArray[_headURL]._description = "empty";
		_headURL++;
		//Find all the hyperlinks of this document and add them to the
		//_urlArray and _urlToUrlRecord if they are not already in the
		//_urlToUrlRecord. Only insert up to _maxURL entries.
		//if(_tailURL == _maxUrls - 1)
			//break;
		//For each word in the document without tags, add the index of this URL to
		//a URLRecordList in the _wordToURLRecordList table if the URL is not already there.
		//while
		//}
	}
	for(int i = 0; i < _headURL;i++) {
			printf("%s\n", _urlArray[i]._url);
			printf("%s\n", _urlArray[i]._description);
		}
}

int main (int argc, char** argv) {
	if(argc<2)
		fprintf(stderr,"Invalid Format\n");
	else {
		int count = 0;
		int maxURLs;
		const char **initialURLs;
		if(strcmp(argv[1],"-u") == 0) {
			maxURLs = atoi(argv[2]);
			initialURLs = new const char*[argc - 3];
			for (int i = 0 ; i < argc - 3; i++) {
				initialURLs[i] = argv[i+3];
				count++;
			}
		}
		else {
			maxURLs = 1000;
			initialURLs = new const char*[argc - 1];
			for (int i = 0 ; i < argc -1; i++) {
				initialURLs[i] = argv[i+1];
				count++;
			}
		}
		WebCrawler *w = new WebCrawler(maxURLs+1,count,initialURLs);
		w -> crawl();
	}
	return 0;
}
