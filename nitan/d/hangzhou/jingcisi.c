// jingcisi.c
// Date: Nov.1997 by Venus
#include <room.h>
inherit ROOM;
void create()
{
        set("short", "凈慈寺");
        set("long", @LONG
凈慈寺，原名慧日永明院，又叫興教寺。凈慈寺面向西湖，後擁
蒼然挺秀的南屏山。往北就回到大道上。
LONG);
        set("exits", ([
            "north"   : __DIR__"road16",
            "enter"   : __DIR__"jingci",
        ]));
        set("no_clean_up", 0);
	set("coor/x", 800);
	set("coor/y", -2100);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}