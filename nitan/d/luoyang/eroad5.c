inherit ROOM;

void create()
{
        set("short", "永徽道");
        set("long", @LONG
再往西就要到西內城門了，遠遠望去，可以看見守城的官兵正在檢查
排隊出城的路人。因為這兒是十字街口，所以非常熱鬧。小商小販們在向
行人吆喝着，兜售他們的商品。北邊是衚衕，許多洛陽城的老百姓住在裏
面，南邊是一條幽靜的碎石小路。
LONG);
        set("outdoors", "luoyang");
        set("no_clean_up", 0);
        set("exits", ([
                  "east" : __DIR__"dongdoor",
                  "north" : __DIR__"hutong",
                  "south" : __DIR__"suishi1",
                  "west" : __DIR__"eroad4",
        ]));
        set("objects", ([
                "/d/taishan/npc/jian-ke" : 2,
        ]));
	set("coor/x", -6940);
	set("coor/y", 2150);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}