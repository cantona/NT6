
// yiyang.c 一陽指力注入武器

#include <ansi.h>

inherit F_SSERVER;

string name() { return "一陽劍氣"; }

private int remove_effect(object me, object weapon);

int perform(object me, object target)
{
        object weapon;
        int skill, skill1, damage;

        if (me->query_skill_mapped("force") != "kurong-changong" &&
            me->query_skill_mapped("force") != "duanshi-xinfa")
                return notify_fail("你所用得內功心法不對，無法運用一陽指。\n");

        if( query_temp("yiyang", me) )
                return notify_fail("你已運一陽指指力於武器上了！\n");

        if (me->query_skill("force",1)<100
                || (me->query_skill("kurong-changong",1)<100 &&
                    me->query_skill("duanshi-xinfa",1)<100)
                || me->query_skill("duanjia-jian",1)<100
                || me->query_skill("sun-finger",1)<120)
                return notify_fail("你的功力不夠，無法運用一陽指指力於武器上！\n");

        if( !objectp(weapon=query_temp("weapon", me)) || query("skill_type", weapon) != "sword" )
                return notify_fail("你沒有使用正確的武器，無法運一陽指力於其上。\n");

        if( query_temp("yiyang", weapon) )
                return notify_fail("該武器已經注滿了一陽指指力！\n");

        if( query("neili", me) <= 300 )
                return notify_fail("你的內力不夠運一陽指力！\n");

        if( query("jingli", me) <= 100 )
                return notify_fail("你的精力不夠運一陽指力！\n");

        if( query("weapon_prop/damage", weapon) >= 5000 )
                return notify_fail("你發現這件武器打造的精緻無比，巧奪天功，無法灌注內力於其上！\n");

        message("vision",HIY"\n"+query("name", me)+"緊握"+query("name", weapon)+"凝神運氣片刻。\n\n"NOR,environment(me),me);
        tell_object(me,HIY"\n你凝神運氣，把一陽指指力灌注到"+query("name", weapon)+"上。\n\n"NOR);

        skill = me->query_skill("force");

        set_temp("yiyang", 25+skill/10, me);

        skill = me->query_skill("sun-finger",1) + me->query_skill("kurong-changong",1);
        skill /= 3;
        set_temp("rig",query("weapon_prop/damage",  weapon), weapon);
        set_temp("yiyang", 1, weapon);

        if( query("weapon_prop/damage", weapon)<1000 )
                damage = 3000 + skill;
        else if( query("weapon_prop/damage", weapon)<3000 )
                damage = 2000 + skill;
        else if( query("weapon_prop/damage", weapon)<5000 )
                damage = 1000 + skill;

        addn("weapon_prop/damage", damage, weapon);
        addn_temp("apply/damage", damage, me);
        call_out("checking", 1, me, weapon);
        addn("neili", -200, me);
        addn("jingli", -50, me);

        return 1;
}

void checking(object me, object weapon)
{
        if (!me) {
                if (!weapon) return;
                set("weapon_prop/damage",query_temp("rig",  weapon), weapon);
                delete_temp("yiyang", weapon);
                delete_temp("rig", weapon);
                return;
        }
        if( query_temp("yiyang", me)){
           if (!weapon)
           {
                       remove_effect(me, weapon);
                tell_object(me, HIY "\n你把一陽指指力收了回來。\n\n" NOR);
                return;
           }
           else if( environment(weapon) != me || weapon != query_temp("weapon", me)){
                       remove_effect(me, weapon);
                tell_object(me, HIY "\n你把一陽指指力從"+weapon->name()+"上收了回來。\n\n" NOR);
                return;
           }
           else if( query("weapon_prop", weapon) == 0){
                remove_effect(me, weapon);
                tell_object(me, HIY "\n你的"+weapon->name()+"已毀，不得不收回灌注於其上的一陽指指力。\n\n" NOR);
                return;
           }
           else if (me->query_skill_mapped("force") != "kurong-changong" &&
                    me->query_skill_mapped("force") != "duanshi-xinfa") {
                remove_effect(me, weapon);
                tell_object(me, HIY "\n你感到內息不暢，無法保持灌注在"+weapon->name()+"上的一陽指指力。\n\n" NOR);
                return;
           }

           addn_temp("yiyang", -1, me);
           call_out("checking", 1, me, weapon);
        }
        else {
           remove_effect(me, weapon);
        tell_object(me, HIY "\n你感到內息混濁，不得不換氣運功，從"+weapon->name()+"上收回灌注的一陽指指力。\n\n" NOR);
        }
}

private int remove_effect(object me, object weapon)
{
        if (weapon)
        {
                if( query_temp("weapon", me) &&
                    query_temp("weapon", me) == weapon )
                    addn_temp("apply/damage", -query("weapon_prop/damage", weapon)+query_temp("rig", weapon), me);
                set("weapon_prop/damage",query_temp("rig",  weapon), weapon);
                delete_temp("yiyang", weapon);
                delete_temp("rig", weapon);
        }
        delete_temp("yiyang", me);
        return 1;
}