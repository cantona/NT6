inherit ROOM;

void create()
{
        set("short", "紫金城");
        set("long", @LONG
這是守護金殿的紫金城牆，周長三裏，城牆由花崗石依山勢砌成，
東西北城門均面臨絕壁，南門為上下路口，氣勢壯觀。
LONG );
        set("exits", ([
                "north" : __DIR__"jinding",
                "south" : __DIR__"jindian",
        ]));
        set("outdoors", "wudang");
        set("no_clean_up", 0);
        set("coor/x", -350);
        set("coor/y", -430);
        set("coor/z", 180);
        setup();
        replace_program(ROOM);
}