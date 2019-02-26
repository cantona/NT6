#include <room.h>
#include <ansi.h>
inherit ROOM;

void create()
{
        set("short","金水橋");
        set("long", @LONG
一座不大的拱橋，橫架在紫禁城的護城河兩岸，通過金水橋向北
走便是紫禁城的正門了，那裏守衞森嚴，堅實的城牆高高的聳立着。
橋的南面是著名的天安門廣場，在這便可以聽見嘈雜的人聲，過往穿
梭其中的人們絡繹不絕，熱鬧非凡。
LONG );
        set("exits", ([
                "south" : "/d/beijing/tiananmen",
                "north" : "/d/beijing/hgmen_s",
        ]));
        set("objects", ([
                "/d/beijing/npc/bing1" : 2,
                "/d/beijing/npc/xiaofan" : 1,
        ]));
        set("outdoors", "beijing");
	set("coor/x", -2800);
	set("coor/y", 7680);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}