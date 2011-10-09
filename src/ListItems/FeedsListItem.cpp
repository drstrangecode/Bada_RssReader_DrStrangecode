/*
 * FeedsListItem.cpp
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

#include "ListItems/FeedsListItem.h"

using namespace Osp::Base;
using namespace Osp::Graphics;
using namespace Osp::Ui;
using namespace Osp::Ui::Controls;
using namespace Osp::App;

FeedsListItem::FeedsListItem() {
    pRowIcon = null;
    pRowSeparatorBitmap = null;
}

FeedsListItem::~FeedsListItem() {
    delete pRowIcon;
    delete pRowSeparatorBitmap;
}

result FeedsListItem::Construct(int width, String & title, String & categories, String & about) {
    Dimension dimension = Dimension(width, ITEM_HEIGHT);
    ListAnnexStyle annexStyle = LIST_ANNEX_STYLE_DETAILED;
    int contentWidth = width - ListItemBase::GetAnnexWidth(annexStyle);

    result r = CustomItem::Construct(dimension, annexStyle);

    Application * app = Application::GetInstance();
    AppResource * res = app->GetAppResource();

    pRowIcon = res->GetBitmapN(L"row-icon.png",
                               BITMAP_PIXEL_FORMAT_ARGB8888);

    pRowSeparatorBitmap = res->GetBitmapN(L"separator.png",
                                          BITMAP_PIXEL_FORMAT_ARGB8888);

    Rectangle icoDim = Rectangle(ITEM_LEFT_MARGIN,
                                 0,
                                 ICON_DIMENSION,
                                 ICON_DIMENSION);

    Rectangle titleDim = Rectangle(ITEM_LEFT_MARGIN + ICON_DIMENSION,
                                   0,
                                   contentWidth - ICON_DIMENSION - ITEM_LEFT_MARGIN,
                                   ITEM_HEIGHT / 3);

    Rectangle categoriesDim = Rectangle(titleDim.x,
                                        titleDim.y + titleDim.height,
                                        titleDim.width,
                                        titleDim.height);

    Rectangle aboutDim = Rectangle(categoriesDim.x,
                                   categoriesDim.y + categoriesDim.height,
                                   categoriesDim.width,
                                   categoriesDim.height);

    Rectangle separatorDim = Rectangle(0,
                                       ITEM_HEIGHT - pRowSeparatorBitmap->GetHeight(),
                                       width,
                                       pRowSeparatorBitmap->GetHeight());

    AddElement(titleDim,
               TITLE_ELM_ID,
               title,
               28,
               Color::COLOR_WHITE,
               Color::COLOR_BLACK,
               Color::COLOR_BLACK,
               true);

    AddElement(categoriesDim,
               CATEGORIES_ELM_ID,
               categories,
               22,
               Color::COLOR_GREY,
               Color::COLOR_BLACK,
               Color::COLOR_BLACK,
               true);

    AddElement(aboutDim,
               ABOUT_ELM_ID,
               about,
               18,
               Color::COLOR_GREY,
               Color::COLOR_BLACK,
               Color::COLOR_BLACK,
               true);

    AddElement(separatorDim,
               SEPARATOR_ELM_ID,
               *pRowSeparatorBitmap,
               pRowSeparatorBitmap,
               pRowSeparatorBitmap);

    return r;
}
