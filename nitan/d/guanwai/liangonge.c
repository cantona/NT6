// liangonge.c 練功房

inherit ROOM;

void create()
{
        set("short", "東練功房");
        set("long", @LONG
這裡是東面的練功房，屋中立著一些練武者常用的木人。
LONG );
        set("exits", ([
                "west" : __DIR__"liangong",
        ]));
        set("for_family", "關外胡家");
        setup();
        replace_program(ROOM);
}