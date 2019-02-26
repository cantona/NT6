inherit SHOP;

void create()
{
        set("short", "百鶴齋");
        set("long", @LONG
這裏是中州城裏最著名的店鋪，整個鋪面裝修得相當精美
雅緻，紅木鋪地，漆門雕窗，大堂正中掛着一幅百鶴圖。不過
店裏的貨櫃上卻空無一物，看來已很久沒人打理了。
LONG);
        set("open_long", @LONG
這裏是中州城裏最著名的店鋪，整個鋪面裝修得相當精美
雅緻，紅木鋪地，漆門雕窗，大堂正中掛着一幅百鶴圖。店鋪
裏的夥計正招呼着客人，忙得滿頭大汗。
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