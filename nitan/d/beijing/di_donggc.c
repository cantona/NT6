#include <room.h>
inherit ROOM;

void create()
{
        set("short", "地安門東街廣場");
        set("long", @LONG
這裏是地安門的東街的廣場，地安門東西大街向兩頭延伸，這裏
也京城裏的繁華地段，是京城北邊的交通要道。廣場上熱鬧非凡，小
販們沿街叫賣着自己的貨物，其中也不乏夾雜着一些流氓混混。南邊
是京城的特務機構東廠的所在地。西邊是地安門廣場，東邊接京城著
名的王府井大街。
LONG );
       set("exits", ([
                "north" : "/d/beijing/dong_2",
                "south" : "/d/beijing/dong_1",
                "east" : "/d/beijing/wang_9",
                "west" : "/d/beijing/dianmen",
        ]));
        set("objects", ([
                "/d/beijing/npc/liumang" : 1,
                "/d/beijing/npc/kid1" : 1,
                "/d/beijing/npc/girl2" : 1,
        ]));
        set("outdoors", "beijing");
	set("coor/x", -2790);
	set("coor/y", 7720);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}