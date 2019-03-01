#include <weapon.h>
#include <ansi.h>

inherit BLADE;

string do_wield();
string do_unwield();

void create()
{
        set_name(GRN "綠波香露刀" NOR, ({ "xianglu dao", "lvbo", "xianglu", "dao" }));
        set_weight(2500);
        if (clonep())
                destruct(this_object());
        else {
                set("long", GRN "一柄碧綠色的鬼頭刀，刀身散發出一陣腥臭，讓"
                            "人聞了幾欲作嘔。\n" NOR);
                set("unit", "把");
                set("value", 800000);
                set("no_sell", "什麼東西？好臭，好臭，快拿走！");
                set("material", "steel");
                set("wield_msg", (: do_wield :));
                set("unwield_msg", GRN "$N" GRN "抹了抹汗，將手中所握的綠波"
                            "香露刀收回。\n" NOR);
                set("stable", 100);
        }
        init_blade(80);
        setup();
}

string do_wield()
{
        object me = this_player();

        // 得授烏老大的碧煙刀法(biyan-dao)者不受刀身毒害。
        if (me->query_skill("biyan-dao") < 1 && me->query_skill("poison") < 120)
        {
                me->affect_by("lb_poison", ([
                        "level" : 150,
                        "id"    : "wu laoda",
                        "duration" : 5 + random(5)
                ]));
                remove_call_out("poison");
                call_out("poison", 6, me);
                return HIB "$N" HIB "抽出柄鬼頭刀，哪知剛握在手中，卻發現手掌已"
                       "然浮腫，磷光閃閃。\n\n" NOR;
        } else
        if (me->query_skill("biyan-dao") < 1 && me->query_skill("poison") > 180)
        {
                return GRN "$N" GRN "抽出柄鬼頭刀，哪知剛握在手中，卻發現手掌已"
                       "然浮腫，磷光閃閃。\n" HIY "幸好$N" HIY "精通毒理，瞬間已"
                       "將掌中所觸綠波劇毒驅之于無形。\n\n" NOR;
        } else
        if (me->query_skill("biyan-dao") < 1 && me->query_skill("poison") > 120)
        {
                me->affect_by("lb_poison", ([
                        "level" : 100,
                        "id"    : "wu laoda",
                        "duration" : 3 + random(3)
                ]));
                remove_call_out("poison");
                call_out("poison", 18, me);
                return HIB "$N" HIB "抽出柄鬼頭刀，哪知剛握在手中，卻發現手掌已"
                       "然浮腫，磷光閃閃。\n" HIC "幸好$N" HIC "知曉毒技，忙呼了"
                       "半天，好容易才化解了部分毒性。\n\n" NOR;
        } else
        {
                return GRN "$N" GRN "單手一抖，掌中已然多了柄綠光閃閃的鬼頭刀。\n" NOR;
        }
}

void poison(object me)
{
        object weapon;

        if( objectp(weapon=query_temp("weapon", me) )
            && query("id", weapon) == "xiangludao"
           && me->query_skill("poison") < 180)
        {
                message_vision(HIB "\n$N" HIB "右手不由得一顫，原來綠波香露刀刀"
                               "身劇毒已沁入肌膚。\n" NOR, me);
                me->affect_by("lb_poison", ([
                        "level" : 300,
                        "id"    : "wu laoda",
                        "duration" : 10 + random(10)
                ]));
                       remove_call_out("poison");
                       call_out("poison", 12, me);
        }
}

mixed hit_ob(object me, object victim, int damage_bonus)
{
        int n;
        int my_exp, ob_exp;

        if (me->query_skill("blade") < 150)
                return damage_bonus / 2;

        switch (random(10))
        {
        case 0:
                if (! victim->is_busy())
                victim->start_busy(me->query_skill("blade") / 10 + 2);
                return GRN "$N" GRN "綠波香露刀連連揮斬，化作一道道綠芒，$n"
                       GRN "只覺一股香氣撲鼻而來，不敢大意，當\n即凝神閉氣，"
                       "招架頓時散亂。\n" NOR;
        case 1:
                n = me->query_skill("blade");
                victim->affect_by("lb_poison", ([
                        "level":query("jiali", me)+random(query("jiali", me)),
                        "id":query("id", me),
                        "duration" : n / 70 + random(n / 30)
                ]));
                return GRN "$N" GRN "綠波香露刀連連揮斬，化作一道道綠芒，$n"
                       GRN "只覺一股香氣撲鼻而來，微一詫異，頓\n時已吸入數口"
                       "毒氣。\n" NOR;
        }
        return damage_bonus;
}
