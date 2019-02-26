// Room: /tangmen/bdajie1.c

inherit ROOM;

void create()
{
        set("short", "北大街");
        set("long",
"一條筆直的大理石街道，兩邊的店鋪可是好地方。東邊不時地傳來小\n"
"二吆喝聲：買了、買了、快來買了。讓你忍不住想進去看看。西邊只不停\n"
"的傳來馬嘶聲，你想那邊會是什麼啊？對了，就是驛站了！能去很多的地\n"
"方啊。\n"
);
        set("outdoors", "tangmen");
        set("no_clean_up", 0);
        set("exits", ([
                "east"  : __DIR__"kedian",
                "south" : __DIR__"zhongxin",
                "west"  : __DIR__"tmyizhan",
                "north" : __DIR__"bdajie2",
        ]));

        setup();
        replace_program(ROOM);
}
