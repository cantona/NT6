// Room: /tangmen/zhongxin.c

inherit ROOM;

void create()
{
        set("short", "唐家鎮中心");
        set("long",
"這裏是唐家鎮的正中心，一個很寬闊的廣場，鋪着青石地面。往來的\n"
"行人大都是唐門的弟子，有許多來自中原的商家在這兒做一些小買賣，人\n"
"聲沸騰，真是一片繁華景象。這裏通向唐家鎮的各條大街。\n"
);
        set("no_sleep_room",1);
        set("outdoors", "tangmen");
        set("no_clean_up", 0);
        set("exits", ([
                "east"  : __DIR__"edajie",
                "south" : __DIR__"ndajie",
                "west"  : __DIR__"xdajie",
                "north" : __DIR__"bdajie1",
        ]));
        set("objects", ([
                __DIR__"npc/shangren" : 1,
                __DIR__"npc/dizi" : 1,
                __DIR__"npc/boy" : 1,
        ]));
        setup();
}
