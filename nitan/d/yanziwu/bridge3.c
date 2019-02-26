// Room: /d/yanziwu/bridge3.c
// Date: Jan.28 2000 by Winder

#include <ansi.h>;
inherit ROOM;

void create()
{
        set("short", "十二回欄");
        set("long", @LONG
十二回欄是一座通往蓮韻塘中倦心亭的十二曲橋。橋墩和欄杆均為
石砌，橋面卻是圓木鋪張着。透過數指寬的木間隙，可以看到橋下清清
的水、紅紅的荷、和跳動着的蛙。
LONG );
        set("outdoors", "mantuo");
        set("no_clean_up", 0);
        set("exits", ([
                "north"  : __DIR__"path16",
                "south"  : __DIR__"juanxin",
        ]));
        set("coor/x", 1220);
        set("coor/y", -1210);
        set("coor/z", 0);
        setup();
        replace_program(ROOM);
}