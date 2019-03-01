#include <room.h>
inherit ROOM;

void create()
{
        set("short", "永內東街");
        set("long", @LONG
永內東街是一條繁華的大街，也是北京最雜亂的地段。一條寬闊
的青石大道從中穿過，向東西兩頭延伸。西邊是京城裡著名的凡陛橋。
從北邊飄來一陣陣誘人的花香，頓時你的精神為之一振。南邊是一個
打鐵舖， 不時傳來叮叮咚咚的敲打聲。
LONG );
        set("exits", ([
                "south" : "/d/beijing/tiepu",
                "north" : "/d/beijing/huadian",
                "east" : "/d/beijing/yong_3",
                "west" : "/d/beijing/yong_1",
        ]));

        set("outdoors", "beijing");
	set("coor/x", -2780);
	set("coor/y", 7650);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}