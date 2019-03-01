#include <ansi.h>
inherit ITEM;

void create()
{
        set_name(NOR + CYN "鐵八卦" NOR, ({ "tie bagua", "tie", "bagua" }));
        set_weight(2000);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", NOR + CYN "這是一個生鐵所鑄的八卦盤，盤上雕"
                            "滿了太極八卦\n紋樣，制作得非常精致。風水師"
                            "常常借此來觀測風\n水和卜卦，也可以用來破除"
                            "(" HIW "break" NOR + CYN ")各種奇門陣法。\n"
                            NOR);
                set("unit", "只");
                set("value", 300000);
                set("no_sell", 1);
                set("material", "steel");
        }
        setup();
}

void init()
{
        add_action("do_break", "break");
        add_action("do_break", "pozhen");
}

int do_break(string arg)
{
        object me, env, owner;
        int skill;

        me = this_player();
        env = environment(me);
        skill = (int)me->query_skill("qimen-wuxing", 1);

        if (me->is_busy()
            || query_temp("pending/exercising", me )
            || query_temp("exit_blocked", me) )
                return notify_fail("你現在正忙著呢。\n");

        if (skill < 1)
                return notify_fail("你把鐵八卦翻來覆去擺弄了半天，卻"
                                   "不知如何下手。\n");

        if (skill < 80)
                return notify_fail("你對奇門五行的研究不夠，尚且無法"
                                   "破陣。\n");

        if( !env || !query("th_buzhen", env) )
                return notify_fail("這裡並沒有被布下奇門陣法。\n");

        if( !objectp(owner=find_player(query("th_zhen_owner", env)) )
           || environment(owner) != env)
        {
                set("long",query("org_desc",  env), env);
                set("exits",query("org_exits",  env), env);
                set("cost",query("org_cost",  env), env);
                delete("org_desc", env);
                delete("org_cost", env);
                delete("org_exits", env);
                delete("th_buzhen", env);
                delete("th_pozhen", env);
                delete("th_zhen_owner", env);

                tell_object(env, HIM "\n突然間紫霧朝周圍散去，四面景致"
                                 "猛然一變。\n\n" NOR);
                return 1;
        }

        if( me != owner && query("max_jingli", me)<500 )
                return notify_fail("你的精力修為不足，難以破陣。\n");

        if( me != owner && query("jingli", me)<300 )
                return notify_fail("你目前的精力不足，難以破陣。\n");

        if( me != owner && query("jing", me)<200 )
                return notify_fail("你目前的精氣不足，難以破陣。\n");

        if( me != owner && skill<query("th_pozhen", env)*3/4 )
        {
                message_vision(HIR "$N" HIR "坐在地上冥思苦想，突然臉色大"
                               "變，嘔出一口鮮血。\n" NOR, me);
                me->receive_wound("jing", 100);
                me->start_busy(3);
                return 1;
        }

        if (me == owner && environment(owner) == env)
        {
                message_vision(HIW "只見$N" HIW "袍袖一拂，紫霧頓時朝四面"
                               "散去，周圍景致又恢復如初。\n" NOR, me);
                me->start_busy(2);
        } else
        {
                message_sort(HIW "\n$N" HIW "凝思片刻，須臾已將陣法的種種"
                             "生克變化全盤了然于胸，不禁仰天一聲長笑，袍袖"
                             "一拂，掠入陣中。只見$N" HIW "掌劈腳挑，直激"
                             "得沙石四起，不一刻陣中之陰霾戾氣四處飛散，消"
                             "逝得無影無蹤。\n\n" NOR, me);
                me->receive_damage("jing", 100);
                addn("jingli", -150, me);
                me->start_busy(3);
        }        
        set("long",query("org_desc",  env), env);
        set("exits",query("org_exits",  env), env);
        set("cost",query("org_cost",  env), env);
        delete("org_desc", env);
        delete("org_cost", env);
        delete("org_exits", env);
        delete("th_buzhen", env);
        delete("th_pozhen", env);
        delete("th_zhen_owner", env);

        return 1;
}