//bingqifang.c                四川唐門─兵器房

inherit ROOM;

void create()
{
        set("short", "兵器房");
        set("long",
"這裡是蜀中唐門的兵器房，房間很大卻充滿了一股蕭殺之氣，靠牆擺\n"
"放著幾個兵器架，其中一個架子上面擺放著一些唐門秘制的暗器和兵器，\n"
"其它的幾個架子上則是江湖中常用的兵器。\n"
);
        set("exits", ([
                "south" : __DIR__"nzlange2",
        ]));
        set("objects", ([
                "/clone/weapon/changjian" : 4
        ]));

        set("no_fight", 1);
        set("area", "tangmen");        
        setup();
        replace_program(ROOM);
}