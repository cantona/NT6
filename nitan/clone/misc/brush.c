// brush.c
//
// This is the basic equip for players just login.

#include <ansi.h>
#include <armor.h>

inherit CLOTH;

void create()
{
        set_name("刷子", ({ "brush", "shua zi" }) );
        set_weight(500);
        if (clonep())
                set_default_object(__FILE__);
        else
        {
                set("unit", "把");
                set("long", "一把刷子，是專門用來刷鞋用的。\n");
                set("value", 200);
        }
        setup();
}

void init()
{
        add_action("do_swab", "swab");
        add_action("do_swab", "caxie");
}

int do_swab(string arg)
{
        int exp;
        object ob;      
        object me;
        object money;
        object shoeshine;

        me = this_player();
        if (! arg || ! objectp(ob = present(arg, environment(me))))
                return notify_fail("你要為誰擦鞋？\n");

        if( !ob->is_character() || query("not_living", ob) )
                return notify_fail("看清楚了，那不是活人！\n");

        if( !query("can_speak", ob) )
                return notify_fail("自古以來沒有聽説過給" +
                                   ob->name() + "擦鞋的！\n");

        if (! living(ob))
                return notify_fail("你還是等別人醒了再説吧！\n");

        if (ob == me)
        {
                message_vision("$N舉着手中的刷子，看着自己，想起"
                               "自己真是好命苦，一時忍不住就要落淚！\n",
                               this_player());
                return 1;
        }

        if (! objectp(shoeshine = present("xie you", me)))
        {
                write("你現在沒有鞋油了。\n");
                return 1;
        }

        if (me->is_busy())
                return notify_fail("你現在正忙着呢，還是等一會兒再説吧！\n");

        me->start_busy(2);

        if (playerp(ob))
        {
                shoeshine->cost();

                if( query("couple/couple_id", me) == query("id", ob) )
                {
                        message_vision("$N跪下來一臉諂媚的把$n的鞋擦得亮晶晶"
                                       "的。$n拍了拍$N的頭説道：“" +
                                       (query("gender", me) == "男性"?
                                        "老公，你的鞋擦得好好哦。" :
                                        "老婆，你的鞋擦的真漂亮！") +
                                       "”\n", me, ob);
                        return 1;
                }

                message_vision("$N一臉諂媚的替$n把鞋擦得油亮，只見$n"
                               "笑眯眯看着$P，道：“好，好！”\n",
                               me, ob);
                if (ob->is_fighting(me))
                {
                        if( query("weiwang", me)>1000 )
                                addn("weiwang", -100, me);
                        else
                        {
                                message_vision("$N笑道：你的道行還淺，再怎麼"
                                               "給我擦鞋也沒有用！看招！\n",
                                               ob);
                                write("你心中大罵不止！\n");
                                return 1;
                        }
                        ob->remove_enemy(me);
                        ob->remove_killer(me);
                        me->remove_enemy(ob);
                        me->remove_killer(ob);
                        write(ob->name() + "停止了對你的攻擊。\n");
                        return 1;
                }
                write("你心中暗罵：這個衰鬼，一分錢都沒有！\n");
                return 1;
        }

        if (me->is_fighting())
        {
                write("你還是等打完架再擦鞋吧！\n");
                return 1;
        }

        if( time()-query_temp("last_swab", ob)<240 )
        {
                message_vision("$n一腳踢開了$N，道：今天我已"
                               "經擦過了，你還是改天再來吧！\n",
                               me, ob);
                return 1;
        }

        message_vision("$N彎下腰來，殷勤的把$n的鞋擦了一遍又一遍。\n",
                       me, ob);
        shoeshine->cost();
        if( query("weiwang", me)>10 )
                addn("weiwang", -10, me);
        else
                set("weiwang", 0, me);

        set_temp("last_swab", time(), ob);

        exp = 120 + random(50);
        if( query("combat_exp", me)<500000 )
                GIFT_D->delay_work_bonus(me, ([ "exp" : exp, "pot" : exp / 3 ]));

        else
                addn("potential", exp/3, me);

        money = new("/clone/money/coin");
        money->set_amount(30 + random(30));

        message_vision("$n看看鞋，哼哼道：好！不錯，這點錢是賞給你的！\n"
                       "$N連忙點頭哈腰，笑眯眯的接了過來。\n", me, ob);
        money->move(me, 1);
        if (! query("zhufu_mod/boots", me) && random(10) == 1) 
        {
                message_vision("$n對$N嘿嘿一笑，道：幹得不賴，有點" 
                               "意思，這個神之祝福戰衣就算是我送給你的禮物吧。\n",
                               me, ob);
                money = new("/clone/goods/zhufu_boots"); 
                money->move(me, 1);
                tell_object(me, HIM "\n你獲得了一個" + money->name() + HIM "！\n" NOR);
                set("zhufu_mod/boots", 1, me); 
        }
        return 1;
}
