// This program is a part of NITAN MudLIB

#include <ansi.h>
#include <combat.h>

string name() { return HIC "滄海笑" NOR; }

inherit F_SSERVER;

int perform(object me, object target)
{
        string msg;
        object weapon, weapon2;
        int skill, ap, dp, damage, px, md, sx;
        int hp;

        me->clean_up_enemy();
        if( !target ) target = me->select_opponent();

        skill = me->query_skill("lonely-sword", 1);

        if( !me->is_fighting(target) )
                return notify_fail(name() + "只能對戰鬥中的對手使用。\n");

        if( skill < 200 )
                return notify_fail("你的獨孤九劍等級不夠，無法施展" + name() + "。\n");

        if( !objectp(weapon=query_temp("weapon", me) )
         || query("skill_type", weapon) != "sword" )
                return notify_fail("你使用的武器不對，無法施展" + name() + "。\n");

        if( me->query_skill_mapped("sword") != "lonely-sword" )
                return notify_fail("你沒有激發獨孤九劍，無法施展" + name() + "。\n");

        if( (int)me->query_skill("force") < 200 )
                return notify_fail("你的內功火候不夠，難以施展" + name() + "。\n");

        if( !living(target) )
                return notify_fail("對方都已經這樣了，用不着這麼費力吧？\n");

        if( query("neili", me)<500 ) 
                return notify_fail("你此時的內力不足，難以施展" + name() + "。\n"); 

        ap = attack_power(me, "sword");
        dp = defense_power(target, "dodge");

        px = target->query_skill("pixie-jian", 1);
        md = target->query_skill("moon-blade", 1);
        sx = target->query_skill("six-finger", 1);

        if( px || md )
                ap += ap/10;              // 作為萬劍之宗，對避邪劍法，圓月刀法有加成。

        if( sx )
                ap -= ap/10;              // 不擅長應付六脈聚氣成劍遠程攻擊，有減成。

        if( objectp(weapon2=query_temp("weapon", target)) )
        {
                msg = HIC "$N" HIC "一襲青衫，踏歌而來，口中作歌曰：" HBWHT "滄海一聲笑，滔滔兩岸潮，浮沉隨浪只記今朝\n" NOR
                        HIW "歌聲中，只見$N" HIW "肩膀微動，一道白光瞬間擊出，射向$n。  \n"  NOR;

                if( ap / 2 + random(ap) > dp )
                {
                        addn("neili", -100, me);
                        msg += HIR "$n" HIR "大駭，連忙舉起手中兵器胡亂抵擋，卻不想虎口劇痛，手中" + weapon2->name() +
                               HIR "捏不住，脱手而出。\n" NOR
                               HIC "$N" HIC "大笑道：$n" HIC "不過如此，嚐嚐下面這招滋味如何？\n \n" NOR;

                        weapon2->unequip();
                        weapon2->move(environment(me));
                } else
                {
                        addn("neili", -200, me);
                        msg += CYN "$n" HIY "心隨意動，手中" + weapon2->name() +  "輕輕一點。\n" NOR
                               HIY "只聽[叮]的一聲響，$N" HIY "輕笑道：$n" HIY "果然了得，\n" NOR
                               HIY "可做我對手。且接這招如何？ \n \n"NOR;
                }
                message_combatd(msg, me, target);
        }
        else
        {
                msg = HIC "$N" HIC "一襲青衫，踏歌而來，口中作歌曰：" HBWHT "滄海一聲笑，滔滔兩岸潮，浮沉隨浪只記今朝\n" NOR
                      HIW "$N" HIW "笑道：久聞$n" HIW "不凡，且接這招如何？  \n"  NOR;
                        message_combatd(msg, me, target);

        }

        msg = HIC "$N" HIC "繼續歌道：" HBWHT" 蒼天笑，紛紛世上潮，誰負誰勝出天知曉 \n" NOR
              HIC "$N" HIC "隨意揮灑手中的" + weapon->name() +"發出道道" HIW "劍氣"HIC"，寒光閃閃，\n" NOR
              HIC "從四面八方朝$n" HIC" 直射而去！\n" NOR;

        damage = damage_power(me, "sword");

        if( ap * 2/3 + random(ap) > dp )
        {
                damage = damage * 3;

                msg += COMBAT_D->do_damage(me, target, REMOTE_ATTACK, damage, 200,
                                           HIR "$n" HIR "被漫天劍氣驚得面如土色，只覺"
                                           "避無所避，擋無可擋，轉眼間" HIW "劍氣" HIR "臨身"
                                           "全身各大穴道鮮血噴濺！\n\n" NOR);


                        if( query_temp("apply/fatal_blow", me) && query("ability2/fatal_blow", me) )
                        {
                                if( random(100) < query("ability2/fatal_chance", me) )
                                {
                                        target->receive_damage("qi", query("qi", target) * query_temp("apply/fatal_blow", me)/100, me);
                                        target->receive_wound("qi", query("qi", target) * query_temp("apply/fatal_blow", me)/200, me);
                                        msg += HIR "緊接着，$N" HIR "追加了致命一擊，給$n" HIR "造成更嚴重的創傷。\n" NOR;
                                }
                        }

                me->start_busy(2);
                if( !target->is_busy() )
                        target->start_busy(3);
                addn("neili", -300, me);

        } else
        {
                msg += CYN "$n" CYN "眼見漫天" HIW "劍氣" CYN "，勢不可擋，"
                       "身法連閃之下，堪堪避了開去，驚出一身冷汗！\n\n" NOR;
                me->start_busy(3);
                addn("neili", -300, me);
                target->start_busy(3);
        }
        message_combatd(msg, me, target);

        hp=query("qi", target);

        if( hp<query("max_qi", target)/10 )
        {
                msg  = HIR "$N" HIR "見$n" HIR"渾身浴血，已是搖搖欲墜，歎了一聲道： \n" NOR
                       HIR "人生苦短，還是早早投胎去吧！手中" + weapon->name() +" 一揮！\n" NOR
                       HIR "$n" HIR "喉中咯咯作響，面上盡是不甘之色，終於倒了下去。 \n\n" NOR;
                msg += HIC"$N" HIC "青衫飄飄而去，歌聲如風：蒼生笑，不再寂寥，豪情仍在痴痴笑笑~~ \n\n\n" NOR;
                message_combatd(msg, me, target);
                target->die(me);
                return 1;
        }

        msg = HIC"$N" HIC "青衫飄飄而去，歌聲如風：蒼生笑，不再寂寥，豪情仍在痴痴笑笑~~ \n\n\n" NOR;

        message_combatd(msg, me, target);
        return 1;
}
