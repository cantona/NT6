// This program is a part of NITAN MudLIB
// hun.c 劍魂

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

string name() { return HIM "劍魂" NOR; }

int can_not_hubo() { return 1;}

void check_fight(object me, object target, object weapon);
private int remove_attack(object me, object weapon);

int perform(object me, object target)
{
        string msg;
        object *ob, weapon;
        int ap, dp, count, p;
        int i, damage;

        if( !query("reborn/times", me) )
                return notify_fail("你尚未轉世重生，無法施展" + name() + "。\n");

        if( query("family/family_name", me) != "華山派"
         && member_array("華山派", query("reborn/fams", me)) == -1 )
                return notify_fail("你尚未轉世重生，無法施展" + name() + "。\n");

/*
        if( query("family/family_name", me) != "華山派" )
                return notify_fail("你不是華山派弟子，無法施展" + name() + "。\n");
*/
        /*
        if( !target ) target = offensive_target(me);

        if( !target
        ||      !target->is_character()
        ||      !me->is_fighting(target) )
                return notify_fail(HUN "只能對戰鬥中的對手使用。\n");
        */

        if( !me->is_fighting() )
                return notify_fail(name() + "只能對戰鬥中的對手使用。\n");

        if( query_temp("dugu_jianhun", me) )
                return notify_fail("你已在使用" + name() + "了！\n");

        weapon=query_temp("weapon", me);
        if( !objectp(weapon) || query("skill_type", weapon) != "sword" )
                return notify_fail("你手中無劍，如何能夠施展" + name() + "？\n");

        if( (int)me->query_skill("lonely-sword", 1) < 1000 )
                return notify_fail("你的獨孤九劍不夠嫻熟，難以施展" + name() + "。\n");

        if( me->query_skill("force") < 1200 )
                return notify_fail("你的內功火候未到，無法配合杖法施展" + name() + "！\n");

        if( me->query_skill("sword", 1) < 1000 )
                return notify_fail("你劍法修為不足，還不會使用" + name() + "！\n");

        if( me->query_skill("sword-cognize", 1) < 500 )
                return notify_fail("你劍道修養火候未到，還不會使用" + name() + "！\n");

        if( me->query_skill("martial-cognize", 1) < 500 )
                return notify_fail("你武學修養火候未到，還不會使用" + name() + "！\n");

        if( query("neili", me) <= 1000 )
                return notify_fail("你的內力不夠施展" + name() + "！\n");

        if( query("jingli", me) <= 500 )
                return notify_fail("你的精力不夠施展" + name() + "！\n");

        count = me->query_skill("sword-cognize", 1) + me->query_skill("martial-cognize", 1);
        count /= 500;

        msg = HIW "$N" HIW "神態寫意，温柔撫弄手中的" + weapon->name() + HIW "，只見" + weapon->name() +
              HIW "表面掠過一絲光影，微微顫動，整把劍竟靈動起來、有若生物。\n" NOR
              HIM"$N"HIM"將手中"+query("name", weapon)+HIM"緩緩刺出，劍招隨意無章！\n"NOR
              HIM "這招看似緩慢，其實疾如閃電，看似隨意無章，卻是和" + weapon->name() + HIM "融為一體，無懈可擊，藴涵着返璞歸真的意境。\n" NOR;

        message_combatd(msg, me);

        damage = damage_power(me, "sword");
        damage += query_temp("apply/damage", me);
        damage += query("jiali", me);
        damage *= 5;
        ap = attack_power(me, "sword") +
             me->query_skill("dodge");

        ob = me->query_enemy();
        addn_temp("apply/ap_power", 100, me);
        for (i = 0; i < sizeof(ob); i++)
        {
                dp = defense_power(ob[i], "parry") +
                     ob[i]->query_skill("dodge");

                if (ap * 2 / 3 + random(ap) > dp)
                {
                        ob[i]->receive_damage("qi", damage, me);
                        ob[i]->receive_wound("qi", damage / 2, me);
                        ob[i]->set_weak(5);
                        set("neili", 0, ob[i]);
                        set("jiali", 0, ob[i]);
                        ob[i]->apply_condition("no_exert", 10);
                        ob[i]->apply_condition("no_perform", 10);

                        msg = HIR "$n" HIR "想招架卻感無從招架，想躲避也感到無處可躲，登時被$N" HIR "一劍劃過，\n"
                              HIR "遭受重創，一陣錐心的刺痛，全身真氣源源而瀉！\n" NOR;

                        if( query_temp("apply/fatal_blow", me) && query("ability2/fatal_blow", me) )
                        {
                                if( random(100) < query("ability2/fatal_chance", me) )
                                {
                                        ob[i]->receive_damage("qi", query("qi", ob[i]) * query_temp("apply/fatal_blow", me)/100, me);
                                        ob[i]->receive_wound("qi", query("qi", ob[i]) * query_temp("apply/fatal_blow", me)/200, me);
                                        msg += HIR "緊接着，$N" HIR "追加了致命一擊，給$n" HIR "造成更嚴重的創傷。\n" NOR;
                                }
                        }
                        p=query("qi", ob[i])*100/query("max_qi", ob[i]);
                        msg += "( $n"+COMBAT_D->eff_status_msg(p)+" )\n";
                        message_vision(msg, me, ob[i]);
                } else
                {
                        ob[i]->start_busy(2);
                        msg = HIC "$n" HIC "情急之下，不及考慮，倒地一滾，僥倖避開$N" HIC "這一招的攻擊，冷汗直淋！\n" NOR;
                        message_vision(msg, me, ob[i]);
                }
        } ;
        addn_temp("apply/ap_power", -100, me);
        me->start_busy(2);
        set_temp("dugu_jianhun", 1, me);
        addn("neili", -200, me);
        addn("jingli", -100, me);

        msg = HIY "$N" HIY "握緊" + weapon->name() + HIY "向天一指, 叫道 : 劍魂一出 ～ 血光漫天 ～ \n"
              HIY "頓時" + weapon->name() + HIY "劍身化出一道紅色的劍形，在天空中恣意飛旋穿梭 ...\n" NOR;

        message_combatd(msg, me);
        call_out("check_fight", 1, me, weapon, count);

        return 1;
}

void check_fight(object me, object weapon, int count)
{
        object *ob;
        int damage, ap, dp, p;
        string msg, limb;
        string *limbs;
        int i;

        if( !objectp( me ) || !objectp(weapon) ) return;

        if( query_temp("dugu_jianhun", me) >= count
        ||      !me->is_fighting() )
        {
                call_out("remove_attack", 1, me, weapon);
                return;
        }

        addn_temp("dugu_jianhun", 1, me);
        message_combatd(HIR "\n劍魂以閃電般的高速在空中穿梭, 以狂亂無比的熱情盡情狂舞 ...\n" NOR, me);

        ob = me->query_enemy();
        ap = me->query_skill("sword", 1) + me->query_skill("sword-cognize", 1) +
             me->query_skill("martial-cognize", 1);
        damage=ap+query("weapon_prop/damage", weapon);
        damage += damage_power(me, "sword");
        damage *= 5;

        for (i = 0; i < sizeof(ob); i++)
        {
                if (! objectp(ob[i])) continue;
                dp=query("parry", ob[i])+
                     ob[i]->query_skill("dodge", 1);

                if (dp / 3 + random(dp) < ap)
                {
                        limbs=query("limbs", ob[i]);
                        if (! arrayp(limbs))
                        {
                                limbs = ({ "身體" });
                                set("limbs", limbs, ob[i]);
                        }
                        limb = limbs[random(sizeof(limbs))];
                        ob[i]->start_busy(1);
                        ob[i]->receive_damage("qi", damage, me);
                        ob[i]->receive_wound("qi", damage / 2, me);
                        p=query("qi", ob[i])*100/query("max_qi", ob[i]);
                        msg = COMBAT_D->damage_msg(damage, "割傷");
                        msg = replace_string(msg, "$l", limb);
                        msg = replace_string(msg, "$w", weapon->name());
                        msg += "( $n"+COMBAT_D->eff_status_msg(p)+" )\n";
                        message_combatd(msg, me, ob[i]);
                }
        }

        call_out("check_fight", 1, me, weapon, count);
}

int remove_attack(object me, object weapon)
{
        if( !objectp( me ) ) return 1;
        if( !query_temp("dugu_jianhun", me))return 1;

        delete_temp("dugu_jianhun", me);
        message_combatd(HIW "一陣狂舞之後, 劍魂又自動飛入你的手中" + weapon->name() + HIW " ...\n" NOR, me);

        return 1;
}
