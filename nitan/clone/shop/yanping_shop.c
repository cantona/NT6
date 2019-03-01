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
這裡是延平城裡最著名的店舖，整個舖面裝修得相當精美雅致，樓
頂憑軒處，正是俯瞰雙溪匯流的好去處。不過店裡的貨櫃上卻空無一物，
看樣子已經很久沒人來打理了。
LONG);
        else
                set("long", @LONG
這裡是延平城裡最熱鬧的店舖，整個舖面裝修得相當精美雅致，樓
頂憑軒處，正是俯瞰雙溪匯流的好去處。店舖裡的伙計正招呼著客人，
忙得滿頭大汗。
LONG);
        return;
}
