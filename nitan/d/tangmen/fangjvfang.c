//fangjvfang.c                四川唐門—防具房

inherit ROOM;

void create()
{
        set("short", "防具房");
        set("long",
"這裏是蜀中唐門的防具房，房間很大，靠牆擺放着幾個木架，上面掛\n"
"着一些防護用具，可以用來防止在練習中傷到自己。其中最具特色的，莫\n"
"過於那套唐門獨有的鹿皮手套。\n"
);
        set("exits", ([
                "north" : __DIR__"nzlange2",
        ]));
        set("objects", ([
                "/d/city/npc/obj/tiejia" : 4
        ]));

        set("no_fight", 1);
        set("area", "tangmen");        
        setup();
        replace_program(ROOM);
}