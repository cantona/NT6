inherit SHOP;

void create()
{
        set("short", "玉皇閣");
        set("long", @LONG
玉皇閣乃是由杭州城郊的玉皇山而得名，所謂「上有天堂
下有蘇杭」，杭州城建築別具一格，這家店舖也不例外。不過
貨櫃上卻空無一物，看樣子已很久沒人來打理了。
LONG);
        set("open_long", @LONG
玉皇閣乃是由杭州城郊的玉皇山而得名，所謂「上有天堂
下有蘇杭」，杭州城建築別具一格，這家店舖也不例外。店堂
裝潢得典雅精致，伙計正彬彬有禮的招呼著客人。
LONG);
        set("no_fight", 1);
        set("no_beg", 1);
        set("owner", "VOID_SHOP");
        set("exits", ([
                "down" : "/d/hangzhou/majiu",
        ]));
        set("no_steal", 1);
        set("objects", ([
                __DIR__"waiter" : 1,
        ]));
        set("no_clean_up", 0);
        set("shop_type", 0);

        setup();
}