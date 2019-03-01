inherit ROOM;

void create()
{
        set("short", "後村山路");
        set("long", @LONG
這是一條蜿蜒的泥土小路，是通向後山的唯一的道路，路
兩旁開滿不知名的野花，陣陣花香飄過，真是一片美麗的田園
風光。但隨著山勢越來越高，路也漸漸難走起來。
LONG);
        set("exits", ([
                "west" : __DIR__"houcun-road",
                "east" : __DIR__"luanshigang",
        ]));

        set("xinshoucun", 1);
        set("outdoors", "newbie");

        set("objects", ([
                "/clone/quarry/tu" : 20+random(20),
        ]));
        setup();

        replace_program(ROOM);
}