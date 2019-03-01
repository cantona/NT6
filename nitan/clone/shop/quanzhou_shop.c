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
這裡是泉州城裡的一家店舖。泉州城雖小，清源山卻甚為著名。從
店舖紅木雕窗放眼望去，整個泉州古城熙熙攘攘的街道盡收眼底。不過
店裡的貨櫃上卻空無一物，看樣子已經很久沒人來打理了。
LONG);
        else
                set("long", @LONG
這裡是泉州城裡的一家店舖。泉州城雖小，清源山卻甚為著名。從
店舖紅木雕窗放眼望去，整個泉州古城熙熙攘攘的街道盡收眼底。店舖
裡的伙計正招呼著客人，忙得滿頭大汗。
LONG);
        return;
}
