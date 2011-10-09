/*
 * FeedItem.h
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

#ifndef FEEDITEM_H_
#define FEEDITEM_H_

#include <FBase.h>

class FeedItem : public Osp::Base::Object {
public:
	FeedItem();
	result Construct();
	virtual ~FeedItem();

	Osp::Base::String title;
	Osp::Base::String link;
	Osp::Base::String pubDate;
	Osp::Base::String creator;

	Osp::Base::Collection::ArrayList categories;

	Osp::Base::String commentsRssUrl;
	Osp::Base::String description;

	Osp::Base::Integer commentsCount;

};

#endif /* FEEDITEM_H_ */
