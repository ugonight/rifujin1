#include "System/item.h"

USING_NS_CC;

void Item::initItem() {

	mItemList["crayon_g"] = new ItemObj("item/crayon_g.png");
	mItemList["egg"] = new ItemObj("item/egg.png");
	mItemList["mushroom"] = new ItemObj("item/mushroom_i.png");
	mItemList["matsu"] = new ItemObj("item/matsu.png");
	mItemList["stick"] = new ItemObj("item/stick_i.png");

}