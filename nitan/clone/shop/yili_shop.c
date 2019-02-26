// /clone/shop/yili_shop.c
// Last modified by winder 2003.10.20

inherit SHOP;

void create()
{
        set("short", "牛大碗");
        set("no_fight", 1);
        set("no_beg", 1);
        set("owner", "VOID_SHOP");
        set("exits", ([
                "down" : "/d/xingxiu/majiu",
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
來往於牛大碗的多是商富大賈。樓內裝潢得非常典雅精緻，堪稱蘭
州城內一絕。紅木鋪地，漆門雕窗，大堂正中掛着一幅百鶴圖。不過貨
櫃上卻空無一物，看樣子已很久沒人來打理了。
LONG);
        else
                set("long", @LONG
來往於牛大碗的多是商富大賈。樓內裝潢得非常典雅精緻，堪稱蘭
州城內一絕。紅木鋪地，漆門雕窗，大堂正中掛着一幅百鶴圖。此時店
堂夥計正忙上忙下，招呼着客人。
LONG);
        return;
}
