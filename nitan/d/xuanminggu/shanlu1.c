inherit ROOM;

void create()
{
        set("short", "山路");
        set("long", @LONG
這是玄冥峯的山路，四周樹木高聳，走獸成羣。
LONG );
        set("exits", ([
                "southeast"  : __DIR__"shanjiao",
                  "northwest"  : __DIR__"xiaolu2",
        ]));

        set("outdoors", "xuanming");
        setup();
        replace_program(ROOM);
}
