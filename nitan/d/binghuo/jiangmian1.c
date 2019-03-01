// Room: /binghuo/jiangmian1.c
// Date: Oct.28 1999 by Winder

inherit ROOM;

void create()
{
        set("short", "錢塘江面");
        set("long", @LONG
只聽得雷聲隱隱，錢塘江上夜潮已至。潮聲如雷，震耳欲聾，江
船猛地被拋了起來。說話聲盡皆掩沒。向窗外看時，只見巨浪猶如一
堵透明的高牆，兩岸風物被掩沒在驚濤之中了。
LONG );
        set("no_sleep_room",1);
        set("outdoors", "wangpan");
        set("no_clean_up", 0);
        setup();
        replace_program(ROOM);
}
