#include <ansi.h>
#include <combat.h>

string name() { return HIW "碧海潮生按玉簫" NOR; }

inherit F_SSERVER;

int perform(object me, object target)
{
        string msg;
        int ap, dp;
        int damage, skill;
        object ob;

        if (! target)
        {
                me->clean_up_enemy();
                target = me->select_opponent();
        }

        if (! target || ! me->is_fighting(target))
                return notify_fail(name() + "只能對戰鬥中的對手使用。\n");

        if( !objectp(ob=query_temp("handing", me)) || !ob->valid_as_xiao() )
        {
                if( !objectp(ob=query_temp("weapon", me) )
                   || ! ob->valid_as_xiao())
                {
                        // 手裡的兵器也不能作為蕭使用
                        return notify_fail("你手裡沒有拿蕭，難以施展" + name() + "。\n");
                }
        }

        skill = me->query_skill("yuxiao-jianfa", 1);

        if (skill < 180)
                return notify_fail("你玉簫劍法等級不夠, 難以施展" + name() + "。\n");

        if ((int)me->query_skill("bibo-shengong", 1) < 180)
                return notify_fail("你碧波神功修為不夠，難以施展" + name() + "。\n");

        if ((int)me->query_skill("bihai-chaosheng", 1) < 180)
                return notify_fail("你的碧海潮生曲太低，難以施展" + name() + "。\n");

        if (me->query_skill_mapped("sword") != "yuxiao-jianfa")
                return notify_fail("你沒有激發玉簫劍法，難以施展" + name() + "。\n");

        if( query("neili", me)<300 )
                return notify_fail("你現在的內力不夠，難以施展" + name() + "。\n");

        if (! living(target))
                return notify_fail("對方都已經這樣了，用不著這麼費力吧？\n");

        ap = attack_power(me, "sword") +
             me->query_skill("bihai-chaosheng", 1);
        dp = defense_power(target, "force") +
             target->query_skill("bihai-chaosheng", 1);

        damage = 0;

        msg = HIW "\n只見$N" HIW "手按玉簫，腳踏八卦四方之位，奏出"
              "一曲「碧海潮生按玉簫」。便聽得那簫聲如鳴琴擊玉，輕輕"
              "發了幾聲，接著悠悠揚揚，飄下清亮柔和的洞簫聲來。\n" NOR;

        if (ap + random(ap) > dp)
        {
                msg += HIR "$n" HIR "只感心頭一震，臉上情不自禁的露"
                       "出了一絲微笑。\n" NOR;
                damage += damage_power(me, "sword");
        } else
                msg += HIC "$n" HIC "暗暗凝神守一，對這簫聲自是應付"
                       "裕如。\n" NOR;

        msg += HIW "\n突然又聽那洞簫聲情致飄忽，纏綿宛轉，便似一個女"
               "子一會兒嘆息，一會兒又似呻吟，一會兒卻又軟語溫存或柔"
               "聲叫喚。\n" NOR;

        if (ap + random(ap / 2) > dp)
        {
                msg += HIR "$n" HIR "只感全身熱血沸騰，就只想手舞足"
                       "蹈的亂動一番。\n" NOR;
                damage += damage_power(me, "sword");
        } else
                msg += HIC "$n" HIC "暗暗凝神守一，對這簫聲自是應付"
                       "裕如。\n" NOR;

        msg += HIW "\n那簫聲清亮宛如大海浩淼，萬裡無波，遠處潮水緩緩"
               "推近，漸近漸快，其後洪濤洶湧，白浪連山，而潮水中魚躍"
               "鯨浮，海面風嘯鷗飛，水妖海怪群魔弄潮，極盡變幻之能事"
               "。\n" NOR;

        if (ap / 2 + random(ap) > dp)
        {
                msg += HIR "霎時間$n" HIR "只感心頭滾熱，喉幹舌燥，"
                       "說不出的難受。\n" NOR;
                damage += damage_power(me, "sword");
        } else
                msg += HIC "$n" HIC "暗暗凝神守一，對這簫聲自是應付"
                       "裕如。\n" NOR;

        msg += HIW "\n時至最後，卻聽那簫聲癒來癒細，幾乎難以聽聞，便"
               "尤如大海潮退後水平如鏡一般，但海底卻又是暗流湍急，洶"
               "湧澎湃。\n" NOR;

        if (ap / 2 + random(ap / 2) > dp)
        {
                msg += HIR "此時$n" HIR "已身陷絕境，全身氣血逆流，"
                       "再也無法脫身。\n" NOR;
                damage += damage_power(me, "sword");
        } else
                msg += HIC "$n" HIC "暗暗凝神守一，對這簫聲自是應付"
                       "裕如。\n" NOR;

        target->receive_damage("jing", damage * 2 / 3, me);
        target->receive_wound("jing", damage / 2, me);

        me->start_busy(2 + random(2));
        addn("neili", -200, me);

        message_combatd(sort_msg(msg), me, target);
        return 1;
}