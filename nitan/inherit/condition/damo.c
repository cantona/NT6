// Inherit: condiction:damo

#include <ansi.h>

mapping mixed_poison(mapping p1, mapping p2)
{
        mapping p;
        int r;

        if (! p1 && ! p2)
                return 0;

        p = allocate_mapping(4);

        // calculate the remain poison
        if (p1) r = (p1["remain"] ? p1["remain"] : (int)p1["level"] * (int)p1["duration"]);
        else    r = 0;

        if (p2) r += (p2["remain"] ? p2["remain"] : (int)p2["level"] * (int)p2["duration"]);

        if (! p2)
        {
                p["level"]  = p1["level"];
                p["id"]     = p1["id"];
                p["name"]   = p1["name"];
                p["remain"] = r;
                return p;
        }

        if (! p1)
        {
                p["level"]  = p2["level"];
                p["id"]     = p2["id"];
                p["name"]   = p2["name"];
                p["remain"] = r;
                return p;
        }

        // generate the new id
        if (! p1["id"]) p1["id"] = p2["id"]; else
        if (! p2["id"]) p2["id"] = p1["id"];

        if (! p1["id"] || p1["id"] != p2["id"])
                // poison made by two man mixed
                p["id"] = "...";
        else
                p["id"] = p1["id"];

        // compare & decide the new level
        p["level"] = p1["level"];
        if (p["level"] < p2["level"])
                p["level"] = p2["level"];

        p["name"] = p1["name"];

        // decide the remain of poison
        p["remain"] = r;

        return p;
}

int do_effect(object ob, string cnd, mapping p)
{
        mapping cnd_info;
        int d;

        if (! p || ! intp(p["level"]) || ! intp(p["duration"]) ||
            ! stringp(p["id"]))
                return 0;

        if (! stringp(p["name"])) p["name"] = this_object()->chinese_name();

        cnd_info = mixed_poison(ob->query_condition(cnd), p);
        ob->apply_condition(cnd, cnd_info);
        return 1;
}

int dispel(object me, object ob, mapping cnd)
{
        int need_lvl;
        int cost_neili;
        int power;
        int dis;
        string pos;

        if (! cnd || ! intp(cnd["level"]) || ! intp(cnd["remain"]) ||
            ! stringp(cnd["id"]))
                return 0;

        pos = cnd["name"];
        if (query("neili", me) < 200)
        {
                tell_object(me, "你內力不足，無法化解" + pos + "。\n");
                return -1;
        }

        need_lvl = cnd["level"] + 10;
        if (query("breakup", ob))
                need_lvl = need_lvl * 6 / 10;
        if (me != ob)
                need_lvl += need_lvl / 5;

        if (cnd["id"] == query("id", me))
                need_lvl = 50;

        if (need_lvl > me->query_skill("force"))
        {
                if (me == ob)
                {
                        tell_object(me, MAG "你運用內功化解" + pos +
                                    "，然而似乎沒有半點效果。\n" NOR);
                        me->start_busy(1);
                        return -1;
                } else
                {
                        tell_object(me, MAG "你運用內功幫助" + ob->name() +
                                    "化解" + pos + "，然而似乎沒有半點效果。"
                                    "\n" NOR);
                        tell_object(ob, MAG + me->name() + "將內力緩緩的輸"
                                    "入你的體力，你覺得一陣噁心，幾欲嘔吐。"
                                    "\n" NOR);
                        if (! me->is_busy())
                        me->start_busy(1);
                        if (! ob->is_busy())
                        ob->start_busy(1);
                        return -1;
                }
        }

        // 去異常能力
        power = me->query_skill("force") + me->query_skill("poison") / 2;
        if (me == ob)
        {
                if (cnd["id"] == query("id", me))
                {
                        tell_object(me, WHT "你運用內功，將" + pos +
                                    "完全化解。\n" NOR);
                        addn("neili", -100, me);
                        cnd["remain"] = 0;
                        me->start_busy(1);
                } else
                {
                        cost_neili = query("neili", me);
                        dis = query("neili", me) * power / (cnd["level"] + 1) / 2;
                        if (cnd["remain"] == -1)
                                cnd["remain"] = 10000;
                        if (dis >= cnd["remain"])
                        {
                                dis = cnd["remain"];
                                cost_neili = cnd["remain"] * 2 * (cnd["level"] + 1) /
                                             power;
                                tell_object(me, WHT "你運用內功，將" + pos +
                                            "完全化解。\n" NOR);
                        } else
                        {
                                tell_object(me, WHT "你運用內功，化解了一點" + pos +
                                            "。\n" NOR);
                        }
                        cnd["remain"] -= dis;
                        if (cnd["remain"] < 0)
                                cnd["remain"] = 0;
                        addn("neili", -cost_neili, me);
                        me->start_busy(2 + random(2));
                }
        } else
        {
                if (cnd["id"] == query("id", me))
                {
                        tell_object(me, WHT "你運用內功，幫助" + ob->name() +
                                    "將" + pos + "盡數化解。\n" NOR);
                        addn("neili", -150, me);
                        cnd["remain"] = 0;
                        me->start_busy(2);
                        ob->start_busy(1);
                } else
                {
                        cost_neili = query("neili", me);
                        dis = query("neili", me) * power / (cnd["level"] + 1) / 4;
                        if (cnd["remain"] == -1)
                                cnd["remain"] = 10000;
                        if (dis >= cnd["remain"])
                        {
                                dis = cnd["remain"];
                                cost_neili = cnd["remain"] * 4 * (cnd["level"] + 1) /
                                             power;
                                tell_object(me, WHT "你運用內功，幫助" + ob->name() +
                                            "將" + pos + "盡數化解。\n" NOR);
                        } else
                        {
                                tell_object(me, WHT "你運用內功，幫助" + ob->name() +
                                            "化解了一點" + pos + "。\n" NOR);
                        }
                        cnd["remain"] -= dis;
                        if (cnd["remain"] < 0)
                                cnd["remain"] = 0;
                        addn("neili", -cost_neili, me);
                        me->start_busy(4 + random(4));
                           if (! ob->is_busy())
                        ob->start_busy(2 + random(2));
                }
        }

        if ( cnd["remain"] == 0)
                ob->clear_condition(this_object()->name());

        return 1;
}

// die reason
string die_reason(string name)
{
        if (! name || name == "毒")
                return "毒發身亡了";
        else
                return name + HIM "發作身亡了";
}

int update_condition(object me, mapping cnd)
{
        int jd;
        int qd;
        int nd;
        int jw;
        int qw;

        if (! cnd) return 0;

        if (! intp(cnd["level"]) || ! intp(cnd["remain"] || ! stringp(cnd["id"])))
                return 0;

        jd = this_object()->jing_damage(me, cnd);
        qd = this_object()->qi_damage(me, cnd);
        nd = this_object()->neili_damage(me, cnd);

        if (! living(me) && (query("jing", me) < jd || query("qi", me) < qd))
        {
                set("die_reason", die_reason(cnd["name"]), me);
                message_vision(this_object()->die_msg_others(), me);
                me->die();
                return 1;
        }

        if (jd)
        {
                // receive damage of jing
                me->receive_damage("jing", jd);
                jw = jd / 2;
                if (jw > query("eff_jing", me))
                {
                        jw = query("eff_jing", me);
                        if (jw < 0) jw = 0;
                }
                me->receive_wound("jing",  jw);
        }

        if (qd)
        {
                // receive damage of qi
                me->receive_damage("qi", qd);
                if (qw > query("eff_qi", me))
                {
                        qw = query("eff_qi", me);
                        if (qw < 0) qw = 0;
                }
                me->receive_wound("qi",  qw);
        }

        if (nd)
        {
                // receive cost of neili
                if (query("neili", me) >= nd)
                        addn("neili", -nd, me);
                else
                        set("neili", 0, me);
        }

        if (cnd["level"] / 2 + random(cnd["level"]) < (int)me->query_skill("force"))
        {
                if (cnd["remain"] <= cnd["level"])
                {
                        message("vision", HIM + me->name() + "長長的籲"
                                "了一口氣，看起來神色好多了。\n" NOR,
                                environment(me), ({ me }));
                        tell_object(me, HIM "你覺得身上的" + cnd["name"] +
                                    HIM "漸漸的不發生作用了，不"
                                    "禁長長的吁了一口氣。\n" NOR);
                        return 0;
                }

                cnd["remain"] -= cnd["level"];
                me->apply_condition(this_object()->name(), cnd);
        }

        message("vision", replace_string(this_object()->update_msg_others(), "$N",
                          me->name()), environment(me), ({ me }));
        tell_object(me, replace_string(this_object()->update_msg_self(), "$?", cnd["name"]));

        return 1;
}