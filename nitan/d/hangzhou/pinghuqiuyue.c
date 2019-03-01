// pinghuqiuyue.c
// Date: Nov.1997 by Venus
#include <room.h>
inherit ROOM;
void create()
{
        set("short", "平湖秋月");
        set("long", @LONG
平湖秋月三面臨水，四面曲欄畫廊，直挹波際。曾有“萬頃湖平
長似鏡，四時月好最宜秋”的聯句來描寫這裡秋夜時皓月當空的幽美
景色。朝西北走便是放鶴亭。東北邊則是白堤。西邊就是孤山。
LONG);
        set("exits", ([
            "west"      : __DIR__"gushan",
            "northwest" : __DIR__"fangheting",
            "northeast" : __DIR__"baiti",
        ]));
        set("outdoors", "xihu");
        set("no_clean_up", 0);
	set("coor/x", 820);
	set("coor/y", -2030);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}