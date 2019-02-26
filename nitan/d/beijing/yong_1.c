#include <room.h>
inherit ROOM;

void create()
{
        set("short", "永內東街");
        set("long", @LONG
永內東街是一條繁華的大街，也是北京最雜亂的地段。一條寬闊
的青石大道從中穿過，向東西兩頭延伸。西邊是京城裏著名的凡陛橋。
北面是一家豪華的大賭場，此時正從裏面傳來一陣陣不堪入耳的聲音。
南邊是匯英酒樓，在京城中，也算是小有名氣的。
LONG );
        set("exits", ([
                "south" : "/d/beijing/huiying",
                "north" : "/d/beijing/duchang",
                "east" : "/d/beijing/yong_2",
                "west" : "/d/beijing/tianqiao",
        ]));
        set("objects", ([
                "/d/beijing/npc/dipi" : 1,
                "/d/beijing/npc/boy1" : 1,
        ]));
        set("outdoors", "beijing");
	set("coor/x", -2790);
	set("coor/y", 7650);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}