inherit ROOM;

void create()
{
        set("short", "岔路");
        set("long", @LONG
這是一條小岔路，東面不遠是唐家堡的主路，不是還能看到
幾個行色匆匆的人來往，西面是高聳的山壁，一條羊腸小路沿著
山壁彎彎曲曲的向遠方延伸。
LONG
        );
        set("exits", ([ /* sizeof() == 2 */
        "northwest" : __DIR__"ycl1",
        "east" : __DIR__"gd2",
        "west" : __DIR__"syang",
        "south" : __DIR__"tuzai1",
]));

        set("outdoors", "yaowang");
        setup();
        replace_program(ROOM);
}
