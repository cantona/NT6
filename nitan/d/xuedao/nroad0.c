inherit ROOM;

void create()
{
        set("short", "山路");
        set("long", @LONG
山路越走越窄，能隱隱望見前方又分出了幾條叉路。
LONG );
        set("exits", ([
                "south" : __DIR__"sroad0",
                "north" : __DIR__"nroad1",
        ]));
        set("outdoors", "xuedao");
        setup();
        replace_program(ROOM);
}
