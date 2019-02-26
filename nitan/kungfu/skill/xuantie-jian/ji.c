
#include <ansi.h>

inherit F_SSERVER;

string name() { return "千均一擊"; }

int perform(object me, object target)
{
        object weapon;
        int skill, skill1;
        int myskill;
        int damageone;
        int damagesub;
        int damage;
        string msg;
        mixed ap,dp;
        int status_flag=0;

        if( !target ) target = offensive_target(me);
        if( !target || !target->is_character() || !me->is_fighting(target) )
                return notify_fail("千均一擊只能對戰鬥中的對手使用。\n");

        if( !objectp(weapon=query_temp("weapon", me)) )
                return notify_fail("你未持武器，不能使用千均一擊！\n");

        if( me->query_skill("force") < 300 )
                return notify_fail("你的內功火候未到，無法施展千均一擊！\n");

        if( me->query_skill("sword") < 300 )
                return notify_fail("你的劍法火候未到，無法施展千均一擊！\n");

        if( query("max_neili", me) <= 3000 )
                return notify_fail("你的內力不夠施展千均一擊！\n");

        if( query("neili", me) <= 1000 )
                return notify_fail("你的內力不夠施展千均一擊！\n");

        if( query("jingli", me) <= 1000 )
                return notify_fail("你的精力不夠施展千均一擊！\n");

        msg=HIW"\n\n$N身子左斜，左手抽出揹負的"+query("name", weapon)+"，順手一招「千均一擊」!\n"NOR;

        ap=attack_power(me, "sword");
        dp=defense_power(target, "force");
        damage=damage_power(me, "sword");
        damage+= query("jiali", me);

        if ( ap/2 + random(ap) > dp )
        {
                msg+=HIB"$N力道使得極猛,挺劍送出。$n早有提防，卻萬想不到來勢竟是如此猛烈，眼見閃避不及，\n"
                        "只聽砰的一聲猛響，登時連退了五六步，才勉強拿椿站定，等時臉如金紙。\n"NOR;
                target->receive_damage("qi", damage,  me);
                target->receive_wound("qi", random(damage/2)+damage/2, me);
                me->start_busy(1+random(2));
                status_flag=1;
        }

        else if( query("int", me)>random(query("int", target)*2) )
        {
                msg+=HIB"$N一劍擊出，右手長袖順勢拂去，$n頃刻間只感五臟六腑都似翻轉了，站在當地，既不敢運氣，\n"
                        "也不敢移動半步，便如僵了一般。\n"NOR;
                if (! target->is_busy())
                        target->start_busy(3+random(4));
                me->start_busy(2+random(2));
                status_flag=1;
        }
        else if (query("str", me)>random(query("str", target)*2) )
        {
                msg+=HIC"$N只覺對方衝撞而來的勁力綿綿不絕，越來越強,運出所有內力振臂一擊。\n" NOR;
                addn("neili", -300, me);
                addn("neili", -300, target);
                me->start_busy(1+random(2));
                if (! target->is_busy())
                        target->start_busy(1+random(2));
                status_flag=1;
        }
        else
        {
                msg += HIG"$n凌空飛躍，身形疾閃，使出本門輕功，身子往回輕輕一側，$N的發招數盡數落空。\n"NOR;
                me->start_busy(2+random(2));
        }
        addn("neili", -200, me);

        message_combatd(msg+"\n", me, target);
        if (status_flag==1) COMBAT_D->report_status(target);
        return 1;
}