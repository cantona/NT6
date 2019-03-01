// /clone/shop/wuxi_shop.c
// Last modified by winder 2003.10.20

inherit SHOP;

void create()
{
        set("short", "聚豐園");
        set("no_fight", 1);
        set("no_beg", 1);
        set("owner", "VOID_SHOP");
        set("exits", ([
                "down" : "/d/wuxi/majiu",
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
聚豐園是無錫城裡最著名的店舖，整個舖面裝修得相當精美雅致，
顯出江南大都會繁華大方的氣派。不過店裡的貨櫃上卻空無一物，看樣
子已經很久沒人來打理了。
LONG);
        else
                set("long", @LONG
聚豐園是無錫城裡最著名的店舖，整個舖面裝修得相當精美雅致，
顯出江南大都會繁華大方的氣派。店舖裡的伙計正招呼著客人，忙得滿
頭大汗。
LONG);
        return;
}
