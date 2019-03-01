// Room: /d/huangshan/taoyuan.c
// Last Modified by winder on Sep. 27 2001

inherit ROOM;
void create()
{
        set("short", "桃源亭");
        set("long", @LONG
這裡位于桃花峰上，周圍溪流環繞，宛若仙居，故稱桃源亭，此處
最佳之處在于可以靜心欣賞黃山三名瀑之一的“人字瀑”，遠看過去，
瀑布傾泄，恰好是個人字，煞是有趣。
LONG
        );
        set("exits", ([ 
                "east" : __DIR__"ciguang",
        ]));
        set("objects", ([
                __DIR__"obj/ting" : 1,
        ]) );
        set("outdoors", "huangshan");
        set("coor/x", -605);
        set("coor/y", -1090);
        set("coor/z", -10);
        setup();
        replace_program(ROOM);
}