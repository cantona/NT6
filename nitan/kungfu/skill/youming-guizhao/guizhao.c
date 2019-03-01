// This program is a part of NITAN MudLIB
// guizhao.c  亡魂鬼爪

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

string name() { return HIB "亡魂鬼爪" NOR; }

int perform(object me, object target)
{
        int skill, ap, dp, damage;
        string msg, pmsg;

        if (! target)
        {
                me->clean_up_enemy();
                target = me->select_opponent();
        }

        if (! target || ! me->is_fighting(target))
                return notify_fail("「亡魂鬼爪」只能在戰鬥中使用。\n");

        if( query("gender", me) != "女性" )
                return notify_fail("你身為男子，難以領會「亡魂鬼爪」其中的奧妙。\n");

        if( query("shen", me)>0 )
                return notify_fail("你是俠義道人士，怎麼能用「亡魂鬼爪」這種陰毒武功。\n");

        if ((int)me->query_skill("youming-guizhao", 1) < 180)
                return notify_fail("你的幽冥鬼爪等級不夠，不能使用「亡魂鬼爪」。\n");

        if ((int)me->query_skill("claw", 1) < 180)
                return notify_fail("你的基本爪法極不夠嫻熟，不能使用「亡魂鬼爪」。\n");

        if ((int)me->query_skill("force", 1) < 180)
                return notify_fail("你的基本內功火候不夠，強行使用「亡魂鬼爪」會震傷自己的經脈。\n");

        /*
        if ((int)me->query_skill("xiaowuxiang", 1) < 180
                && (int)me->query_skill("bahuang-gong", 1) < 180
                && (int)me->query_skill("beiming-shengong", 1) < 180)
                return notify_fail("你的逍遙派內功火候不夠。\n");

        if (me->query_skill_mapped("force") != "xiaowuxiang"
                || me->query_skill_mapped("force") != "bahuang-gong"
                || me->query_skill_mapped("force") != "beiming-shengong")
                return notify_fail("你沒有運用逍遙派內功！\n");
        */

        if( query("neili", me)<800 )
                return notify_fail("你現在真氣太弱，不能使用「亡魂鬼爪」。\n");

        if( query("max_neili", me)<1000 )
                return notify_fail("你現在內力太弱，不能使用「亡魂鬼爪」。\n");

        if( query_temp("gz_pfmed", me) == 1 )
                return notify_fail("你剛使過這一招，不能聚集足夠的元氣。\n");

        if( !query("jiali", me) )
                return notify_fail("你爪上帶力不足，不能使用「亡魂鬼爪」。\n");

        skill = (int)me->query_skill("youming-guizhao", 1);

        message_combatd(HIB "\n突然$N" HIB "將雙掌變爪合于胸前，象風車般急轉數圈，而後雙爪向外一翻\n"
                        "繞著$n" HIB "疾轉數圈，五根手指向著$n頂門直下插落。\n\n" NOR, me, target);

        addn("neili", -400, me);
        set_temp("gz_pfmed", 1, me);

        call_out("recover", 1800 / skill, me);


        ap = attack_power(me, "claw");
        dp = defense_power(target, "dodge");

        if (ap / 2 + random(ap) > dp)
        {
                addn("neili", -100, me);
                damage = damage_power(me, "claw");
                damage+= query("jiali", me);
                pmsg = HIR "$n" HIR "只覺得頭頂一陣麻癢，$N"
                       HIR "的手爪已在$n" HIR "頭頂留下五個整整齊齊的指洞！\n" NOR;
                msg = COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 80, pmsg);
                me->start_busy(2);
        } else
        {
                msg = CYN "可是$p" CYN"見此招來勢凌厲，閃身護頭向後閃躲，雖是堪堪避過$P"
                      CYN "的攻擊，但已驚出了一身冷汗。\n\n" NOR;
                me->start_busy(3);
        }

        message_combatd(msg, me, target);

        if (userp(target))
                target->fight_ob(me);
        else
        if (! target->is_killing(me))
                target->kill_ob(me);
        return 1;
}

int recover(object me)
{
        if (! me) return 0;

        delete_temp("gz_pfmed", me);
        return 1;
}
