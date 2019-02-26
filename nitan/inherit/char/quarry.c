// Inherit: quarry.c 獵物
// Create by Vin for Heros.cn

#include <ansi.h>
inherit NPC;

int is_quarry()
{
        return 1;
}

void setup()
{
        if (query("aves"))
        {
                set("limbs", ({ "頭部", "身體", "左翅", "右翅",
                                "爪子", "尾巴" }));
                set("verbs", ({ "bite", "claw" }));
        } else
        {
                set("limbs", ({ "頭部", "身體", "腹部", "背部",
                                "前腳", "後腳", "尾部" }));
                set("verbs", ({ "hoof", "bite", "claw" }));
        }
        set("race", "野獸");
        set("attitude", "aggressive");
        ::setup();
}

void init()
{
        object me, ob;

        ::init();
        if (! interactive(me = this_player()))
                return;

        // 自動攻擊馭獸術等級不高的玩家
        if ((int)me->query_skill("training", 1) < 100 &&
            query_temp("owner") != query("id", me) &&
            !query("no_auto_kill"))
        {
                remove_call_out("kill_ob");
                call_out("kill_ob", 0, me);
        }

        remove_call_out("disappear");
        call_out("disappear", 15);
}

void disappear()
{
        object ob = this_object();

        // 捕獵呼出的野獸會遁之
        if (living(ob) && query("owner", ob))
        {
                message_vision(WHT "\n突然$N" WHT "猛地一竄，瞬間便"
                               "消失得無影無蹤。\n\n", ob);
                destruct(ob);
        }
}

void die(object killer)
{
        object me, item;
        object ob = this_object();
        int power, skill;
        string msg;

        if (query("aves"))
                message_vision(HIR "\n只見$N" HIR "撲騰了幾下，從半"
                               "空中墜落下來，死了。\n\n" NOR, ob);
        else
                message_vision(HIR "\n只聽$N" HIR "嚎了幾聲，倒在地"
                               "上撲騰了幾下，死了。\n\n" NOR, ob);

        if (objectp(me = killer)
           || objectp(me = query_last_damage_from()))
        {
                // 如果為自己的獵物，則獎勵之
                // if (query("owner", ob) == query("id", me) &&
                if (
                   query("combat_exp", me) <= 5000000)
                {
                        // 根據獵物設定的參數來給予獎勵
                        power = query("power", ob);

                        if (power < 50)
                                power = 50;

                        if (power > 500)
                                power = 500;

                        GIFT_D->delay_bonus(me, ([ "prompt" : "通過這次獵取" + ob->name() +
                                                              HIG "的經歷",
                                                   "exp"    : random(power) + power,
                                                   "pot"    : random(power / 2) + power / 2,
                                                   "score"  : random(power / 4), ]));
                }
                skill = me->query_skill("hunting", 1);

                // 獲得物品
                if (query("item1", ob) && random(skill) > 10)
                {
                        item = new(query("item1", ob));
                        item->move(me, 1);

                        msg = HIC "你仔細翻尋" + ob->name() +
                              HIC "的屍體，從上面割下了一" +
                              query("base_unit", item) +
                              item->name() + HIC;

                        // 一定機率獲得高級物品
                        if (query("item3") && random(skill) > 60
                           && random(5) > 3)
                        {
                                item = new(query("item3"));
                                item->move(me, 1);

                                msg += "及一" + query("base_unit", item) +
                                       item->name() + HIC;
                        } else
                        if (query("item2") && random(skill) > 30
                           && random(4) > 2)
                        {
                                item = new(query("item2"));
                                item->move(me, 1);

                                msg += "及一" + query("base_unit", item) +
                                       item->name() + HIC;
                        }
                        msg += "。\n\n" NOR;
                        tell_object(me, msg);
                }
        }
        destruct(ob);
}
