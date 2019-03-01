// hun.c 大雅若俗

#include <ansi.h>

inherit F_SSERVER;

int perform(object me, object target)
{
        string msg,str,force;
        object weapon,weapon2;
        int n;
        int skill, ap, dp, damage;

        me->clean_up_enemy();
        if (! target) target = me->select_opponent();

        skill = me->query_skill("daya-jian", 1);

        if (! me->is_fighting(target))
                return notify_fail("大雅若俗只能對戰鬥中的對手使用。\n");

        if(me->query_skill_mapped("sword") != "daya-jian") 
                return notify_fail("你沒有用大雅劍法，無法使用大雅若俗絕招！\n");

        if (skill < 100)
                return notify_fail("你的大雅劍法等級不夠，練好了再來！\n");

        if( !objectp(weapon=query_temp("weapon", me)) || 
            query("skill_type", weapon) != "sword" )
                return notify_fail("你使用的武器不對。\n");

        if( query("neili", me)<500 )
                return notify_fail("你的內力不夠。\n");
        
        ap = me->query_skill("sword") + me->query_skill("force");
        ap+=query("jiali", me);
        ap+=query("jianu", me);

        damage = ap + random(ap);
                
        dp = target->query_skill("parry",1) + target->query_skill("dodge",1);
        dp = dp*3/2;

        msg = HIC "\n$N" HIC "先行存念，內勁真氣勃發，" NOR CYN "大雅古劍法" HIC "頓時揮洒得淋漓盡致！\n" +
              weapon->name() + HIC "如同活了一樣，幻化出滿天劍影，向$n" HIC "撲面罩來！\n\n" NOR;

        message_combatd(msg, me, target);

        n=query("tianmo_jieti/times", me);
        
        while (n-- && me->is_fighting(target))
        {
                if (! target->is_busy() && random(3))
                        target->start_busy(1);
                COMBAT_D->do_attack(me, target, weapon, 0);
        }

        force = me->query_skill_mapped("force");
        if (!stringp(force)) force = "force";
        
        msg = HIM "\n$N" HIM "一陣狂攻之後，忽然招式一緩，身形急退，須臾已在丈許之外。\n"
              "$n" HIM "見$N" HIM "力有不繼，正要搶上反擊，$N" HIM "突然仗劍而立，雙目凝視$n" HIM "。\n"
              "$n" HIM "被這犀利的目光嚇得一哆嗦，不解$N" HIM "是何意，心頭一陣迷惘。\n"
              "忽聞$N" HIM "大喝一聲:\n"
              HIW "風蕭蕭兮易水寒，壯士一去兮不復還!\n"
              HIM "歌聲中混雜著強勁的" HIR + to_chinese(force)+ HIM"，$n" HIM "不由心神大亂。\n"
              "此時，只見$N" HIM "人劍合一，如流星、似閃電，刺向$n" HIM "，正是" NOR CYN "大雅古劍法" HIM "的" HIW "『不歸式』" HIM"！！\n\n" NOR;

        weapon2=query_temp("weapon", target);
        
        if (ap / 2 + random(ap) > dp || !living(target))
        {
                if (weapon2)
                        msg += HIM "$n" HIM "見$N" HIM "來勢兇猛，不敢正面抵擋，手中" + weapon2->name() + HIM "一顫側擊" + weapon->name() + HIM "的劍脊\n"
                               "$N" HIM "竟是置若罔聞，" HIW "『不歸式』" HIM "仍舊一往直前，$n" HIM "手中" + weapon2->name() + HIM "為$N內力侵灌而入，渾身振顫！\n" NOR;
                else
                        msg += HIM "$n" HIM "見$N" HIM "來勢兇猛，不敢正面抵擋，側身進步雙掌奮力側擊$N" HIM "\n"
                               "$N" HIM "竟是置若罔聞，" HIW "『不歸式』" HIM "仍舊一往直前，$n" HIM "無可奈何，被擊個正著！\n" NOR;

                target->receive_damage("qi", damage, me);
                target->receive_wound("qi", damage/2, me);
                str=COMBAT_D->status_msg(query("qi", target)*100/query("max_qi", target));
                msg += "($n"+str+")\n";
                target->start_busy(1);
        } else
        {
                if (weapon2)
                        msg += HIM "$n" HIM "見$N" HIM "來勢兇猛，不敢正面抵擋，手中" + weapon2->name() + HIM "一顫側擊" + weapon->name() + HIM "的劍脊\n"
                               "$N" HIM "被緩得一緩，" HIW "『不歸式』" HIM "已然落空！\n" NOR;
                else
                        msg += HIM "$n" HIM "見$N" HIM "來勢兇猛，不敢正面抵擋，側身進步雙掌奮力側擊$N" HIM "\n"
                               "$N" HIM "被緩得一緩，" HIW "『不歸式』" HIM "已然落空，但$n" HIM "也被$N" HIM "震得氣血翻湧！\n" NOR;
        }

        me->start_busy(2 + random(2));
        message_vision(msg, me, target);
        addn("neili", -damage/3, me);
        return 1;
}

