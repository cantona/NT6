#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", "兵器庫大門");
        set("long", @LONG
你正站在荊州兵器庫的門口，可以看到兩個穿着制服的官兵正在
此地巡邏，不時地傳來吶喊聲。老百姓是不允許在此觀看的，你最好
趕快走開。
LONG );
        set("exits", ([
                "east" : __DIR__"nandajie2",
        ]));
        set("objects", ([
                "/d/city/npc/bing" : 2,
        ]));

        set("coor/x", -7110);
	set("coor/y", -2070);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}