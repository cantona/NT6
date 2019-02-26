#include <room.h>
inherit ROOM;

void create()
{
        set("short", "地安門西街廣場");
        set("long", @LONG
這裏是地安門的西街的廣場，地安門東西大街向兩頭延伸，這裏
也京城裏的繁華地段，是京城北邊的交通要道。廣場上熱鬧非凡，小
販們沿街叫賣着自己的貨物，其中也不乏夾雜着一些流氓混混。南邊
是京城的特務機構西廠的所在地。東邊就是地安門廣場了。
LONG );
       set("exits", ([
                "north" : "/d/beijing/di_5",
                "south" : "/d/beijing/di_2",
                "east" : "/d/beijing/dianmen",
                "west" : "/d/beijing/di_3",
        ]));
        set("objects", ([
                "/d/beijing/npc/xianren" : 1,
                "/d/beijing/npc/hunhun" : 1,
        ]));
        set("outdoors", "beijing");
	set("coor/x", -2810);
	set("coor/y", 7720);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}