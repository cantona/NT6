
#include <ansi.h>
#include <command.h>

inherit F_CLEAN_UP;

int main(object me, string str)
{
        object ob, stone;
        string type;
        int p, mp;

        if( !str )
                return notify_fail("你要凝練什麼物品？\n");

        if( me->is_busy() )
                return notify_fail("先忙完了你的事情再做這件事情吧。\n");

        if( me->is_fighting() )
                return notify_fail("你現在正在打架，沒時間做這些事情。\n");

        if( !objectp(ob = present(str, me)) )
                return notify_fail("你身上沒有這件物品。\n");

        if( me->query_skill("force") < 300 )
                return notify_fail("你的內功修為不夠，難以凝練物品。\n");

        if( query("max_neili", me)<5000 )
                return notify_fail("你的內力修為不夠，難以凝練物品。\n");

        if( query("neili", me)<3000 )
                return notify_fail("你現在的內力不足，難以凝練物品。\n");

        if( !query("can_sign", ob) || !(p=query("quality_level", ob)) )
                return notify_fail("這東西似乎凝練不出什麼。\n");

        if( !query("require/level", ob) || query("require/level", ob) < 20 )
                return notify_fail("必須是20級以上的裝備才能凝練。\n");

        message_vision(HIM "$N" HIM "將" + ob->name() +
                       HIM "握於掌中，默默運轉內力，開始凝鍊。\n" NOR, me);

        if (random(100)<50 )
        {
                message_vision(HIR "突然卻見" + ob->name() +
                               HIR "嗤的化作一股青煙，什麼都"
                               "沒有留下。\n" NOR, me);
                destruct(ob);
                return 1;
        }

        if( query("skill_type", ob) )
                stone = new("/clone/enchase/weapon_soul"+p);
        else 
        {
                type = query("armor_type", ob);
                stone = new("/clone/enchase/"+type+"_soul"+p);
        }

        message_vision(HIM "霎時只見$N" HIM "掌心白霧蒸騰，似乎發"
                       "生了什麼不同尋常的事情。\n" NOR, me);

        if( query("value", stone) )
        {
                mp=query("value", stone)/300;
                mp = 5 + random(mp);
                if (mp < 5) mp = 5;
                if (mp > 100) mp = 100;

                addn("magic_points", mp, me);
                tell_object(me, HIC "你通過凝練"+ stone->name() +
                                HIC "的過程，從而獲得了" +
                                chinese_number(mp) + "點靈慧。\n" NOR);
        }
        addn("max_neili", -1, me);
        addn("neili", -3000, me);
        me->start_busy(5);

        stone->move(me, 1);
        destruct(ob);
        return 1;
}

int help(object me)
{
write(@HELP
指令格式：concise <物品ID>

此指令可讓你將某些物品凝鍊。一般來説所有怪外掉落的裝備都可以
被凝練，不過凝練物品需要比較高的內功等級和內力修為，每次成功
的凝練都會增加一定數量的靈慧，但是會消耗一點最大內力。
HELP);
        return 1;
}


