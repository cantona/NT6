inherit ROOM;

void create()
{
        set("short", "後村小路");
        set("long", @LONG
這是一條蜿蜒的青石舖就的小路，是通向後山的唯一的道
路，路兩旁開滿不知名的野花，陣陣花香飄過，真是一片美麗
的田園風光。
LONG);
        set("exits", ([
                "west" :  __DIR__"lianwuchang",
                "east" : __DIR__"houcun-shanlu",
        ]));

        set("xinshoucun", 1);
        set("outdoors", "newbie");

        set("objects", ([
                "/clone/quarry/tu" : 20 + random(20),
        ]));
        setup();

        replace_program(ROOM);
}
