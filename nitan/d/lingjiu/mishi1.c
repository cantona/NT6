inherit ROOM;

void create()
{
        set("short", "密室");
        set("long", @LONG
這是個陰暗的密室，牆上的油燈發出昏暗的黃光。
LONG );
        set("exits", ([
                "south" : __DIR__"midao13",
                "north" : __DIR__"midao14",
                "east" : __DIR__"midao14",
                "up" : __DIR__"huayuan",
        ]));
        setup();
        replace_program(ROOM);
}