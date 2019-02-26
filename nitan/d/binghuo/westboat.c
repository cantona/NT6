// Room: /binghuo/westboat.c
// Date: Oct.28 1999 by Winder

inherit ROOM;

void create()
{
        set("short", "錢塘江面");
        set("long", @LONG
只聽得雷聲隱隱，錢塘江上夜潮已至。潮聲如雷，震耳欲聾，大
船猛地被拋了起來。説話聲盡皆掩沒。大船順風順水，向杭州疾馳。
LONG );
        set("no_sleep_room",1);
        set("outdoors", "wangpan");
        set("no_clean_up", 0);
        setup();
        replace_program(ROOM);
}
