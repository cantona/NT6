#include <room.h>
inherit ROOM;

void create()
{
        set("short", "鳥市");
        set("long", @LONG
你一走到這裡，便聽見了許許由各種各樣鳥兒輕脆的叫聲編織成
的動聽的梵籟。你可以看到很多京城裡衣著華麗的公子哥兒在這裡精
挑細選，一個個油頭粉面，平時無事可作，就靠這些來打發著混日子。
LONG );
       set("exits", ([
                "east" : "/d/beijing/xi_1",
                "west" : "/d/beijing/majiu",
        ]));
        set("objects", ([
                "/d/beijing/npc/richman1" : 1,
                "/d/beijing/npc/shusheng2" : 1,
        ]));
        set("outdoors", "beijing");
	set("coor/x", -2840);
	set("coor/y", 7680);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}