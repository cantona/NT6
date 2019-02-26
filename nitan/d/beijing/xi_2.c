#include <room.h>
inherit ROOM;

void create()
{
        set("short", "西單");
        set("long", @LONG
這裏就是西單，西單也是京城裏的繁華地段。人來人往，十分熱
鬧。遊人雖然多，但大都只四處晃悠，着東瞅瞅西看看，也不急着買
什麼。從右邊飄來一陣濃濃的藥材氣味，那裏就是著名的『回春堂』
藥鋪了。不斷有人從北邊走來，似乎那裏也挺熱鬧。南邊則是京城裏
的西長安大街。
LONG );
       set("exits", ([
                "east" : "/d/beijing/huichuntang",
                "west" : "/d/beijing/xi_1",
                "north" : "/d/beijing/bei_2",
                "south" : "/d/beijing/caroad_w2",
        ]));
        set("objects", ([
                "/d/beijing/npc/boy3" : 1,
                "/d/beijing/npc/xiaofan" : 1,
                "/d/beijing/npc/girl2" : 1,
        ]));
        set("outdoors", "beijing");
	set("coor/x", -2820);
	set("coor/y", 7680);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}