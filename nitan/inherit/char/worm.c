// Inherit: worm.c 毒蟲
// Create by Vin for Heros.cn

#include <ansi.h>
inherit NPC;

int is_worm()
{
        return 1;
}

void setup()
{
        mapping p;

        p = query("worm_poison");
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
        if (! stringp(p["id"]))   p["id"]      = "nature worm";


        ::setup();
}

void init()
{
        object me, ob;

        ::init();
        if (! interactive(me = this_player()))
                return;

        if (present("xiong huang", this_player()) ||
            (int)me->query_skill("xiuluo-yinshagong", 1) >= 100)
                return;

        remove_call_out("kill_ob");
        call_out("kill_ob", 0, me);
}

mixed hit_ob(object me, object ob, int damage)
{
        mapping p;
        string  msg;
        int force;
        int dur;

        p = query("worm_poison", me);
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
                        msg = MAG "你覺得傷口有些發麻，連忙運功化解，但是一時"
                                  "體力不支，難以施為。\n" NOR;
                } else
                if (query("jing", ob) < 60)
                {
                        msg = MAG "你覺得傷口有些發麻，連忙運功化解，但是一時"
                                  "精神不濟，難以施為。\n" NOR;
                } else
                if (query("neili", ob) < damage / 5 + 50)
                {
                        msg = MAG "你覺得傷口有些發麻，連忙運功化解，但是一時"
                                  "內力不足，難以施為。\n" NOR;
                } else
                {
                        addn("neili", -damage/5, ob);
                        ob->receive_damage("qi", 20);
                        ob->receive_damage("jing", 10);
                        return HIM "你覺得被咬中的地方有些發麻，連忙運功化解"
                                   "毒性。\n" NOR;
                }
        }

        if (ob->affect_by("poison", ([ "level" : (int)p["level"],
                                       "name"  : "蟲毒",
                                       "id"    : "nature poison",
                                       "duration" : dur, ])))
        {
                msg += HIR "$n" HIR "臉色一變，只覺被咬中的地方一陣麻木。\n" NOR;
        }

        return msg;
}