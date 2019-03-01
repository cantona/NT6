#include <weapon.h>
#include <ansi.h>

inherit HAMMER;

#define ZHUJIAN    "/clone/lonely/book/zhujian1"

void create()
{
        set_name(NOR + YEL "黃金斧" NOR, ({"huangjin fu", "huangjin", "fu"}));
        set_weight(20000);
        if (clonep())
                destruct(this_object());
        else {
                set("long", YEL "這是一柄純金黃鑄造的大斧，斧柄末端似乎有些鬆動。\n" NOR);
                set("unit", "柄");
                set("value", 800000);
                set("no_sell", 1);
                set("material", "gold");
                set("wield_msg", YEL "$N" YEL "舉起一柄純黃所鑄的大斧，隨手揮舞了兩下。\n" NOR);
                set("unwield_msg", YEL "$N" YEL "哈哈一笑，將手中的黃金斧收回背後。\n" NOR);
                set("stable", 100);
        }
        init_hammer(180);
        setup();
}

mixed hit_ob(object me, object victim, int damage_bonus)
{
        int n;
        int my_exp, ob_exp;

        if (me->query_skill_mapped("hammer") != "leiting-fu"
           || me->query_skill("leiting-fu", 1) < 150)
                return damage_bonus / 2;

        switch (random(6))
        {
        case 0:
                n = me->query_skill("hammer");
                victim->receive_damage("qi", n, me);
                victim->receive_wound("qi", n, me);
                return YEL "$N" YEL "一聲斷喝，手中黃金斧霎時金芒暴漲，呼的一聲朝$n"
                       YEL "猛劈而去！\n" NOR;
        }
        return damage_bonus;
}

void init()
{
        add_action("do_pick", "pick");
        add_action("do_pick", "turn");
}

int do_pick(string arg)
{
        object me, ob;
        me = this_player();

        if (! arg || ! id(arg))
                return 0;

        ob = find_object(ZHUJIAN);
        if (! ob) ob = load_object(ZHUJIAN);
        if (! environment(ob))
        {
                ob->move(me, 1);
                message_vision(HIC "$N" HIC "扭開斧柄，發現斧柄中空，其中藏"
                               "有一卷竹簡。\n$N" HIC "頓時大喜過望，連忙將"
                               "之取出，收入懷中。\n" NOR, me);
                return 1;
        } else
                return notify_fail(YEL "你扭開斧柄，發現柄中空空如也，什麼"
                                   "都沒有。\n" NOR);
}