// /clone/shop/yanping_shop.c
// Last modified by winder 2003.10.20

inherit SHOP;

void create()
{
        set("short", "雙溪樓");
        set("no_fight", 1);
        set("no_beg", 1);
        set("owner", "VOID_SHOP");
        set("exits", ([
                "down" : "/d/yanping/majiu",
        ]));
        set("objects", ([
                __DIR__"waiter" : 1,
        ]));
        set("shop_type", 0);

        setup();
}

void init()
{
        if (query("shop_type") == 0)
                set("long", @LONG
這裏是延平城裏最著名的店鋪，整個鋪面裝修得相當精美雅緻，樓
頂憑軒處，正是俯瞰雙溪匯流的好去處。不過店裏的貨櫃上卻空無一物，
看樣子已經很久沒人來打理了。
LONG);
        else
                set("long", @LONG
這裏是延平城裏最熱鬧的店鋪，整個鋪面裝修得相當精美雅緻，樓
頂憑軒處，正是俯瞰雙溪匯流的好去處。店鋪裏的夥計正招呼着客人，
忙得滿頭大汗。
LONG);
        return;
}
