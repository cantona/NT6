// /clone/misc/yinzhen.c
// Last modified by winder 2003.9.2

#include <weapon.h>
#include <ansi.h>

inherit THROWING;

void create()
{
        set_name(HIW "銀針" NOR, ({ "yin zhen" , "yin", "zhen" }) );
        set_weight(200);

        if( clonep() ) set_default_object(__FILE__);
        else
        {
                set("unit", "把");
                set("long", HIW"這是三寸長的銀針，細而柔韌，多為醫家刺穴療傷之用。\n能運用這種銀針的醫者多為曠世神醫，並有深厚的內功。\n你可以試着用它來鍼灸(zhenjiu)療傷。\n" NOR);
                set("value", 0);
                set("yingdu", 50);
                set("base_unit", "枚");
                set("base_weight", 10);
                set("base_value", 0);
                set("material","crimsonsteel");
        }
        set_amount(1);
        init_throwing(30);
        setup();
}

void init()
{
        add_action("do_heal", "zhenjiu");
}

int do_heal(string arg)
{
        object ob, me = this_player();
        int damage, heals, i, exp, pot;
        string msg, s;

        if (me->query_skill("acupuncture", 1) < 1 )
                return notify_fail("你鍼灸術都沒學，去殺人啊？\n");
        if( query("equipped", this_object()) != "wielded" )
                return notify_fail("你必須把銀針拿在手裏才能鍼灸。\n");
        if (! arg || ! objectp(ob = present(arg, environment(me))))
                return notify_fail("你想對誰施行鍼灸術？\n");
        if (! ob->is_character() )
                return notify_fail("看清楚了，那不是活人！\n"); 
        if( query_temp("noliving", ob) || !living(ob) )
                return notify_fail("你還是等他醒了之後再治療吧。\n");
        if (me->is_busy()) return notify_fail("你現在正忙着呢。\n");
        if (me->is_fighting() || ob->is_fighting())
                return notify_fail("戰鬥中還想療傷，你找死啊？\n");
        if( ob->is_killing(query("id", me)) )
                return notify_fail("人家不會給你這個機會的。\n");
        if( query("race", ob) != "人類" )
          return notify_fail("你要當獸醫？\n");
        if (ob != me && userp(ob))
        {
                        tell_object(me, YEL "你不能為玩家鍼灸。\n" NOR);
                        return 1;
        }
        if( !userp(ob) && random(me->query_skill("acupuncture",1)+query("cor", me))<1 )
        {
                        message_vision( HIY "$N" HIY "正想給$n" HIY "療傷，可$n" HIY "望着$N" HIY "那不停顫抖的雙手，臉上露出害怕的神色。\n" NOR + CYN "$n" CYN "皺了皺眉頭，對$N" CYN "説道：你那點手藝還是算了吧。\n"NOR, me, ob);
                        return 1;
        }
        if (me!=ob && ob->query_skill("force") >= 150)
                return notify_fail("人家內功深厚，不指望你替他療傷。\n");
        if( (query("max_qi", ob)*5/100>query("eff_qi", ob)) )
                return notify_fail("現在此人受傷過重，施行鍼灸太危險了！\n");
        if( query("neili", me)<80 )
                return notify_fail("你的內力不足，無法使用鍼灸術為人療傷！\n");
        if( query("jing", me)<50 )
                return notify_fail("你的精不足，無法集中精力！\n");
        if( time()-query_temp("last/zhenjiu", ob)<60 )
                return notify_fail("人家剛剛接收過鍼灸治療，現在不需要你幫忙。\n");
        if( query("max_qi", ob) == query("eff_qi", ob) )
        {
                if(me != ob) return notify_fail("這人並沒有受傷！\n");
                else
                        message_vision(HIW"$N"HIW"決定用自己來做試驗，來提高自己鍼灸術的水平。\n" NOR, me);
        }
        set_temp("last/zhenjiu", time(), ob);
        addn("neili", -50, me);
        addn("jing", -30, me);
        me->start_busy(1 + random(1));
        me->improve_skill("acupuncture", 5 + random(me->query_skill("acupuncture",1)));
        tell_object(me, HIC "在實踐過程中你的「鍼灸術」提高了！\n" NOR);
        if (me == ob) s = "$N";
                 else s = "$n";
        msg = HIW"$N"HIW"手捏銀針，小心翼翼地向"+s+HIW"的穴道刺去，\n"NOR;
        if (random(120) > (int)me->query_skill("acupuncture", 1))
        {
                damage=1+random(query("max_qi", ob)/2);
                i=query("max_qi", ob)*10/damage;

                if (i > 100)
                        msg += CYN"可是$N"CYN"用力稍偏，沒刺中穴道，"+s+CYN"臉上露出一絲難過的神情。"NOR;
                else
                {
                        if (i > 40)
                                msg += RED"但是$N"RED"用力過猛，竟然刺出了血，這可是鍼灸中的大忌！"NOR;
                        else
                                msg += RED"$N"RED"刺了下去才發現刺錯了穴道，"+s+RED"「哇」的噴出了一口鮮血！"NOR;
                }

                ob->receive_wound("qi", damage);
                damage = i;
        }
        else
        {
                msg += HIW"$N"HIW"的銀針準確無誤地刺入穴道，隨着銀針的緩緩轉動，"+s+HIW"長長地出了一口氣，臉色好看多了。"NOR;
                damage = -1;
                if( me != ob/* && query("combat_exp", me)<200000*/ )
                {
                        exp = 20 + random(20);
                        pot = 5 + random(5);

                        addn("combat_exp", exp, me);
                        addn("potential", pot, me);

                        tell_object(me,HIC"你獲得了"+chinese_number(exp)+"點經驗和"+chinese_number(pot)+"點潛能。\n"NOR);
                }

                heals = me->query_skill("acupuncture", 1)+random(me->query_skill("acupuncture", 1));

                if( (query("eff_qi", ob)+heals/3)>query("max_qi", ob) )
                        set("eff_qi",query("max_qi",  ob), ob);
                else addn("eff_qi", heals / 3, ob);
        }

        msg += "\n";
        if (me == ob) message_vision(msg, me);
        else message_vision(msg, me, ob);

        if (damage > 0)
        {
                if( query("qi", ob)<0 )
                {
                        set("eff_qi", 1, ob);
                        set("qi", 1, ob);

                        if (userp(ob))
                        {
                                if (me == ob)
                                        message_vision(HIR"好險啊！$N"HIR"差一點把自己扎死。\n"NOR, me);
                                else
                                        message_vision(HIR"好險啊！$N"HIR"差一點把$n"HIR"扎死。\n"NOR, me, ob);
                        }
                }
                else
                {
                        if (me != ob)
                        {
                                if (random(damage) < 40)
                                {
                                        message_vision(HIR"$N"HIR"痛得「哇哇」大叫不止，怒道：居然敢下毒手，你想殺死我啊！\n" NOR, ob);
                                        ob->kill_ob(me);
                                        me->fight_ob(ob);
                                }
                                else
                                {
                                        message_vision(HIR"$N"HIR"「哇」的大叫一聲，不滿地道：好痛啊！下次你可千萬當心點！\n"NOR,ob);
                                }
                        }
                }
                
        }

        return 1;
}
