// This program is a part of NT MudLIB
// qi.c 無形劍氣

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

string name() { return HIG "無形劍氣" NOR; }

int perform(object me, object target)
{
        object weapon;
        int damage;
        string msg;
        int ap, dp;
        int n;

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(name() + "只能對戰鬥中的對手使用。\n");

        if ((int)me->query_skill("force") < 420)
                return notify_fail("你的內功火候不夠，使不出" + name() + "。\n");

        if( query("max_neili", me) < 5000 )
                return notify_fail("你的內力修為還不足以使出如此犀利的" + name() + "。\n");

        if( query("neili", me) < 500 )
                return notify_fail("你的真氣不夠，無法使用" + name() + "。\n");

        if (me->query_skill("six-finger", 1) < 200)
                return notify_fail("你的六脈神劍修為有限，無法使用" + name() + "！\n");

        if (me->query_skill_prepared("finger") != "six-finger")
                return notify_fail("你沒有準備六脈神劍，無法使用" + name() + "。\n");

        if (! living(target))
               return notify_fail("對方都已經這樣了，用不著這麼費力吧？\n");

        msg = HIG "$N" HIG "中指一按，一股凌厲無倫的無形劍氣直奔$n" HIG "胸前射去。\n" NOR;

        ap = attack_power(me, "finger")+me->query_skill("force");
        dp = defense_power(target, "dodge") + target->query_skill("force");
        weapon=query_temp("weapon", target);
        me->start_busy(3);
        if (ap / 2 + random(ap) > dp)
        {
                damage = damage_power(me, "finger");
                if( (n = me->query_skill("qimai-liuzhuan", 1) / 100) >= 1 )
                {
                        msg += HIM"$N"HIM"運用氣脈流轉的輔助，使得無形劍氣傷害更強。\n"NOR;
                        damage += damage*n*15/100;
                }
                addn("neili", -400, me);
                if( !objectp(weapon) || query("skill_type", weapon) == "pin" )
                        msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 120,
                                                   HIR "$n" HIR "只覺得胸前一陣劇痛，鮮血"
                                                   "自創口激射而出，眼前頓時一黑！\n" NOR);
                else
                if( weapon->is_item_make() || query("damage", weapon)>180 ||
                    query("skill_type", weapon) == "hammer" )
                        msg += COMBAT_D->do_damage(me, target, REMOTE_ATTACK, damage, 100,
                                                   HIR "$n" HIR "橫" + weapon->name() + HIR "試圖招架，"
                                                   HIR "怎奈這股劍氣如此犀利，透過" + weapon->name() +
                                                   HIR "直震得$n" HIR "狂吐鮮血，五臟六腑都要翻轉過來！\n" NOR);
                else
                {
                        msg += COMBAT_D->do_damage(me, target, REMOTE_ATTACK, damage, 80,
                                                   HIR "$n" HIR "橫轉" + weapon->name() + HIR "，擋在胸"
                                                   "前，只聽啪啦一聲，" + weapon->name() +
                                                   HIR "碎成數截，激飛上天！\n$n" HIR "連退"
                                                   "幾步，“哇”的吐了一口鮮血，臉色變的慘白。\n" NOR);
                        weapon->move(environment(me));
                        set("no_wield", weapon->name()+"已經碎掉了，沒法裝備了。\n", weapon);
                        weapon->set_name("碎掉的" + weapon->name());
                        set("value", 0, weapon);
                }
        } else
        {
                msg += CYN "可是$p" CYN "內功頗為深厚，輕輕將這道劍氣化解于無形。\n" NOR;
        }
        message_combatd(msg, me, target);

        return 1;
}
