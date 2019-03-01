// /d/quanzhen/shanlu12.c
// Java Oct.10 1998

inherit ROOM;

void create()
{
        set("short", "山道");
        set("long", @LONG
此段山路是沿着峭壁而開鑿出來的，特別崎嶇難行。有時峭壁邊
必須面貼山璧，側身而過。尤其當山鳳吹來時，更需特別小心，不然
一失足，就要掉進萬丈深淵了。往北是一塊廣大的空地。往南下是一
塊巨巖。
LONG
        );
        set("outdoors", "zhongnan");
        set("exits", ([
                "northup"    : __DIR__"daxiaochang",
                "southdown"  : __DIR__"juyan",
        ]));

        set("coor/x", -3170);
        set("coor/y", 100);
        set("coor/z", 110);
        setup();
        replace_program(ROOM);
}