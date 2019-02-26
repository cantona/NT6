// liangongs.c 練功房

inherit ROOM;

void create()
{
        set("short", "南練功房");
        set("long", @LONG
這裏是南面的練功房，屋中立着一些練武者常用的木人。
LONG );
        set("exits", ([
                "north" : __DIR__"liangong",
        ]));
        set("for_family", "關外胡家");
        setup();
        replace_program(ROOM);
}
