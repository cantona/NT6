// /d/quanzhen/baoziyan.c
// Java Oct.10 1998

inherit ROOM;

void create()
{
        set("short", "抱子巖");
        set("long", @LONG
一路過來，山路是越來越險。只見光禿禿的山路，左旁盡是怪石，
而右則是萬丈深淵，渺不見底。前方不遠處的一塊巨石，便是有名的
抱子巖。再看幾眼，覺那巖生得甚是奇怪，就如一個婦人抱著個孩子
般，細心呵護。往南和西各是一片密林。
LONG
        );
        set("outdoors", "zhongnan");
        set("exits", ([
                "west"      : __DIR__"shulin2",
                "south"     : __DIR__"shulin1",
        ]));
        set("objects", ([
                CLASS_D("quanzhen")+"/chen": 1,
        ]));

        set("coor/x", -3150);
        set("coor/y", 60);
        set("coor/z", 90);
        setup();
        replace_program(ROOM);
}