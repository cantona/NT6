// Inherit: snake.c 蛇類
// Update by Vin for Heros.cn
// 設置毒蛇毒性level和毒液的量remain/maximum，毒蛇每次咬中對
// 方，都會將perhit 指明的毒量注入到對方的體內，每過一段時間
// 毒蛇會自動恢復supply 量的毒液。level將和武功的force做比較。
// 設置level時候應該參考內功等級。毒量和中毒UPDATE_CONDITION
// 的次數成正比，設置毒量的時候應該參考氣和精。

#include <ansi.h>
inherit NPC;

int is_snake()
{
        return 1;
}

void setup()
{
        mapping p;

        set("race", "蛇類");
        set("unit", "條");
        set("limbs", ({ "頭部", "身體", "七寸", "尾巴" }));
        set("verbs", ({ "bite" }));
        set("attitude", "aggressive");

        p = query("snake_poison");

        if (! p)
        {
                ::setup();
                return;
        }

        if (! intp(p["level"]))   p["level"]   = 30;
        if (! intp(p["perhit"]))  p["perhit"]  = 10;
        if (! intp(p["maximum"])) p["maximum"] = 20;
        if (! intp(p["remain"]))  p["remain"]  = p["maximum"];
        if (! intp(p["supply"]))  p["supply"]  = 1;
        if (! stringp(p["id"]))   p["id"]      = "nature snake";

        ::setup();
}

void init()
{
        object me, ob;

        ::init();
        if (! interactive(me = this_player()))
                return;

        // 自動攻擊蛇毒奇巧等級不高的玩家
        if (! present("xiong huang", this_player()) &&
            query_temp("owner") != query("id", me) &&
            (int)me->query_skill("shedu-qiqiao", 1) < 100)
        {
                remove_call_out("kill_ob");
                call_out("kill_ob", 0, me);
        }
        add_action("convert", "bian");
        add_action("convert", "convert");
        remove_call_out("disappear");
        call_out("disappear", 15);
}

mixed hit_ob(object me, object ob, int damage)
{
        mapping p;
        string  msg;
        int force;
        int dur;

        p = query("snake_poison", me);
        if (! p) return;
        if (damage / 3 + random(damage * 2 / 3) <
            (int)query_temp("apply/armor", ob))
        {
                // Defeated by armor
                return;
        }

        msg = "";
        dur = p["perhit"];
        if (dur > (int)p["remain"]) dur = p["remain"];
        p["remain"] = (int)p["remain"] - dur;
        this_object()->apply_condition("poison-supply", 1);
        if (! dur) return;

        force = (int)ob->query_skill("force");
        if (random(force / 2) + force / 2 >= (int)p["level"] &&
            query("neili", ob) > damage / 5)
        {
                if (query("qi", ob) < 150)
                {
                        msg = HIR "你覺得傷口有些發麻，連忙運功化解，但"
                              "是一時體力不支，難以施為。\n" NOR;
                } else
                if (query("jing", ob) < 60)
                {
                        msg = HIR "你覺得傷口有些發麻，連忙運功化解，但"
                              "是一時精神不濟，難以施為。\n" NOR;
                } else
                if (query("neili", ob) < damage / 5 + 50)
                {
                        msg = HIR "你覺得傷口有些發麻，連忙運功化解，但"
                              "是一時內力不足，難以施為。\n" NOR;
                } else
                {
                        addn("neili", -damage/5, ob);
                        ob->receive_damage("qi", 20);
                        ob->receive_damage("jing", 10);
                        return HIM "你覺得被咬中的地方有些發麻，連忙運功"
                               "化解毒性。\n" NOR;
                }
        }

        if (ob->affect_by("poison", ([ "level" : (int)p["level"],
                                       "name"  : "蛇毒",
                                       "id"    : "nature poison",
                                       "duration" : dur, ])))
        {
                msg += HIR "$n" HIR "臉色一變，只覺被咬中的地方一陣麻木。\n" NOR;
        }
        return msg;
}

void die(object killer)
{
        object me, item;
        object ob = this_object();
        int power, skill;
        string msg;

        message_vision(HIR "\n只見$N" HIR "卷著身子在地上撲騰了"
                       "幾下，死了。\n\n" NOR, ob);

        if (objectp(me = killer)
           || objectp(me = query_last_damage_from()))
        {
                // 如果為自己的獵物，則獎勵之
                if (query("owner", ob) == query("id", me)
                   && query("combat_exp", me) <= 500000)
                {
                        // 根據獵物設定的參數來給予獎勵
                        power = query("power", ob);

                        if (power < 5)
                                power = 5;

                        if (power > 500)
                                power = 500;

                        GIFT_D->delay_bonus(me, ([ "prompt" : "通過這次獵取" + ob->name() +
                                                              HIG "的經歷",
                                                   "exp"    : random(power) + power,
                                                   "pot"    : random(power / 3) + power / 3,
                                                   "score"  : random(power / 4), ]));
                }
                skill = me->query_skill("hunting", 1);

                // 獲得物品
                if (query("item1") && random(skill) > 10)
                {
                        item = new(query("item1"));
                        item->move(me, 1);

                        msg = HIC "你仔細翻尋" + ob->name() +
                              HIC "的屍體，從上面割下了一" +
                              query("base_unit", item) +
                              item->name() + HIC;

                        // 一定幾率獲得高級物品
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