inherit ROOM;

void create()
{
        set("short", "客店");
        set("long", @LONG
這裏是一個路邊的小客店。來往的行人都在這裏稍事休息。往東
的路可以到達中原。
LONG );
        set("exits", ([
                "east" : __DIR__"tulu2",
        ]));
        set("objects", ([
                __DIR__"npc/xiaoer2" :1
        ]));
        setup();
        replace_program(ROOM);
}