// baiti.c
// Date: Nov.1997 by Venus
#include <room.h>
inherit ROOM;
void create()
{
        set("short", "白堤");
        set("long", @LONG
白堤橫旦湖上，把西湖分成裡湖與外湖。堤上種滿了楊柳，碧桃。
每逢春至，“翩翩柳絲泛綠，樹樹桃顏帶笑”。白居易曾有“亂花漸
欲迷人眼，淺草才能沒馬蹄。最愛湖東行不足，綠楊蔭裡白沙堤。”
來描述這裡的景色。朝西南走過了錦帶橋便是“平湖秋月”。東邊則
是斷橋。
LONG);
        set("exits", ([
            "southwest" : __DIR__"pinghuqiuyue",
            "east"      : __DIR__"duanqiao",
        ]));
        set("outdoors", "xihu");
        set("no_clean_up", 0);
	set("coor/x", 830);
	set("coor/y", -2020);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}