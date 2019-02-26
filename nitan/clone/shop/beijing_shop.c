inherit SHOP;

void create()
{
        set("short", "聚寶堂");
        set("long", @LONG
這裏便是北京城裏最有名的聚寶堂，鋪里人來人往，川流
不息，顯出天子之都繁華大方的氣派。不過店裏的貨櫃上卻空
無一物，看樣子已經很久沒人來打理了。
LONG);
        set("open_long", @LONG
這裏便是北京城裏最有名的聚寶堂，鋪里人來人往，川流
不息，顯出天子之都繁華大方的氣派。鋪面寬敞明亮，櫃上擺
滿了各式各樣、琳琅滿目的貨物。
LONG);
        set("no_fight", 1);
        set("no_beg", 1);
        set("owner", "VOID_SHOP");
        set("exits", ([
                "down" : "/d/beijing/majiu",
        ]));
        set("no_steal", 1);
        set("objects", ([
                __DIR__"waiter" : 1,
        ]));
        set("no_clean_up", 0);
        set("shop_type", 0);

        setup();
}