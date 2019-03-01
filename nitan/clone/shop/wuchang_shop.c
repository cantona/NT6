// /clone/shop/wuchang_shop.c
// Last modified by winder 2003.10.20

inherit SHOP;

void create()
{
        set("short", "悅新昌");
        set("no_fight", 1);
        set("no_beg", 1);
        set("owner", "VOID_SHOP");
        set("exits", ([
                "down" : "/d/wuchang/majiu",
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
悅新昌是落于長江邊上，是一間裝潢雅致的店舖。江城樓宇別具一
格，這家店舖也不例外。不過貨櫃上卻空無一物，看樣子已很久沒人來
打理了。
LONG);
        else
                set("long", @LONG
悅新昌坐落于長江邊上，是一間裝潢雅致的店舖。江城樓宇別具一
格，這家店舖也不例外。此時店堂伙計正忙上忙下，招呼著客人。
LONG);
        return;
}
