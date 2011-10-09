/*
 * FeedParser.h
 *
 * Created by: Dr. Strangecode
 * ---------------------------------------------
 * This is free code, it can be used, modified, 
 * destroyed, raped and whatever without limits.
 * I own no copyrights over it.
 * This code is provided AS IS without warranty
 * of any kind either expressed or implied,
 * including but not limited to the implied
 * warranties of merchantability and/or fitness
 * for a particular purpose.
 * ---------------------------------------------
 * For more free code visit http://drstrangecode.org
 */


#ifndef FEEDPARSER_H_
#define FEEDPARSER_H_

#include <FXml.h>
#include <FBase.h>
#include <FIo.h>

class FeedParser {
public:
	FeedParser();
	virtual ~FeedParser();
	result Construct(Osp::Base::String & filePath);

	Osp::Base::Collection::ArrayList * ParseFeedN();

private:

	result ParsePubDateTag(Osp::Base::String & in, Osp::Base::String & out);
	Osp::Base::String rssFeedFilePath;

};

#endif /* FEEDPARSER_H_ */
