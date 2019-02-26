// Room: /d/songshan/houting.c
// Last Modified by Winder on Jul. 15 2001

inherit ROOM;

void create()
{
        set("short", "後庭");
        set("long", @LONG
這裏是峻極禪院花院內的後庭。庭院中青石鋪地、古柏森森，四周
是本派首腦人物的起居之處，向來少有人來。北面是獨尊壇。
LONG );
        set("exits", ([
                "north" : __DIR__"duzuntan",
                "south" : __DIR__"huayuan",
                "east"  : __DIR__"woshi",
                "west"  : __DIR__"danfang",
        ]));
        set("objects", ([
                __DIR__"npc/ding": 1,
        ]));
        set("outdoors", "songshan");
        set("coor/x", -20);
        set("coor/y", 930);
        set("coor/z", 90);
        setup();
        replace_program(ROOM);
}