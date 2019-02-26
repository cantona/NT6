// Room: /tangmen/edajie.c
 

inherit ROOM;

void create()
{
        set("short", "東大街");
        set("long",
"這是一條寬闊的青石板街道，北邊是一個鋪子，裏面的老闆是唐門的\n"
"中人，買一些個雜物。南邊是一個銀號，據説是蜀中最老的錢莊了，而且\n"
"信譽不一般啊，很多中原來的商人都把錢存在這兒。\n"
);
        set("outdoors", "tangmen");
        set("no_clean_up", 0);
        set("exits", ([
                "west" : __DIR__"zhongxin",
                "south" : __DIR__"tsqianz",
                "north" : __DIR__"tjpuzi",
        ]));

        setup();
        replace_program(ROOM);
}
