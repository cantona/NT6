// guanyuntai.c 觀雲台
// Modified by haiyan

#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", "觀雲台");
        set("long", @LONG
這裡是武當山天柱峰的觀雲台。放眼望去，只見雲海湧動，氣勢
磅礡。你心中微微一動，凝神靜思，感覺在這裡進行參悟(canwu)，靜
觀雲的變化，于太極拳理似乎極有幫助。
LONG );
        set("no_fight", "1");
        set("no_steal", "1");
        set("no_sleep_room","1");
        set("exits", ([
                "westdown" : __DIR__"jinding",
        ]));
        set("coor/x", -340);
        set("coor/y", -420);
        set("coor/z", 190);
        setup();
}

void init()
{
        add_action("do_canwu", "canwu");
}

int do_canwu(string arg)
{
        object me;
        int cost, quanli, lvl;

        me = this_player();
        quanli=query("taiji_quanli", me);
        lvl = me->query_skill("taiji-quan", 1);
        if (me->is_busy())
                return notify_fail("你現在還忙著，靜不下心來參悟太極拳理。\n");

        if( query("jing", me)<query("max_jing", me)*7/10 )
                return notify_fail("你現在的精氣不夠，無法進行參悟。\n");

        if (lvl < 200)
                return notify_fail("你的太極功夫還不到家，不必在這裡浪費時間了。\n");

        if (! arg || ! sscanf(arg, "%d", cost))
                return notify_fail("你要花多少潛能來參悟太極拳理？\n");

        if( cost >= query("potential", me)-query("learned_points", me) )
                return notify_fail("你現在沒有這麼多的潛能！\n");

        if (lvl >= 200 && lvl < 300 && quanli == 1)
                return notify_fail("你上次參悟出的太極拳理還未理解透徹，不要急于求成。\n");

        if (lvl >= 300 && lvl < 400 && quanli == 2)
                return notify_fail("你上次參悟出的太極拳理還未理解透徹，不要急于求成。\n");

        if (lvl >= 400 && lvl < 500 && quanli == 3)
                return notify_fail("你上次參悟出的太極拳理還未理解透徹，不要急于求成。\n");

        if (lvl >= 500 && quanli >= 4)
                return notify_fail("你已經徹底領悟了太極拳理，不必再參悟了。\n");

        if (cost < 100)
                return notify_fail("參悟太極拳理至少需要一百點潛能才能有所進步。\n");

        message_vision("$N盤膝而坐，靜靜地凝視著千變萬化的流雲，開始潛心鑽研"
                       "太極拳理。\n", me);

        set_temp("potential_cost", cost, me);
        me->set_short_desc("正坐在地下凝神靜思。");
        me->start_busy((:call_other, __FILE__, "canwu" :),
                       (:call_other, __FILE__, "halt_canwu" :));
        return 1;
}

int canwu(object me)
{
        int cost, hint;

        cost=query_temp("potential_cost", me);
        if (cost > 0)
             cost = random(2) + 1;
        else
             cost = 0;

        addn("learned_points", cost, me);
        switch (random(30))
        {
            case 0:
                    write("你怔怔地望著不斷滾動的流雲，似乎想到了些什麼。\n");
                    break;

            case 1:
                    write("你默默思索，對太極以柔克剛的道理似乎又想通了點什麼。\n");
                    break;

            case 2:
                    write("你看到腳下不住翻滾的白雲，似乎想到了些“綿勁”的道理。\n");
                    break;

            case 3:
                    write("你雙手圈動，似乎又想通了太極拳理的一些奧秘。\n");
                    break;
        }

        if( me->addn_temp("potential_cost",-cost) <= 0 )
        {
            message_vision(HIM "$N參悟完畢，覺得對更深一層的太極拳理好像似懂非懂。\n"NOR, me);
            me->set_short_desc(0);
            return 0;
        }

        if( !query("taiji_quanli", me) || query("taiji_quanli", me)<2 )
               hint = 10000;
        else if( query("taiji_quanli", me)<3)hint=20000;
              else  hint = 30000;

        if ((random(hint)) < me->query_int())
        {
             addn("taiji_quanli", 1, me);
             if( query("taiji_quanli", me)<4 )
                 message_vision(HIY "$N" HIY "參悟完畢，似乎從流雲的變化中悟出了更"
                                "深的太極拳理，不禁面露微笑。\n" NOR, me);
             else
             {
                 message_vision(HIY "$N" HIY "參悟完畢，心中登時豁然，對太極拳理的諸般變化"
                                "已了然于胸，禁不住縱聲長笑……\n\n" NOR, me);
                 write(HIC "你已經徹底參悟出了太極拳理！\n\n" NOR);
             }
             if (me->can_improve_skill("taiji-quan"))
                  me->improve_skill("taiji-quan", 200000);
             me->set_short_desc(0);
             return 0;
        }
        return 1;
}

int halt_canwu(object me)
{
        tell_object(me, "你中止了參悟。\n");
        message_vision("$N長嘆一聲，緩緩站了起來。\n", me);
        addn("potential", (query("learned_points", me)-query("potential", me))/5, me);
        delete_temp("potential_cost", me);
        me->set_short_desc(0);
        return 1;
}
