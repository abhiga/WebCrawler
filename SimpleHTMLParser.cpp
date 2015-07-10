
#include "SimpleHTMLParser.h"
#include "openhttp.h"
#include <string.h>
//int count = 0;
char *c = new char[400];
SimpleHTMLParser::SimpleHTMLParser()
{
}

bool
SimpleHTMLParser::match(char **b, const char *m) {
	int len = strlen(m);
	if ( !strncasecmp(*b, m, len)) {
		(*b)+=len;
		return true;
	}
	return false;
}

bool
SimpleHTMLParser::parse(char * buffer, int n)
{
	enum { START, TAG, SCRIPT, ANCHOR, HREF,
	       COMMENT, FRAME, SRC, TITLE, META, METAKEY, METADESC } state;

	state = START;
	
	char * bufferEnd = buffer + n;
	char * b = buffer;
	bool lastCharSpace = false;
	while (b < bufferEnd) {
		//printf("<%c,%d,%d>", *b, *b,state);
		switch (state) {
		case START: {
			if (match(&b,"<SCRIPT")) {
				state = SCRIPT;
			}
			else if (match(&b,"<!--")) {
				state = COMMENT;
			}
			else if (match(&b,"<A ")) {
				state = ANCHOR;
			}
			else if (match(&b,"<FRAME ")) {
				state = FRAME;
			}
			else if (match(&b,"<TITLE>")) {
				state = TITLE;
			}
			else if (match(&b,"<META NAME=\"keywords\" content=\"")) {
				state = METAKEY;
			}
			else if (match(&b,"<META NAME=\"description\" content=\"")) {
				state = METAKEY;
			}
			else if (match(&b,"<META CONTENT=\"")) {
				state = META;
			}
			else if (match(&b,"</HEAD>")) {
				onContentFound('*');
			}
			else if	(match(&b,"<")) {
				state = TAG;
			}
			else {
				char c = *b;
				//Substitute one or more blank chars with a single space
				/*if (c=='\n'||c=='\r'||c=='\t'||c==' ') {
					if (!lastCharSpace) {
						//onContentFound(' ');
					}
					lastCharSpace = true;
				}
				else {
					//onContentFound(c);
					lastCharSpace = false;
				}*/
				
				b++;
			}
			break;
		}
		
		case META: {
			memset(c,0,400*sizeof(char));
			int count = 0;
			if (match(&b, "name=\"description\"")||match(&b, "name=\"keywords\"")) {
				for(int i = 0; i < 400; i++) {
					if(c[i]!=0) 
						onContentFound(c[i]);
					else 
						break;
				}
				state = START;
			}
			else if (match(&b,">")) {
				state = START;
				//onContentFound('*');
			}			
			else {
				c[count++] = *b;
				b++;
			}
			break;
		}
		case METAKEY: {
			if (match(&b,"\" />")) {
				state = START;
				//onContentFound('*');
			}
			else if(match(&b,"\"/>")) {
				state = START;
				//onContentFound('*');
			}
			else if(match(&b,"/>")) {
				state = START;
				//onContentFound('*');
			}
			else if(match(&b,"\" >")) {
				state = START;
				//onContentFound('*');
			}
			else if(match(&b,"\">")) {
				state = START;
				//onContentFound('*');
			}
			else if(match(&b,">")) {
				state = START;
				//onContentFound('*');
			}			
			else {
				char c = *b;
				//Substitute one or more blank chars with a single space
				//if (c=='\n'||c=='\r'||c=='\t'||c==' ') {
				if (!(('a'<= c && c <= 'z') || ('A' <= c && c <= 'Z'))) {
					if (!lastCharSpace) {
						onContentFound(' ');
					}
					lastCharSpace = true;
				}
				else {
					onContentFound(c);
					lastCharSpace = false;
				}
				
				b++;
			}
			break;
		}
		case TITLE : {
			if (match(&b, "</TITLE>")){
				state = START;
				//onContentFound('*');
			}
			else {
				char c = *b;
				//Substitute one or more blank chars with a single space
				//if (c=='\n'||c=='\r'||c=='\t'||c==' ') {
				if (!(('a'<= c && c <= 'z') || ('A' <= c && c <= 'Z'))) {
					if (!lastCharSpace) {
						onContentFound(' ');
					}
					lastCharSpace = true;
				}
				else {
					onContentFound(c);
					lastCharSpace = false;
				}
				
				b++;
			}
			break;
		}
		case ANCHOR: {
			if (match(&b,"href=\"")) {
				state = HREF;
				urlAnchorLength=0;
				//printf("href=");
			}
			else if (match(&b,">")) {
				// End script
				state = START;
			}
			else {
				b++;
			}
			break;
				
		}
		case HREF: {
			if (match(&b,"\"")) {
				// Found ending "
				state = ANCHOR;
				urlAnchor[urlAnchorLength] = '\0';
				onAnchorFound(urlAnchor);
				//printf("\n");
			}
			else {
				if ( urlAnchorLength < MaxURLLength-1) {
					urlAnchor[urlAnchorLength] = *b;
					urlAnchorLength++;
				}
				//printf("%c", *b, *b);
				b++;
			}
			break;
		}
		case FRAME: {
			if (match(&b,"src=\"")) {
				state = SRC;
				urlAnchorLength=0;
				//printf("href=");
			}
			else if (match(&b,">")) {
				// End script
				state = START;
			}
			else {
				b++;
			}
			break;
				
		}
		case SRC: {
			if (match(&b,"\"")) {
				// Found ending "
				state = FRAME;
				urlAnchor[urlAnchorLength] = '\0';
				onAnchorFound(urlAnchor);
				//printf("\n");
			}
			else {
				if ( urlAnchorLength < MaxURLLength-1) {
					urlAnchor[urlAnchorLength] = *b;
					urlAnchorLength++;
				}
				//printf("%c", *b, *b);
				b++;
			}
			break;
		}
		case SCRIPT: {
			if (match(&b,"/SCRIPT>")) {
				// End script
				state = START;
			}
			else {
				b++;
			}
			break;
		}
		case COMMENT: {
			if (match(&b,"-->")) {
				// End comments
				state = START;
			}
			else {
				b++;
			}
			break;
		}
		case TAG: {
			if (match(&b, ">")) {
				state = START;
			}
			else {
				b++;
			}
			break;
		}
		default:;
		}
		
	}
}

void
SimpleHTMLParser::onContentFound(char c) {
}

void
SimpleHTMLParser::onAnchorFound(char * url) {
}
