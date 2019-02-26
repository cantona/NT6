#include <room.h>
#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", "地安門");
        set("long", @LONG
這裏是是紫禁城地安門，高大的城門正上方刻着『地安門』三個
大字，厚實堅固的古城牆高高聳立着。城門兩旁整齊的站着幾個衞兵，
仔細的監守着這裏。南方由地安門大街通往京城的中心。
LONG );
        set("exits", ([
                "south" : "/d/beijing/di_dajie2",
                "north" : __DIR__"anding",
        ]));
        set("objects", ([
                "/d/beijing/npc/ducha" : 1,
                "/d/beijing/npc/bing2" : 1,
                "/d/beijing/npc/bing3" : 1,
        ]));
        set("outdoors", "beijing");
	set("coor/x", -2800);
	set("coor/y", 7750);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}