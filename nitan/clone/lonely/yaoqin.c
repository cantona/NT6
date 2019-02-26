#include <weapon.h>
#include <music.h>
#include <ansi.h>

inherit SWORD;
inherit MI_QIN;

void create()
{
        set_name(HIW "白玉瑤琴" NOR,({ "baiyu yaoqin", "baiyu", "yaoqin", "qin" }) );
        set_weight(9000);
        if (clonep())
                destruct(this_object());
        else {
                set("long", HIW "這是一具通體都用上等白玉雕制而成瑤琴，非常的華麗及名貴。\n" NOR);
                set("unit", "具");
                set("value", 800000);
                set("no_sell", 1);
                set("material", "steel");
                set("wield_msg", HIW "$N" HIW "從背後緩緩取出一具白玉瑤琴，輕輕的"
                                 "合抱在手中。\n" NOR);
                set("unwield_msg", HIW "$N" HIW "微微一笑，將手中的白玉瑤琴收了起"
                                 "來，放到背後。\n" NOR);
                set("stable", 100);
        }
        init_sword(120);
        setup();
}

void init()
{
        add_action("play_qin", "play");
}

mixed hit_ob(object me, object victim, int damage_bonus)
{
        int n;
        int my_exp, ob_exp;

        if (me->query_skill_mapped("sword") != "qixian-wuxingjian" ||
            me->query_skill("qixian-wuxingjian", 1) < 100)
                return damage_bonus / 2;

        switch (random(12))
        {
        case 0:
                if (! victim->is_busy())
                victim->start_busy(me->query_skill("sword") / 10 + 2);
                return HIW "$N" HIW "大喝一聲，眼中精光一閃，琴音音律頓時一變，$n" HIW "霎"
                       "時覺得頭暈目眩，無法再戰！\n" NOR;

        case 1:
                n = me->query_skill("sword");
                victim->receive_damage("qi", n * 3 / 4, me);
                victim->receive_wound("qi", n * 3 / 4, me);
                return HIW "$N" HIW "一聲冷哼，反手拂過白玉瑤琴琴身，霎時琴音變得尖鋭無比，"
                       "猶如利箭一般射向$n" HIW "！\n" NOR;
        }
        return damage_bonus;
}