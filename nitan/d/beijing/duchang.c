#include <room.h>
inherit ROOM;

void create()
{
        set("short", "宏升賭場");
        set("long", @LONG
這裏就是北京城中最大的宏升賭場，四周的賭房裏傳出來吆五喝
六的賭博聲。這個賭場規模雖算不上很大， 但賭的種類卻很齊全， 
服務也非常周到。在這兒， 世上的各行各色的人夾雜在一起， 有腰
盤萬貫的富家子弟， 也有窮得叮噹響的窮漢。有拿刀佩劍的的江湖俠
客， 也有掉兒啷噹的流氓地痞。有官府的侍衞， 也有在逃的犯人。
LONG );
       set("exits", ([
                "south" : "/d/beijing/yong_1",
        ]));
        set("objects", ([
                "/d/beijing/npc/duke" : 2,
                "/d/beijing/npc/liumang" : 1,
                "/d/beijing/npc/haoke1" : 1,
                "/d/beijing/npc/dipi" : 1,
        ]));
        set("outdoors", "beijing");
	set("coor/x", -2790);
	set("coor/y", 7660);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}