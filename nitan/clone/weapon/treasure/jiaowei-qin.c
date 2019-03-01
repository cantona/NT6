//jiaowei qin 焦尾琴

#include <weapon.h>
#include <ansi.h>

inherit F_UNIQUE;
inherit SWORD;

void create()
{
        set_name(HIM"焦尾琴"NOR,({"jiaowei qin","qin"}));
        set_weight(500);
        if(clonep())
                 set_default_object(__FILE__);
        else{
                set("unit","張");
                set("value",40000);
                set("material","steel");
                set("long","相傳這便是當年蔡文姬從火中所救出的焦木做成的美琴，琴的尾端仍可見焦黑色。\n");
                set("wield_msg",HIY"$N伸手輕輕一揮,一張焦尾琴便已出現在$N手中.\n"NOR);
                set("unwield_msg",HIY"$N十指一拂，琴聲曳然而止。$N收起焦尾琴，放進背著的包袱裡。\n"NOR);
//                set("unequip_msg",HIY"你十指一拂，琴聲曳然而止。你收起焦尾琴，放進背著的包袱裡。.\n"NOR);
        }
        init_sword(150);
        setup();
}

//int wield()
//{
//        object ob = environment();

/*        if (ob && !wizardp(ob)) {
                tell_object(ob, name() + "是巫師用品，你不能使用，請馬上向巫師報告，否則後果自負。\n");
                call_out("let_him_die", 300, ob);
                return 0;
        }*/
//        return ::wield();
//}
/*
void let_him_die(object ob)
{
        if (ob = environment()) {
                addn("combat_exp", -30000, ob);
                set_temp("last_damage_from", "盜用巫師用品中毒", ob);
                ob->die();
        }
}
*/
mixed weapon_hit_ob(object me, object victim, int damage_bonus)
{
        int n;

        if (me->query_skill_mapped("sword") != "liangyi-sword" ||
            me->query_skill("liangyi-sword", 1) < 100)
//                return damage_bonus / 2;
                return 0;

        switch (random(4))
        {
        case 0:
                if (! victim->is_busy())
                {
                        victim->start_busy(me->query_skill("sword") / 100 + 1);
                  return WHT "$N" WHT "一聲斷喝，單手猛然拂過手中焦尾琴，焦尾琴頓時發出一股尖銳的"
                       "琴音，$n" WHT "只覺頭暈目眩，幾欲昏厥！\n" NOR;
                }
        case 1:
                n = me->query_skill("sword");
                victim->receive_damage("qi", n * 3 / 4, me);
                victim->receive_wound("qi", n * 3 / 4, me);
                return WHT "$N" WHT "一聲冷哼，手中焦尾琴一振，霎時龍吟驟起，一道劍氣攜著尖"
                       "銳的琴音直射$n" WHT "而去！\n" NOR;
        }
        return damage_bonus;
}