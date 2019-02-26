// cuipingfeng.c 翠屏峯頂
// Winder Oct.10 1998

inherit ROOM;

void create()
{
        set("short", "翠屏峯頂");
        set("long", @LONG
這裏是翠屏峯的峯頂。翠屏峯是終南山的第一峯，也是最矮的一
個山峯。懸崖邊建有一個小亭子，你走進亭中憑攔遠望，遠處的山間
白雲漂浮繚繞，好像修築着什麼建築，山景清麗，可惜被白雲盡遮住
了。幾個遊客也在亭中歇腳，正嘖嘖讚美着此地美景。
LONG
        );
        set("outdoors", "zhongnan");
        set("exits", ([
                "southdown" : __DIR__"baishulin3",
        ]));
        set("objects",([
                __DIR__"npc/youke" : 2,
        ]));

        set("coor/x", -3140);
        set("coor/y", 50);
        set("coor/z", 50);
        setup();
        replace_program(ROOM);
}