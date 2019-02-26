#include <room.h>
inherit ROOM;

void create()
{
        set("short", "永內東街");
        set("long", @LONG
永內東街是一條繁華的大街，也是北京最雜亂的地段。一條寬闊
的青石大道從中穿過，向東西兩頭延伸。西邊是京城裏著名的凡陛橋。
LONG );
        set("exits", ([
                "west" : "/d/beijing/yong_2",
                "south" : "/d/beijing/zsh_bjdamen",
        ]));

        set("objects", ([
               "/clone/npc/walker"  : 1,
        ]));
        set("outdoors", "beijing");
	set("coor/x", -2770);
	set("coor/y", 7650);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}