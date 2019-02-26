#include <room.h>
inherit ROOM;

void create()
{
        set("short", "楊柳衚衕");
        set("long", @LONG
這裏是楊柳衚衕的衚衕口，深深的巷道朝着南邊曲折的延伸下去，
旁晚時分，衚衕口不遠的西邊炊煙渺渺，似是居住着幾户人家。只見
北方塵土飛揚，馬蹄聲和吆喝聲相互穿插，那裏便是貫穿京城的長安
大街。
LONG );
       set("exits", ([
                "north" : "/d/beijing/caroad_w1",
                "south" : "/d/beijing/yangliu2",
                "west" : "/d/beijing/minju_y",
        ]));
        set("objects", ([
                "/d/beijing/npc/old1" : 1,
        ]));
        set("outdoors", "beijing");
	set("coor/x", -2830);
	set("coor/y", 7660);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}