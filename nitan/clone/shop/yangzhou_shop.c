inherit SHOP;

void create()
{
        set("short", "通天閣");
        set("long", @LONG
這裡是揚州城裡最著名的店舖，整個舖面裝修得相當精美
雅致，顯出十裡揚州繁華大方的氣派。不過店裡的貨櫃上卻空
無一物，看樣子已經很久沒人來打理了。
LONG);
        set("open_long", @LONG
這裡是揚州城裡最熱鬧的店舖，舖裡人來人往，川流不息。
舖面裝修得精美雅致，顯出十裡揚州繁華大方的氣派。店舖裡
的伙計正招呼著客人，忙得滿頭大汗。
LONG);
        set("no_fight", 1);
        set("no_beg", 1);
        set("owner", "VOID_SHOP");
        set("exits", ([
                "down" : "/d/city/majiu",
        ]));
        set("no_steal", 1);
        set("objects", ([
                __DIR__"waiter" : 1,
        ]));
        set("no_clean_up", 0);
        set("shop_type", 0);

        setup();
}