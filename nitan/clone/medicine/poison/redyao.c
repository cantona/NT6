// redyao.c

// inherit F_CLEAN_UP;
inherit COMBINED_ITEM;
#include <ansi.h>

void create()
{
        set_name(HIR"紅色藥粉"NOR, ({ "red yao","yao"}) );
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("long", "這是一包五毒教精煉的毒藥。\n你可以用(rpour)命令試試。\n" );
                set("unit", "些");
                set("base_value", 200);
                set("base_unit", "包");
                set("base_weight", 30);
                set("pour_type", "snake_poison");
                set("value", 200);
        }
        set_amount(1);
}

void init()
{
        add_action("do_rpour", "rpour");
        add_action("do_tu", "tu");
}

int do_rpour(string arg)
{
        string what;
        object ob,me,who,victim;
//        object *inv;
        function f;
        me = this_player();
        if( !arg ||        sscanf(arg, "%s in %s", who, what)!=2 || victim == me)
                return notify_fail("命令格式: rpour <人物> in <物品>。\n");
        victim = present(who, environment(me));
        if( !victim || victim==me) return notify_fail("沒有你想下毒的人哦。\n");
        if( query("family/family_name", me) != "五毒教" )
                return notify_fail("下毒！！你怎麼能幹這麼卑鄙的事哦？\n");
        if ((int)me->query_skill("five-poison",1) < 50)
                return notify_fail("才這麼點本事就想害人？別弱了我五毒教的威名啊！\n");
        ob = present(what, victim);
        if( !ob )                                // 41
                return notify_fail("對方身上沒有" + what + "這樣東西。\n");
//        if( me->query_temp("being_toudu") )
//                return notify_fail("你已經在找機會下手了！\n");
        if( query("max_liquid", ob) )
        {
                int myskill=(me->query_skill("five_poison",1))*10+query("neili", me);
                int skill=query("neili", victim);
                if( query("liquid/remaining", ob)<1 )
                        return notify_fail("那個容器是空的，不能用來溶解毒粉！\n");
                if (random(myskill)<random(skill))
                {
                        tell_object(me, HIR "糟糕！你失手了！\n\n" NOR);
                        message_vision("$N一回頭，正好發現$n正想向$P身上的" + ob->name() + "下毒！\n\n" + "$N喝道：「幹什麼！」\n\n", victim, me);
                        if( userp(victim) )
                        {
                                victim->fight_ob(me);
                                me->fight_ob(victim);
                        }
                        else
                        {
                                victim->kill_ob(me);
                                me->kill_ob(victim);
                        }
                        me->start_busy(3);
                        return 1;
                }
                f = (: call_other, __FILE__, "drink_drug" :);
                set("liquid/drink_func", bind(f,ob), ob);
                addn("liquid/slumber_effect", 100, ob);
                message("vision","你與" + victim->name() + "擦身而過，偷偷將《" + name() + "》灑進他的" + ob->name()+ "裏面。\n", this_player());
                add_amount(-1);
                me->start_busy(2);
                if( random(myskill) < skill/2 )
                        message("vision","你看到"+me->name()+"鬼鬼祟祟地在"+victim->name()+"身上的一"+query("unit", ob)+ob->name()+"裏灑入了一些"+name()+"！\n",environment(me),({me,victim}));
                return 1;
        }
        else return notify_fail("毒只能下在飲水裏面！\n");
        return 1;
}

int drink_drug(object ob)
{
        this_player()->apply_condition("snake_poison",this_player()->query_condition("snake_poison")+query("liquid/slumber_effect", ob));
        return 0;
}

#include "poison2.h";
