// baoshuta.c
// Date: Nov.1997 by Venus
#include <room.h>
inherit ROOM;
void create()
{
        set("short", "保淑塔");
        set("long", @LONG
保淑塔姿態秀麗挺拔，塔基極小，卻負荷了極高的塔身。傳說吳
越王錢弘淑奉召入京，久留未返，他大臣吳延爽為祝原其平安歸來，
而建此塔，故名保淑塔。往南是下山的路。
LONG);
        set("exits", ([
            "southdown" : __DIR__"baoshishan",
        ]));
        set("outdoors", "xihu");
        set("no_clean_up", 0);
	set("coor/x", 810);
	set("coor/y", -1980);
	set("coor/z", 20);
	setup();
        replace_program(ROOM);
}