
// jianzhi.c 劍指相配攻擊
// 神鵰俠侶(20)：玉簫劍法與彈指功夫均以攻敵穴道為主，劍指相配，精微奧妙

#include <ansi.h>

inherit F_SSERVER;

string name() { return "劍指相配"; }

void remove_effect(object me, object weapon, int speed, int damage);

int perform(object me, object target)
{
        object weapon;
        int speed, damage, sword;

        weapon=query_temp("weapon", me);

        if( !target && me->is_fighting() ) target = offensive_target(me);

        if( !target
        ||  !target->is_character()
        ||  !me->is_fighting(target) )
                return notify_fail("劍指相配攻擊只能對戰鬥中的對手使用。\n");

        if( !objectp(weapon) || query("skill_type", weapon) != "sword" )
                return notify_fail("你手中無劍，如何談得上「劍指相配」？\n");

        if( query_temp("secondary_weapon", me) )
                return notify_fail("你正握着短兵，沒有手能空出來「劍指相配」了。\n");

        if( query_temp("th_jianmang", me) )
                return notify_fail("你正凝神使動「劍芒」，不能再分心了！\n");

        if( query_temp("th_jianzhi", me) )
                return notify_fail("你正在運用劍指相配的攻勢！\n");

        if( me->query_skill("yuxiao-jianfa",1) < 120 )
                return notify_fail("你的玉簫劍法修為未到，不能劍指相配攻敵！\n");

        if( me->query_skill("tanzhi-shentong",1) < 120 )
                return notify_fail("你的彈指神通修為未到，不能劍指相配攻敵！\n");

        if( me->query_skill("bibo-shengong", 1) < 120 )
                return notify_fail("你的碧濤玄功修為不足，強使劍指相配，徒然分散功力！\n");

        if( me->query_skill_mapped("sword") != "yuxiao-jianfa")
                return notify_fail("你並沒有使用玉簫劍法！\n");

        if( me->query_skill_mapped("force") != "bibo-shengong")
                return notify_fail("你所運使的內功無法與劍指相配之心法協調！\n");

        if( me->query_skill_mapped("finger") != "tanzhi-shentong")
                return notify_fail("你所施展的指法並非彈指神通！\n");

        if( me->query_skill_prepared("finger") != "tanzhi-shentong")
                return notify_fail("你還沒有準備好施展彈指神通！\n");

        if( query("max_neili", me) <= 1200 )
                return notify_fail("你的內力修為不足，倘若施展劍指相配，反而會有力分則弱的兇險！\n");

        if( query("neili", me) <= 400 )
                return notify_fail("你的內力不足，不足以施展劍指相配！\n");

        if( query("jingli", me) <= 400 )
                return notify_fail("你的精力不足，不足以施展劍指相配！\n");

        damage = me->query_skill("yuxiao-jianfa",1) + me->query_skill("tanzhi-shentong",1);
        sword = (me->query_skill("sword") + me->query_skill("finger") );
        addn("neili", -250, me);
        addn("jingli", -100, me);

        //命中率增加
        addn_temp("apply/defense", damage, me);
        addn_temp("apply/attack", damage, me);

        COMBAT_D->do_attack(me,target,query_temp("weapon", me));

        message_combatd(HIG"$N手中"+weapon->name()+HIG"一騰，飛舞來去，瀟灑自如，著著都是攻勢，一招不待$n化解開去，第二招第三招已連綿而至！\n"NOR, me,target);

        //第二劍稍快
        addn_temp("apply/attack", damage/3, me);
        COMBAT_D->do_attack(me,target,query_temp("weapon", me));
        addn_temp("apply/attack", -damage/3, me);

        if(me->is_fighting(target) ){
        message_combatd(HIG"$N劍勢未止，左手指力已藴勁彈出，點向$n各路穴道，"+HIW"「玉簫劍法」"NOR+HIG"與"+HIW"「彈指神通」"NOR+HIG"互相為用，越發精微奧妙，變化無窮！\n"NOR, me,target);

        weapon->unequip();
        COMBAT_D->do_attack(me,target,query_temp("weapon", me));
        weapon->wield();
        }
        set_temp("th_jianzhi", sword/10, me);

        if( query_temp("th_jianzhi", me)>70 )
        set_temp("th_jianzhi", 70, me);

        call_out("checking", 1, me, weapon,speed,damage);

        return 1;
}

void checking(object me, object weapon,int speed, int damage)
{
        if (!me) return;
        if( !living(me) || me->is_ghost() )
        {
                remove_effect(me, weapon, speed, damage);
                return ;
        }
        if( !me->is_fighting() )
        {
                message_combatd("\n$N見戰局已畢，便即收起了劍指相配的功法。\n", me);
                remove_effect(me, weapon, speed, damage);
                return ;
        }

        else if( environment(weapon) != me || weapon != query_temp("weapon", me) )
        {
                message_combatd("\n$N手中兵器已失，當下收回了劍指相配的攻勢。\n"NOR, me);
                remove_effect(me, weapon, speed, damage);
                return ;
        }
        else if( me->query_skill_mapped("sword") != "yuxiao-jianfa"
         || me->query_skill_mapped("finger") != "tanzhi-shentong"
         || me->query_skill_prepared("finger") != "tanzhi-shentong" )
        {
                remove_effect(me, weapon, speed, damage);
                message_combatd(HIG"\n$N一揮"+weapon->name()+HIG"，驟然變換招數，不再是玉簫劍法與彈指神通的搭配進擊！\n"NOR, me);
                return ;
        }
        else if( query("neili", me)<500 || query("jingli", me)<500 )
        {
                tell_object(me, HIW "\n你驚覺內息漸弱，再如此快攻恐怕後繼乏力，當下不動聲色，暗暗收了左手「彈指神通」攻勢。\n" NOR);
                remove_effect(me, weapon, speed, damage);
                return ;
        }
        else if( query_temp("th_jianzhi", me) <= 20 )
        {
                remove_effect(me, weapon, speed, damage);
                message_combatd(HIG"\n$N一揮"+weapon->name()+HIG"，左手食中二指捏起劍訣，心無旁騖地使動「玉簫劍法」！\n"NOR, me);
                return;
        }

                else call_out("checking", 1, me, weapon,speed,damage);
                return;
}

void remove_effect(object me, object weapon, int speed, int damage)
{
        if (!me) return;
        addn_temp("apply/defense", -damage, me);
        addn_temp("apply/attack", -damage, me);

        delete_temp("th_jianzhi", me);
}