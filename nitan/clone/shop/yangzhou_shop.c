inherit SHOP;

void create()
{
        set("short", "通天閣");
        set("long", @LONG
這裏是揚州城裏最著名的店鋪，整個鋪面裝修得相當精美
雅緻，顯出十里揚州繁華大方的氣派。不過店裏的貨櫃上卻空
無一物，看樣子已經很久沒人來打理了。
LONG);
        set("open_long", @LONG
這裏是揚州城裏最熱鬧的店鋪，鋪里人來人往，川流不息。
鋪面裝修得精美雅緻，顯出十里揚州繁華大方的氣派。店鋪裏
的夥計正招呼着客人，忙得滿頭大汗。
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