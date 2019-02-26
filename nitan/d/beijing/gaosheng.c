#include <room.h>
inherit ROOM;

void create()
{
        set("short", "高升茶館");
        set("long", @LONG
一座規模不小的茶館，門前的幡上舞着『高升』兩個大字。你剛
進來，就聞到一股茶香沁入心脾，精神為之一爽。幾張八仙桌一字排
開，坐滿了客人，或高聲談笑，或交頭接耳。茶博士搖頭晃腦的説着
書，茶鋪的夥計忙個不停。你要想打聽江湖掌故和謠言，這裏是個好
所在。
LONG );
       set("exits", ([
                "north" : "/d/beijing/caroad_w2",
        ]));
        set("objects", ([
                "/d/beijing/npc/chaboshi" : 1,
                "/d/beijing/npc/teahuoji" : 1,
                "/d/beijing/npc/chake" : 2,
                "/d/beijing/npc/old2" : 1,
        ]));
        set("outdoors", "beijing");
	set("coor/x", -2820);
	set("coor/y", 7660);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}