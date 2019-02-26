// Room: /d/shaolin/hantan2.c
// Date: YZC 96/02/06

#include <room.h>
inherit ROOM;

void create()
{
        set("short", "萬古寒潭");
        set("long", @LONG
這是寒潭之中。從這裏已可感覺到深水下的巨大壓力，徹骨冰涼
的潭水在身體四周凝成一層薄弧的冰殼，四肢也已開始麻木，令你感
到舉手投足都甚為困難。水中的吸力也漸漸加強，你不由自主地往下
沉去。
LONG );
        set("no_clean_up", 0);
        setup();
}

void init()
{
        call_out("down", 5, this_player());
}

void down(object me)
{
        tell_object(me, "只覺腳底水流盤旋，一股強大的吸力把你往下拉去...\n");
        me->move(__DIR__"hantan3");
}
