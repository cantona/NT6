// liangong.c 練功房

inherit ROOM;

void create()
{
        set("short", "練功房");
        set("long", @LONG
這裡是練功房，屋中立著一些練武者常用的木人。東面似乎還有
一間房子。
LONG );
        set("exits", ([
                "east" : __DIR__"liangonge",
                "west" : __DIR__"houyuan",
                "south": __DIR__"liangongs",
        ]));
        set("for_family", "關外胡家");
        setup();
        replace_program(ROOM);
}