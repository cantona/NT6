#include <weapon.h>
#include <ansi.h>

inherit THROWING;

void create()
{
        set_name(HIW "銀針" NOR, ({ "yin zhen" , "yin", "zhen" }) );
        set_weight(200);

        if( clonep() )
                set_default_object(__FILE__);
        else
        {
                set("unit", "枚");
                set("long", HIW "這是一枚三寸長的銀針，細而柔韌，多為醫家"
                            "刺穴療傷之用。能運用這種銀針的醫者多為曠世\n"
                            "神醫，並有深厚的內功。你可以試着用它來鍼灸"
                            "(zhenjiu)療傷。\n" NOR);
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
        object me, ob;
        int damage, heals, i;
        int exp, pot;
        int flag;
        string msg, s;

        me = this_player();
        if (me->query_skill("zhenjiu-shu", 1) < 1 )
                return notify_fail("你鍼灸術都沒學，去殺人啊？\n");

        if( this_object() != query_temp("handing", me) )
                return notify_fail("你必須把銀針拿在手裏才能鍼灸。\n");

        if (! arg || ! objectp(ob = present(arg, environment(me))))
                return notify_fail("你想對誰施行鍼灸術？\n");

        if( !ob->is_character() || query("not_living", ob) )
                return notify_fail("看清楚了，那不是活人！\n"); 

        if (! living(ob))
                return notify_fail("你還是等他醒了之後再治療吧。\n");

        if( query("no_zhenjiu", ob) )
                return notify_fail("人家不想接受你的好意。\n");

        flag = 0;

        if (! playerp(ob))
        {
                if (me->query_skill("zhenjiu-shu", 1) < 60)
                {
                        message_vision( HIY "$N" HIY "正想給$n" HIY "療傷，可$n"
                                        HIY "望着$N" HIY "那不停顫抖的雙手，臉上"
                                        "露出害怕的神色。\n" NOR + CYN "$n" CYN
                                        "皺了皺眉頭，對$N" CYN "説道：你那點手藝"
                                        "還是算了吧。\n", me, ob);
                        return 1;
                }
        } else
        {
                if (ob != me && playerp(ob))
                {
                        if( !is_sub(query("id", me),query("env/can_accept", ob)) )
                        {
                                // user refuse to accept
                                return notify_fail("人家現在不想接受你的好意。\n");
                        }
                        flag = 1;
                }
        }

        if (me->is_busy())
                return notify_fail("你現在正忙着呢。\n");

        if (me->is_fighting() || ob->is_fighting())
                return notify_fail("戰鬥中還想療傷，你找死啊？\n");

        if( ob->is_killing(query("id", me)) )
                return notify_fail("人家不會給你這個機會的。\n");

        if (ob->query_skill("force") >= 150)
                return notify_fail("人家內功深厚，不指望你替他療傷。\n");

        if( (query("max_qi", ob)*5/100>query("eff_qi", ob)) )
                return notify_fail("現在此人受傷過重，施行鍼灸太危險了！\n");   

        if( query("max_qi", ob) == query("eff_qi", ob) )
        {
                if(me != ob)
                        return notify_fail("這人並沒有受傷！\n");
                else
                        message_vision(HIW "$N" HIW "決定用自己來做試驗，來提高自己"
                                       "鍼灸術的水平。\n" NOR, me);
        }

        if( query("neili", me)<80 )
                return notify_fail("你的內力不足，無法使用鍼灸術為人療傷！\n");

        if( query("jing", me)<50 )
                return notify_fail("你的精不足，無法集中精力！\n");

        if( time()-query_temp("last/zhenjiu", ob)<60 )
                return flag = 1;

        set_temp("last/zhenjiu", time(), ob);

        addn("neili", -50, me);
        addn("jing", -30, me);
        me->start_busy(1 + random(1));
        me->improve_skill("zhenjiu-shu", 5 + random(30));
        tell_object(me, HIC "在實踐過程中你的「鍼灸術」提高了！\n" NOR);

        if (me == ob) s = "$N";
                 else s = "$n";

        msg = HIW "$N" HIW "手捏銀針，小心翼翼地向" + s + HIW "的穴道刺去，\n" NOR;

        if (random(120) > (int)me->query_skill("zhenjiu-shu", 1))
        {
                damage=1+random(query("max_qi", ob)/2);
                i=query("max_qi", ob)*10/damage;

                if (i > 100)
                        msg += CYN "可是$N" CYN "用力稍偏，沒刺中穴道，" + s +
                               CYN "臉上露出一絲難過的神情。" NOR;
                else
                {
                        if (i > 40)
                                msg += RED "但是$N" RED "用力過猛，竟然刺出了"
                                "血，這可是鍼灸中的大忌！" NOR;
                        else
                                msg += RED "$N" RED "刺了下去才發現刺錯了穴道，"
                                + s + RED "「哇」的噴出了一口鮮血！" NOR;
                }

                ob->receive_wound("qi", damage);                
                damage = i;
        } else
        {
                msg += HIW "$N" HIW "的銀針準確無誤的刺入穴道，隨着銀針的緩緩轉"
                       "動，" + s + HIW "長長的出了一口氣，臉色好看多了。\n" NOR;

                damage = -1;

                if( me != ob && query("combat_exp", me)<500000 && 
                    ! flag)
                {
                        exp = 100 + random(300);
                        pot = exp / 3;

                        GIFT_D->work_bonus(me, ([ "exp" : exp, "pot" : pot ]));
                }

                heals = me->query_skill("zhenjiu-shu", 1) + random(me->query_skill("zhenjiu-shu", 1));

                if( (query("eff_qi", ob)+heals)>query("max_qi", ob) )
                        set("eff_qi",query("max_qi",  ob), ob);
                else
                        addn("eff_qi", heals/3, ob);
        }

        msg += "\n";
        
        if (me == ob)
                message_vision(msg, me);
        else
                message_vision(msg, me, ob);

        if (damage > 0)
        {
                if( query("qi", ob)<0 )
                {
                        set("eff_qi", 1, ob);
                        set("qi", 1, ob);

                        if (playerp(ob))
                        {
                                if (me == ob)
                                        message_vision(HIR "好險啊！$N" HIR "差一點把自己扎"
                                                       "死。\n" NOR, me);
                                else
                                        message_vision(HIR "好險啊！$N" HIR "差一點把$n" HIR
                                                       "扎死。\n", me,ob);
                        }
                } else
                {
                        if (me != ob)
                        {
                                if (random(damage) < 40)
                                {
                                        message_vision(HIR "$N" HIR "痛得「哇哇」大叫不止，"
                                                       "怒道：居然敢下毒手，你想殺死我啊！\n" NOR, ob);

                                        ob->kill_ob(me);
                                        me->fight_ob(ob);
                                } else
                                {
                                        message_vision(HIR "$N" HIR "「哇」的大叫一聲，不"
                                                       "滿地道：好痛啊！下次你可千萬當心點"
                                                       "！\n",ob);
                                }
                        }
                }
        }

        return 1;
}
