inherit ROOM;

void create()
{
        set("short", "土路");
        set("long", @LONG
這是一條不起眼的土路。塵埃泛起的遠方，北邊波光瀲灩的一大
片幽藍水光處，就是著名的聖湖。
LONG );
        set("outdoors", "xuedao");
        set("exits", ([
                "south" : __DIR__"tulu2",
                "north" : __DIR__"shenghu",
        ]));
        setup();
}