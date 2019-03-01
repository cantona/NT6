#include <ansi.h>
#include <command.h>

inherit F_CLEAN_UP;

int main(object me, string str)
{
        object ob, stone;
        int p, mp;

        if (! str)
                return notify_fail("你要熔煉什麼物品？\n");

        if (me->is_busy())
                return notify_fail("先忙完了你的事情再做這件事情吧。\n");

        if (me->is_fighting())
                return notify_fail("你現在正在打架，沒時間做這些事情。\n");

        if (! objectp(ob = present(str, me)))
                return notify_fail("你身上沒有這件物品。\n");

        if (me->query_skill("force") < 300)
                return notify_fail("你的內功修為不夠，難以熔煉物品。\n");

        if( query("max_neili", me)<5000 )
                return notify_fail("你的內力修為不夠，難以熔煉物品。\n");

        if( query("neili", me)<3000 )
                return notify_fail("你現在的內力不足，難以熔煉物品。\n");

        if( !query("can_make", ob) || !query("item_origin", ob) )
                return notify_fail("這東西似乎熔煉不出什麼。\n");

        p=query("power_point", ob);

        message_vision(HIM "$N" HIM "將" + ob->name() +
                       HIM "握于掌中，默默運轉內力，迫"
                       "使其熔化。\n" NOR, me);

        if (p < 50)
        {
                message_vision(HIR "突然卻見" + ob->name() +
                               HIR "嗤的化作一股青煙，什麼都"
                               "沒有留下。\n" NOR, me);
                destruct(ob);
                return 1;
        }

        p = random(p * 3 / 2);

        if (p > 120)
                stone = new("/clone/fam/item/stone5");
        else if (p > 90)
                stone = new("/clone/fam/item/stone4");
        else if (p > 70)
                stone = new("/clone/fam/item/stone3");
        else if (p > 50)
                stone = new("/clone/fam/item/stone2");
        else
                stone = new("/clone/fam/item/stone1");

        message_vision(HIM "霎時只見$N" HIM "掌心白霧蒸騰，似乎發"
                       "生了什麼不同尋常的事情。\n" NOR, me);

        if( query("value", stone) )
        {
                mp=query("value", stone)/300;
                mp = 5 + random(mp);
                if (mp < 5) mp = 5;
                if (mp > 100) mp = 100;

                addn("magic_points", mp, me);
                tell_object(me, HIC "你通過熔煉"+ stone->name() +
                                HIC "的過程，從而獲得了" +
                                chinese_number(mp) + "點靈慧。\n" NOR);
        }
        addn("max_neili", -1, me);
        addn("neili", -3000, me);
        me->start_busy(5);

        stone->set_amount(1);
        stone->move(me, 1);
        destruct(ob);
        return 1;
}

int help(object me)
{
write(@HELP
指令格式：fuse <物品ID>

此指令可讓你將某些物品熔化。一般來說能夠鑄造武器的原料都可以
被熔煉，不過熔煉物品需要比較高的內功等級和內力修為，每次成功
的熔煉都會增加一定數量的靈慧，但是會消耗一點最大內力。
HELP);
        return 1;
}

