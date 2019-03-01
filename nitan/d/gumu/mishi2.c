// mishi2.c 密室
// Java Oct.10 1998

#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", "密室");
        set("long", @LONG
這裡是古墓中的密室，四周密不透風，你只能借著牆上昏暗的燈光
來勉強分辨方向。牆是用整塊的青石砌合起來的，接合的甚是完美，你
難以從中找出一絲縫隙。牆上(wall)好象雕有一些文字。
LONG        );
        set("exits", ([
                "east"  : __DIR__"mishi3",
                "west"  : __FILE__,
                "north" : __FILE__,
                "south" : __DIR__"mishi1",
                "up" : __DIR__"houting",
        ]));
        set("no_clean_up", 0);
        set("coor/x", -3200);
        set("coor/y", 30);
        set("coor/z", 100);
        setup();
}


void init()
{
        add_action("do_think", "think");
}

int do_think(string arg)
{
        object here, me = this_player();
        int add;

        if (! here = find_object(__DIR__"mishi2"))
                here = load_object(__DIR__"mishi2");

        if( query("special_skill/clever", me) )
                add = me->query_int() * 4;
        else
                add = me->query_int() * 3;

        if (! living(me) || arg != "wall")
                return notify_fail("你要參悟什麼？\n");

        if (me->is_busy() || me->is_fighting())
                return notify_fail("你現在正忙著呢。\n");

        if ((int)me->query_skill("sword", 1) < 30)
                return notify_fail("你的內功修為不夠，無法領悟牆"
                                   "上的心法。\n");

        if( !query("can_learn/yunv-xinfa/wall", me) )
                return notify_fail("你研究了半天，卻發現牆壁上的心法"
                                   "甚難領悟。\n");

        if ((int)me->query_skill("yunv-xinfa", 1) < 180)
                return notify_fail("你發現牆上所記載的心法過于深奧，自"
                                   "己一時難以領悟。\n");

        if ((int)me->query_skill("yunv-xinfa", 1) > 240)
                return notify_fail("你發現牆上所記載的心法過于膚淺，自"
                                   "己無法領會到任何東西。\n");

        if( query("jing", me)<35 )
                return notify_fail("你現在精神不濟，過于疲倦，還是休息"
                                   "一會吧。\n");

        me->receive_damage("jing", 30);

        if (me->can_improve_skill("yunv-xinfa"))
                me->improve_skill("yunv-xinfa", add);

        me->start_busy(random(2));
        message_vision(HIY "\n$N" HIY "聚精會神的參詳牆上所記載的心法，"
                       "似有所悟。\n" NOR, me);
        write(HIC "你對「玉女心法」有了新的領悟。\n" NOR);
        return 1;
}

