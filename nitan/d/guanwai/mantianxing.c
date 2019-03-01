// /guanwai/mantianxing.c

inherit ROOM;

void create()
{
        set("short", "滿天星");
        set("long", @LONG
這裡是一片開闊的平原，附近不但沒有任何小山丘陵，就連一棵樹也找
不到。抬眼望去，地平線筆直的將藍天與雪原分隔在兩邊。據說夜間因這裡
無物遮擋，可遍觀滿天星鬥。進山的人們多在此祈求上蒼的保佑。
LONG );
        set("exits", ([
                "southeast" : __DIR__"caoguduo",
                "west"      : __DIR__"ermenkan",
        ]));
        set("no_clean_up", 0);
        set("outdoors", "guanwai");
        setup();
        replace_program(ROOM);
}