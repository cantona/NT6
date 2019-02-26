inherit ROOM;

void create()
{
        set("short", "山路");
        set("long", @LONG
這是玄冥峯的山路，四周樹木高聳，走獸成羣。
LONG );
        set("exits", ([
                "northup"      : __DIR__"xuanmingfeng",
                "southeast"    : __DIR__"xuanminggu",
        ]));

        set("outdoors", "xuanming");
        setup();
        replace_program(ROOM);
}
