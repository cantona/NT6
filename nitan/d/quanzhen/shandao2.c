// /d/quanzhen/shandao2.c
// Java Oct.10 1998

inherit ROOM;

void create()
{
        set("short", "山道");
        set("long", @LONG
此段山路是沿着峭壁而開鑿出來的，特別崎嶇難行。有時峭壁邊
必須面貼山璧，側身而過。尤其當山鳳吹來時，更需特別小心，不然
一失足，就要掉進萬丈深淵了。往東南是一塊廣大的空地。往北下通
往後山腳，遠遠可以望見一個較大的湖。
LONG
        );
        set("outdoors", "zhongnan");
        set("exits", ([
                "southup"   : __DIR__"shandao1",
                "northdown" : __DIR__"shulin4",
        ]));

        set("coor/x", -3190);
        set("coor/y", 130);
        set("coor/z", 120);
        setup();
        replace_program(ROOM);
}