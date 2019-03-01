inherit SHOP;

void create()
{
        set("short", "聽竹軒");
        set("long", @LONG
聽竹軒坐落于蘇州城北，雖稱之為軒，實際卻是一間裝潢
雅致的店舖。蘇州城建築別具一格，這家店舖也不例外。不過
貨櫃上卻空無一物，看樣子已很久沒人來打理了。
LONG);
        set("open_long", @LONG
聽竹軒坐落于蘇州城北，雖稱之為軒，實際卻是一間裝潢
雅致的店舖。蘇州城建築別具一格，這家店舖也不例外。此時
店堂伙計正忙上忙下，招呼著客人。
LONG);
        set("no_fight", 1);
        set("no_beg", 1);
        set("owner", "VOID_SHOP");
        set("exits", ([
                "down" : "/d/suzhou/majiu",
        ]));
        set("no_steal", 1);
        set("objects", ([
                __DIR__"waiter" : 1,
        ]));
        set("no_clean_up", 0);
        set("shop_type", 0);

        setup();
}
