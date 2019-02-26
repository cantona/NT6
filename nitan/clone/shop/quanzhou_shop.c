// /clone/shop/quanzhou_shop.c
// Last modified by winder 2003.10.20

inherit SHOP;

void create()
{
        set("short", "福人頤");
        set("no_fight", 1);
        set("no_beg", 1);
        set("owner", "VOID_SHOP");
        set("exits", ([
                "down" : "/d/quanzhou/majiu",
        ]));
        set("no_steal", 1);
        set("objects", ([
                __DIR__"waiter" : 1,
        ]));
        set("no_clean_up", 0);
        set("shop_type", 0);

        setup();
}

void init()
{
        if (query("shop_type") == 0)
                set("long", @LONG
這裏是泉州城裏的一家店鋪。泉州城雖小，清源山卻甚為著名。從
店鋪紅木雕窗放眼望去，整個泉州古城熙熙攘攘的街道盡收眼底。不過
店裏的貨櫃上卻空無一物，看樣子已經很久沒人來打理了。
LONG);
        else
                set("long", @LONG
這裏是泉州城裏的一家店鋪。泉州城雖小，清源山卻甚為著名。從
店鋪紅木雕窗放眼望去，整個泉州古城熙熙攘攘的街道盡收眼底。店鋪
裏的夥計正招呼着客人，忙得滿頭大汗。
LONG);
        return;
}
