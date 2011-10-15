/*
 * Settings.h
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

#ifndef SETTINGS_H_
#define SETTINGS_H_

/*
 * HTTP redirect actually does not work on Bada 2.0
 * so I have to point to the direct feedburner url
 * */
#define kFeedUrl L"http://feeds.feedburner.com/DrStrangecode"
//#define kFeedUrl L"http://drstrangecode.org/rss"
#define kMainFeedLocalFilePath "/Home/mainfeed.xml"

#define kMainFormNameString L"MainForm"
#define kItemFormNameString L"ItemForm"

#endif /* SETTINGS_H_ */
