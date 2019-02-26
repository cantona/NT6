// Room: /d/shaolin/hantan1.c
// Date: YZC 96/02/06

#include <room.h>
inherit ROOM;

void create()
{
        set("short", "萬古寒潭");
        set("long", @LONG
這是寒潭之中。四周水聲嘩嘩，似乎有一股暗流在極力牽扯着你
往下沉。透過潭水隱約可見潭周的巖壁，被數萬年水流衝激磨削得十
分光滑。雖然口中含了闢水珠，身上卻仍然感覺到絲絲寒意侵入肌膚，
而且越是往下，水底的吸力越強，寒意更甚。
LONG );
        set("no_clean_up", 0);
        setup();
}

void init()
{
        call_out("down", 10, this_player());
}

void down(object me)
{
        tell_object(me, "只覺腳底水流盤旋，一股強大的吸力把你往下拉去...\n");
        me->move(__DIR__"hantan2");
}
