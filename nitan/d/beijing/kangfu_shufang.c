#include <room.h>
inherit ROOM;

void create()
{
        set("short", "康親王書房");
        set("long", @LONG
這裡是康親王書房，房中書架上整整齊齊地堆放著很多書。不過
書上積了一些灰塵，顯然是很久沒有動過了。而書櫥裡的幾件精巧玉
器卻更顯得玲瓏剔透，光彩照人。
LONG );
        set("exits", ([
                "south" : "/d/beijing/kangfu_zoulang2",
        ]));

        set("outdoors", "beijing");
	set("coor/x", -2800);
	set("coor/y", 7730);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}