// longhongdong.c
// Date: Nov.1997 by Venus
#include <room.h>
inherit ROOM;
void create()
{
        set("short", "龍泓洞");
        set("long", @LONG
又叫通天洞。在洞口的巖壁上刻有姿態各異，一丈多高的佛像六
尊。左下方有兩組浮雕。前一組記述了唐僧取經的故事；後一組為白
馬馱經，刻有“竺法闌”，“聶摩騰”字樣。東邊是下山的路。小路
往上延伸向西北。
LONG);
        set("exits", ([
                "northwest" : __DIR__"shexudong",
                "eastdown"  : __DIR__"feilaifeng",
        ]));

        set("outdoors", "hangzhou");
        set("no_clean_up", 0);
	set("coor/x", 730);
	set("coor/y", -2070);
	set("coor/z", 10);
	setup();
        replace_program(ROOM);
}