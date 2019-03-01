inherit SHOP;

void create()
{
        set("short", "殘月樓");
        set("long", @LONG
成都號稱天府之國，物產豐盛，富甲一時。整個店舖裝潢
雅致，看得出店主是費了一番心思的，不過店裡的貨櫃上卻空
無一物，看樣子已經很久沒人來打理了。
LONG);
        set("open_long", @LONG
成都號稱天府之國，物產豐盛，富甲一時。這家殘月樓出
售各式各樣的稀有物品，都是在別地難于購買的。整個店舖裝
潢雅致，看得出店主是費了一番心思的。
LONG);
        set("no_fight", 1);
        set("no_beg", 1);
        set("owner", "VOID_SHOP");
        set("exits", ([
                "down" : "/d/chengdu/majiu",
        ]));
        set("no_steal", 1);
        set("objects", ([
                __DIR__"waiter" : 1,
        ]));
        set("no_clean_up", 0);
        set("shop_type", 0);

        setup();
}