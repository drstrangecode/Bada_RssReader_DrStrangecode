/*
 * FeedItem.cpp
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


#include "Content/FeedItem.h"

using namespace Osp::Base;

FeedItem::FeedItem() {
}

result FeedItem::Construct() {
    return categories.Construct();
}

FeedItem::~FeedItem() {
    categories.RemoveAll(true);
}
