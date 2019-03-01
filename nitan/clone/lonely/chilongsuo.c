#include <weapon.h>
#include <ansi.h>

inherit WHIP;

void create()
{
        set_name(HIY "赤龍金索" NOR, ({ "chilong jinsuo", "chilong", "jinsuo", "suo", "whip" }) );
        set_weight(2800);
        if (clonep())
                destruct(this_object());
        else {
                set("long", HIY "一根由赤金所熔鑄的長索，索柄刻有一個小小的「"
                            HIR "向" HIY "」字。\n" NOR);
                set("unit", "根");
                set("value", 800000);
                set("no_sell", "這……這不是向…我的天，連天王老子你都敢惹？");
                set("material", "steel");
                set("wield_msg", HIY "$N" HIY "「颼」的一聲從腰間抽出一卷金索，"
                                 "凌空舞了個圈子。\n" NOR);
                set("unwield_msg", HIY "$N" HIY "冷笑一聲，將手中赤龍金索盤好，"
                                 "放回腰間。\n" NOR);
                set("stable", 100);
        }
        init_whip(100);
        setup();
}

mixed hit_ob(object me, object victim, int damage_bonus)
{
        int n;
        int my_exp, ob_exp;

        if (me->query_skill_mapped("whip") != "panlong-suo" ||
            me->query_skill("panlong-suo", 1) < 100)
                return damage_bonus / 2;

        switch (random(10))
        {
        case 0:
                if (! victim->is_busy())
                victim->start_busy(me->query_skill("whip") / 12 + 1);
                return HIY "$N" HIY "手中赤龍金索一抖，金索頓時化作一道金光，"
                       "遊龍般竄向$n" HIY "胸前要穴！\n" NOR;

        case 1:
                n = me->query_skill("whip");
                victim->receive_damage("qi", n * 2 / 3, me);
                victim->receive_wound("qi", n * 2 / 3, me);
                return HIY "只見$N" HIY "聚力于腕，赤龍金索霎時竟如同鐵棍一般"
                       "，向$n" HIY "橫掃而去！\n" NOR;
        }
        return damage_bonus;
}