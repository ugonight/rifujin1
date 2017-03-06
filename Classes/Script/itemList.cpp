#include "System/item.h"

USING_NS_CC;

void Item::initItem() {

	mItemList["crayon_g"] = new ItemObj("item/crayon_g.png");
	mItemList["crayon_b"] = new ItemObj("item/crayon_b.png");
	mItemList["egg"] = new ItemObj("item/egg.png");
	mItemList["mushroom"] = new ItemObj("item/mushroom_i.png");
	mItemList["matsu"] = new ItemObj("item/matsu.png");
	mItemList["stick"] = new ItemObj("item/stick_i.png");
	mItemList["key"] = new ItemObj("item/key_i.png");
	mItemList["key2"] = new ItemObj("item/key2_i.png");
	mItemList["lamp"] = new ItemObj("item/lamp_i.png");
	mItemList["board"] = new ItemObj("item/board_i.png");
	mItemList["seed"] = new ItemObj("item/seed_i.png");

}