inherit SHOP;

void create()
{
        set("short", "百寶齋");
        set("long", @LONG
這裡是長安城裡小有名氣的店堂─百寶齋。長安城民眾富
裕，舖裡出售的貨物也是別具一格。整個舖面裝潢得非常雅致，
不過貨櫃上卻空無一物，看來已很久沒人打理了。
LONG);
        set("open_long", @LONG
這裡是長安城裡小有名氣的店堂─百寶齋。長安城民眾富
裕，舖裡出售的貨物也是別具一格。整個舖面裝潢得非常雅致。
貨櫃上擺滿了各式各樣、琳琅滿目的貨物。
LONG);
        set("no_fight", 1);
        set("no_beg", 1);
        set("owner", "VOID_SHOP");
        set("exits", ([
                "down" : "/d/changan/majiu",
        ]));
        set("no_steal", 1);
        set("objects", ([
                __DIR__"waiter" : 1,
        ]));
        set("no_clean_up", 0);
        set("shop_type", 0);

        setup();
}