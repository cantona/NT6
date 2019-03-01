inherit ROOM;

void create()
{
        set("short", "土路");
        set("long", @LONG
這是一條不起眼的土路，卻是連接雪山寺與中原的必經之路。西
邊點點的炊煙依稀可見。往北可以通往雪山寺。
LONG );
        set("outdoors", "xuedao");
        set("exits", ([
                "east" : __DIR__"tulu1",
                "north" : __DIR__"tulu3",
                "west" : __DIR__"kedian",
        ]));
        setup();
        replace_program(ROOM);
}