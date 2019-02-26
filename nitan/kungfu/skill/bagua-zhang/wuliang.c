// wuliang.c 八卦掌「乾坤無量」
// Create for Haiyan 2002

#include <ansi.h>


inherit F_SSERVER;
int perform(object me, object target)
{
        string msg;
        int ap, dp;
        int count, acter;
        int i, bsy, lvl;

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail("「乾坤無量」只能對戰鬥中的對手使用。\n");

        if (me->query_skill_mapped("strike") != "bagua-zhang") 
                return notify_fail("你沒有激發八卦掌，無法施展「乾坤無量」。\n"); 

        if ((int)me->query_skill("bagua-zhang", 1) < 120)
                return notify_fail("你的八卦掌不夠嫻熟，不會使用「乾坤無量」。\n");

        if( query_temp("weapon", me) || query_temp("secondary_weapon", me) )
                return notify_fail("「乾坤無量」只能空手施展。\n");  

        if (! me->query_skill_prepare() || me->query_skill_prepare() && 
            me->query_skill_prepared("strike") != "bagua-zhang") 
                return notify_fail("你現在沒有準備使用八卦掌，無法使用「乾坤無量」！\n"); 

        if( query("neili", me)<350 )
                return notify_fail("你的真氣不夠，無法使用「乾坤無量」。\n");

        msg = HIY "$N" HIY "掌法忽然變快，使出八卦掌法「乾坤無量」，腳下沿八卦方位疾走，雙掌虛虛實實地拍向$n。\n" NOR;

        dp = (target->query_skill("force", 1) + 
             target->query_skill("parry", 1) +
             target->query_skill("martial-cognize", 1)) / 3 +
             target->query_skill("count", 1); 

        if( query("character", me) == "光明磊落" || 
            query("character", me) == "國土無雙" || 
            query("character", me) == "狡黠多變" )
             acter = 3;
        else
             acter = 4;

        ap = (me->query_skill("taiji-shengong", 1) +
             me->query_skill("bagua-zhang", 1) +
             me->query_skill("martial-cognize", 1) + 
             me->query_skill("taoism", 1)) / acter; 

        if ( ap / 2 + random(ap) > dp )
        {
                msg += HIR "$n" HIR "被$N" HIR
                       "這一變化攻了個措手不及，“嘭嘭嘭”連中數掌，" HIR
                       "噴出幾口鮮血，臉色變得煞白！\n" NOR;
                count = ap / 28; 
                bsy = 2;
                lvl = me->query_skill("bagua-zhang", 1) / 60;
                addn_temp("apply/attack", count, me);
        } else
        {
                msg += HIC "$n" HIC "見$N" HIC "忽然變招，不敢大意，連忙屏息凝氣，小心應對，將$N"
                       HIC "的招式盡數拆解。\n" NOR;
                count = 0;
                lvl = 0;
                bsy = 5;
        }
                
        message_combatd(msg, me, target);

        addn("neili", -150, me);

        for (i = 0; i < lvl; i++)
        {
                if (! me->is_fighting(target))
                        break;
                COMBAT_D->do_attack(me, target, 0, 0);
        }

        addn_temp("apply/attack", -count, me);
        me->start_busy(2 + random(bsy));

        return 1;
}