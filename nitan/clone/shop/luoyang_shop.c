inherit SHOP;

void create()
{
        set("short", "天寰閣");
        set("long", @LONG
天寰閣是洛陽城裡最著名的店舖，整個舖面裝修得相當精
美雅致，顯出東都洛陽繁華大方的氣派。不過店裡的貨櫃上卻
空無一物，看樣子已經很久沒人來打理了。
LONG);
        set("open_long", @LONG
天寰閣是洛陽城裡最著名的店舖，整個舖面裝修得相當精
美雅致，顯出東都洛陽繁華大方的氣派。店舖裡的伙計正招呼
著客人，忙得滿頭大汗。
LONG);
        set("no_fight", 1);
        set("no_beg", 1);
        set("owner", "VOID_SHOP");
        set("exits", ([
                "down" : "/d/luoyang/majiu",
        ]));
        set("no_steal", 1);
        set("objects", ([
                __DIR__"waiter" : 1,
        ]));
        set("no_clean_up", 0);
        set("shop_type", 0);

        setup();
}