// ROOM: /xiakedao/shidong1.c
inherit ROOM;

void create()
{
        set("short", "石洞");
        set("long", @LONG
這是一個石洞，也不知走了多久，只覺越走越低，洞中出現了
流水之聲，淙淙爭爭，清脆悅耳，如擊玉磬。
LONG );
        set("exits", ([
               "east" : __DIR__"dongmen",
               "north" : __DIR__"yongdao2",
               "south" : __DIR__"shidong6",
        ]));
        set("no_clean_up", 0);
        set("coor/x", -3100);
        set("coor/y", -22080);
        set("coor/z", 0);
        setup();
        replace_program(ROOM);
}