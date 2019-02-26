// Room: /huanghe/huanghe4.c
// Java. Sep 21 1998

#include <room.h>

inherit ROOM;
void create()
{
        set("short", "黃河岸邊");
        set("long", @LONG
這裏是黃河岸邊。黃河流淌到這裏，已經泥沙渾濁了。黃色的河水
在河牀裏翻滾着，咆哮着，捲起一個個巨大的漩渦。黃河在這裏由於受
到東面泰山的阻擋，轉而向北。
LONG );
        set("exits", ([
                "west"      : __DIR__"huanghe3",
                "northeast" : __DIR__"huanghe5",
        ]));
        set("no_clean_up", 0);
        set("outdoors", "huanghe");
        set("coor/x", 150);
        set("coor/y", 520);
        set("coor/z", 0);
        setup();
        replace_program(ROOM);
}
