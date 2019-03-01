// Code of JHSH
#include <ansi.h>
inherit ITEM;


void create()
{
        set_name("噴火筒", ({ "huo qiang", "qiang", "gun" }) );
        set_weight(4000);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("long", "這是一把噴火筒，顏色黑中透紫，是用烏金煉出的
精鐵打造而成。後邊還連著一個鐵箱。\n"
);
                set("unit", "把");
                set("bullet", 5);
        }

}

void init()
{
        add_action("do_load","load");
        add_action("do_aim","aim");
        add_action("do_fire","shoot");
}

int do_load()
{
        object me=this_player();

        if (me->query_skill_mapped("throwing") != "wuxing-jueji")
                return notify_fail("你沒有激發五行絕技作為暗器，不會使用精妙的噴火筒！\n");

        if (me->query_skill("wuxing-jueji",1) < 120)
                return notify_fail("你五行絕技太差了點，不會使用精妙的噴火筒！\n");

        if( me->is_busy() )
                return notify_fail("你正忙著呢。\n");

        if (query_temp("loaded"))
                return notify_fail("石油已經裝好了。\n");

        if (query("bullet") <= 0)
                return notify_fail("石油已經用盡了。\n");

        message_vision("$N給噴火筒裡上了一些石油。\n",me);
        set_temp("loaded",1);
        me->start_busy(3+random(3));
        
        return 1;
}

int do_aim(string target)
{
        object ob;
        object me=this_player();

        if (me->query_skill_mapped("throwing") != "wuxing-jueji")
                return notify_fail("你沒有激發五行絕技作為暗器，不會使用精妙的噴火筒！\n");

        if (me->query_skill("wuxing-jueji",1) < 120)
                return notify_fail("你五行絕技太差了點，不會使用精妙的噴火筒！\n");

        if( me->is_busy() )
                return notify_fail("你正忙著呢。\n");

        if( !target)
                return notify_fail("你想射誰？\n");

        if(!objectp(ob = present(target, environment(me))))
                return notify_fail("這裡沒有這個人。\n");

        if( query("no_fight", environment(me)) )
                return notify_fail("這裡不能攻擊別人。\n");

        if( !ob->is_character() || ob->is_corpse() )
                return notify_fail("看清楚一點，那並不是活物。\n");

        if( !query_temp("loaded"))
                return notify_fail("你還沒裝石油呢。\n");

        message_vision(HIW"$N將噴火筒對準了$n。\n"NOR,me,ob);

        set_temp("aimed",target);
        me->start_busy(3+random(3));
        
        return 1;
}

int do_fire()
{
        string target;
        object ob;
        object me=this_player();

        if (me->query_skill_mapped("throwing") != "wuxing-jueji")
                return notify_fail("你沒有激發五行絕技作為暗器，不會使用精妙的噴火筒！\n");

        if (me->query_skill("wuxing-jueji",1) < 120)
                return notify_fail("你五行絕技太差了點，不會使用精妙的噴火筒！\n");

        if( me->is_busy() )
                return notify_fail("你正忙著呢。\n");

        if( query("no_fight", environment(me)) )
                return notify_fail("這裡不能攻擊別人。\n");

        if (!(target=query_temp("aimed")) )
                return notify_fail("你先瞄準了再開火。\n");

        if (!objectp(ob = present(target,environment(me))))
                return notify_fail("你的目標已經離開了。\n");

        if( !ob->is_character() || ob->is_corpse() )
                return notify_fail("你的目標已經死了。\n");

        message_vision(HIY"$N嘿嘿一聲姦笑，扣動機關，一條火燄向$n直噴過去。\n"NOR,me,ob);
        
        addn("bullet",-1);
        remove_call_out("shoot_target");
        call_out("shoot_target",1,me,target);
        me->start_busy(5);

        return 1;
}

int shoot_target(object me, string target)
{
        object ob;
        string *limbs;
        int damage;

        if (!objectp(ob = present(target,environment(me))))
                return notify_fail("一陣濃煙過去，好象什麼也沒打著。\n");

        if( !ob->is_character() || ob->is_corpse() )
                return notify_fail(target+"已經死了。\n");

        if( query("combat_exp", me)<random(query("combat_exp", ob)*2) )
        {
                message_vision(HIY"$N只覺一股熱浪撲面而來，忙使一招野驢打滾，狼狽萬分的躲了開去！\n"NOR,ob);
        }
        else
        {
                limbs=query("limbs", ob);
                message_vision(HIR"一股燒焦的氣味傳來，只見$N的"+
                                limbs[random(sizeof(limbs))]+"已被火燄噴中，"+
                                "頃刻間皮破肉爛，變成焦炭模樣。"+
                                "$N立時跌倒，狂叫悲呼。\n"NOR,ob);
                damage=query("max_qi", me)+query("max_qi", ob);
                damage=random(damage/2);
                ob->receive_wound("qi",random(damage/2),me);
                ob->receive_damage("qi",damage,me);
        }

        ob->kill_ob(me);
        me->start_busy(random(5));
        
        delete_temp("aimed");
        delete_temp("loaded");

        return 1;
}