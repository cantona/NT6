inherit SHOP;

void create()
{
        set("short", "百鶴齋");
        set("long", @LONG
這裡是中州城裡最著名的店舖，整個舖面裝修得相當精美
雅致，紅木舖地，漆門雕窗，大堂正中掛著一幅百鶴圖。不過
店裡的貨櫃上卻空無一物，看來已很久沒人打理了。
LONG);
        set("open_long", @LONG
這裡是中州城裡最著名的店舖，整個舖面裝修得相當精美
雅致，紅木舖地，漆門雕窗，大堂正中掛著一幅百鶴圖。店舖
裡的伙計正招呼著客人，忙得滿頭大汗。
LONG);
        set("no_fight", 1);
        set("no_beg", 1);
        set("owner", "VOID_SHOP");
        set("exits", ([
                "down" : "/d/zhongzhou/majiu",
        ]));
        set("no_steal", 1);
        set("objects", ([
                __DIR__"waiter" : 1,
        ]));
        set("no_clean_up", 0);
        set("shop_type", 0);

        setup();
}