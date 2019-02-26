//room: /d/yanziwu/cuixia.c
inherit ROOM;

void create()
{
        set("short","翠霞堂");
        set("long", @LONG
古樸莊嚴，氣度非凡，你一進門就不由的驚歎。好大一座廳堂！
 西邊彷彿有一間小廳，東邊則是一片竹林，南面有一道穿堂，不知通
向什麼地方。
LONG );
        set("exits",([
                "west" : __DIR__"xiaoting",
                "east" : __DIR__"zhulin1",
                "south": __DIR__"chuantang",
        ]));

        set("objects",([
                __DIR__"npc/azhu" : 1,
                __DIR__"npc/deng" : 1,
        ]));

        set("valid_startroom", 1);
        setup();
}

int valid_leave(object me, string dir)
{
        object guarder;

        if (dir != "east")
                return 1;

        if (guarder = present("deng baichuan", this_object()))
                return guarder->permit_pass(me, dir);

        return 1;
}