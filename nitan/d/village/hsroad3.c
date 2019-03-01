// hsroad3.c
// by Xiang

inherit ROOM;

void create()
{
        set("short", "黃土路");
        set("long", @LONG
一條坑坑窪窪的土路，彎彎曲曲的通向山裡。
LONG );
        set("outdoors", "village");
        set("exits", ([
                "southeast" : __DIR__"hsroad2",
                "north"     : __DIR__"sexit",
        ]));
        set("objects", ([
                "/d/taishan/npc/tangzi" : 4,
        ]));

        setup();
        replace_program(ROOM);
}
