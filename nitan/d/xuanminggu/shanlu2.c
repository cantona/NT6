inherit ROOM;

void create()
{
        set("short", "山路");
        set("long", @LONG
這是玄冥峯的山路，四周樹木高聳，走獸成羣。
LONG );
        set("exits", ([
                "northup"    : __DIR__"shanlu3",
                  "southeast"    : __DIR__"zulin1",
        ]));

        set("outdoors", "xuanming");
        setup();
        replace_program(ROOM);
}
