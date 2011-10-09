/*
 * FeedParser.cpp
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

#include "XmlParser/FeedParser.h"
#include "Content/FeedItem.h"

using namespace Osp::Base;
using namespace Osp::Base::Collection;
using namespace Osp::Base::Utility;

/* File APIs*/
using namespace Osp::Io;

/* LibXml APIs*/
using namespace Osp::Xml;

/* ========= XML tags that are to be parsed ========== */
#define kItemTag 							L"item"
#define kTitleTag 							L"title"
#define kLinkTag 							L"link"
#define kPubDateTag 						L"pubDate"
#define kCategoryTag 						L"category"
#define kDescription 						L"description"
#define kCommentsRssUrlTag 					L"wfw:commentRss"
#define kCommentsCountTag 					L"slash:comments"
#define kCreatorTag 						L"dc:creator"
/* =================================================== */

FeedParser::FeedParser() {
}

FeedParser::~FeedParser() {
}

result FeedParser::Construct(Osp::Base::String & filePath) {
	/* Check that the file actually exists,
	 * return E_FILE_NOT_FOUND if not */

	result r = E_SUCCESS;
	if (!File::IsFileExist(filePath)) {
		r = E_FILE_NOT_FOUND;
	}
	else {
		rssFeedFilePath = filePath;
	}

	return r;
}

result FeedParser::ParsePubDateTag(String & in, String & out) {
	/*
	 * Converts a date string.
	 * Input format: "Thu, 25 Aug 2011 21:13:55 +0000"
	 * Output format: "Thu, 25 Aug 2011"
	 * */
	result r = E_SUCCESS;

	StringTokenizer tokenizer(in, " ");
	if (tokenizer.GetTokenCount() != 6) {
		AppLog("Error parsing xml date value");
		r = E_PARSING_FAILED;
	} else {
		for (int i = 0; i < 4; i++) {
			String token;
			tokenizer.GetNextToken(token);
			out.Append(token);
			out.Append(" ");
		}
		out.Remove(out.GetLength() - 1, 1);
	}

	return r;
}

ArrayList * FeedParser::ParseFeedN() {

	/* xmlReaderForFile accept a const char * so
	 * we need to convert "Osp::Base::String" to "const char *"
	 * Here's how: */
	ByteBuffer * fileNameBuffer = StringUtil::StringToUtf8N(rssFeedFilePath);

	/* Create the xml reader */
	xmlTextReaderPtr reader = null;
	reader = xmlReaderForFile((const char *) fileNameBuffer->GetPointer(), NULL, 0);

	/* delete the buffer*/
	delete fileNameBuffer;

	if (reader == null) {
		AppLog("Fatal: Cannot open file!");
		return null;
	}

	/* Create the feeds list */
	ArrayList * feedsList = new ArrayList();
	feedsList->Construct();

	FeedItem * currentFeed = null;
	String currentValue;

	/* Read next node, if a node is available xmlTextReaderRead returns 1*/
	while (xmlTextReaderRead(reader) > 0) {

		/* Libxml char pointers to store node name and value */
		const xmlChar *name = null;
		const xmlChar *value = null;

		/* Two Osp::Base::String variables to store current node name and value */
		String nodeName;
		String nodeValue;

		/* Read node name */
		name = xmlTextReaderConstName(reader);
		/* Turn libxml char pointer to Osp::Base::String */
		if (name != null) {
			Osp::Base::Utility::StringUtil::Utf8ToString((char*) name, nodeName);
		}

		/* If the current node has a value */
		if (xmlTextReaderHasValue(reader)) {
			/* Read node value */
			value = xmlTextReaderConstValue(reader);
			if (value != null) {
				/* Turn libxml char pointer to Osp::Base::String */
				Osp::Base::Utility::StringUtil::Utf8ToString((char*) value,
						nodeValue);
			}
		}

		/* Read node type */
		int xmlreadType = xmlTextReaderNodeType(reader);

		/* Perform different action based upon the current node type */
		if (xmlreadType == XML_READER_TYPE_TEXT) {
			currentValue = nodeValue;
		} else if (xmlreadType == XML_READER_TYPE_CDATA) {
			currentValue = nodeValue;
		} else if (xmlreadType == XML_READER_TYPE_ELEMENT) {
			if (nodeName.Equals(kItemTag, true)) {
				/* Found a new <item> tag,
				 * create a new FeedItem object
				 * and add it to the feedsList */
				FeedItem * feedItem = new FeedItem();
				currentFeed = feedItem;
				feedsList->Add(*feedItem);
			}
		} else if (xmlreadType == XML_READER_TYPE_END_ELEMENT) {

			if (nodeName.Equals(kItemTag, true)) {
				/* </item> found */
				currentFeed = null;
			} else if (nodeName.Equals(kTitleTag, true)) {
				if (currentFeed)
					currentFeed->title = currentValue;
			} else if (nodeName.Equals(kPubDateTag, true)) {
				if (currentFeed) {
					String pubDate;
					result r = ParsePubDateTag(currentValue, pubDate);
					if (IsFailed(r))
						currentFeed->pubDate = L"---";
					else
						currentFeed->pubDate = pubDate;
				}
			} else if (nodeName.Equals(kCategoryTag, true)) {
				if (currentFeed)
					currentFeed->categories.Add(*(new String(currentValue)));
			} else if (nodeName.Equals(kDescription, true)) {
				if (currentFeed) {

					String beforeEllipsis = currentValue;

					int index;
					if (currentValue.IndexOf(L"&#8230;", 0, index) == E_SUCCESS) {
						currentValue.SubString(0, index, beforeEllipsis);
					}

					xmlParserCtxtPtr parserctxt = xmlNewParserCtxt();
					ByteBuffer * bf = StringUtil::StringToUtf8N(beforeEllipsis);
					xmlChar * final = xmlStringDecodeEntities(parserctxt, (xmlChar *)bf->GetPointer(), XML_SUBSTITUTE_REF | XML_SUBSTITUTE_PEREF, 0, 0, 0);
					delete bf;
					xmlFreeParserCtxt(parserctxt);

					String descFinal;
					StringUtil::Utf8ToString((const char *)final, descFinal);

					currentFeed->description = descFinal;
				}
			} else if (nodeName.Equals(kCommentsRssUrlTag, true)) {
				if (currentFeed)
					currentFeed->commentsRssUrl = currentValue;
			} else if (nodeName.Equals(kCreatorTag, true)) {
				if (currentFeed)
					currentFeed->creator = currentValue;
			} else if (nodeName.Equals(kLinkTag, true)) {
				if (currentFeed)
					currentFeed->link = currentValue;
			} else if (nodeName.Equals(kCommentsCountTag, true)) {
				if (currentFeed) {
					int commentsCount;
					result r = Integer::Parse(currentValue, commentsCount);
					if (IsFailed(r))
						currentFeed->commentsCount = 0;
					else
						currentFeed->commentsCount = commentsCount;
				}
			}
		}
	}

	xmlFreeTextReader(reader);

	AppLog("Found %d elements", feedsList->GetCount());

	return feedsList;
}

