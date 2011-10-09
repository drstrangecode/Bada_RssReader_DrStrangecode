/*
 * FeedsListItem.h
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

#ifndef FEEDSLISTITEM_H_
#define FEEDSLISTITEM_H_

#include <FBase.h>
#include <FGraphics.h>
#include <FUi.h>
#include <FApp.h>

class FeedsListItem : public Osp::Ui::Controls::CustomItem {
    public:
        static const int ITEM_HEIGHT = 100;
        static const int ITEM_LEFT_MARGIN = 10;
        static const int ICON_DIMENSION = 0;//ITEM_HEIGHT;

        static const int ICO_ELM_ID = 1;
        static const int TITLE_ELM_ID = 2;
        static const int CATEGORIES_ELM_ID = 3;
        static const int ABOUT_ELM_ID = 4;
        static const int SEPARATOR_ELM_ID = 5;

        FeedsListItem();
        virtual ~FeedsListItem();

        result Construct(int width,
                         Osp::Base::String & title,
                         Osp::Base::String & categories,
                         Osp::Base::String & about);

    private:
        Osp::Graphics::Bitmap * pRowIcon;
        Osp::Graphics::Bitmap * pRowSeparatorBitmap;
};

#endif /* FEEDSLISTITEM_H_ */
