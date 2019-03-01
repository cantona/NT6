// qinglindong.c
// Date: Nov.1997 by Venus
#include <room.h>
inherit ROOM;
void create()
{
        set("short", "清林洞");
        set("long", @LONG
又叫老虎洞。只見靠右雕有弭陀，觀音，大勢至三尊小佛。洞口
東側壁上還刻着一組“廬舍那佛會”浮雕，它上刻花頭龕，中間坐着
釋迦牟尼，左右分列文殊，普賢，還有天王佛像。西邊是下山的路。
小路往上延伸向東。
LONG);
        set("exits", ([
                "eastup"    : __DIR__"cuiweiting",
                "westdown"  : __DIR__"feilaifeng",
        ]));
        set("objects", ([
                "/clone/npc/walker" : 1,
        ]));
        set("outdoors", "hangzhou");
        set("no_clean_up", 0);
	set("coor/x", 750);
	set("coor/y", -2070);
	set("coor/z", 10);
	setup();
        replace_program(ROOM);
}