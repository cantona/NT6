// Room: /d/xiakedao/xiaodian.c
// xiao dian in xiakedao
// YZC 1995/12/04
// arnzh 97/1/24
inherit ROOM;

void create()
{
        set("short", "小吃店");
        set("long", @LONG
這個小吃店佈置簡易，空空的石壁什麼也沒有，但生意卻很好。
顧客多是匆匆的江湖人，買點包子、雞腿、米酒就趕路去了。
LONG );
        set("exits", ([
                "west" : __DIR__"yingbin",
        ]));
        set("objects", ([
                __DIR__"npc/xiaoer2" : 1,
        ]));
        set("no_clean_up", 0);
        set("coor/x", -3070);
        set("coor/y", -22080);
        set("coor/z", 0);
        setup();
        replace_program(ROOM);
}