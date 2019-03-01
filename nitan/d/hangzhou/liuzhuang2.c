// liuzhuang2.c

#include <room.h>

inherit ROOM;

void create()
{
        set("short", "劉莊側院");
        set("long", @LONG
這裡是劉莊旁邊的院子，你走到這裡不禁有些驚奇，居然擺了幾
個江湖上練武之人才用的練功木人，旁邊有幾個護院家丁模樣的人坐
在一旁指手畫腳的不知道在說些什麼。
LONG);
        set("exits", ([
            "south" : __DIR__"liuzhuang",
        ]));
        set("objects", ([
                __DIR__"npc/jiading" : 2,
                "/clone/npc/mu-ren" : 3,
        ]));
	set("coor/x", 770);
	set("coor/y", -2070);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}