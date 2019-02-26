// hp cmds (Mon  09-04-95)
// Update by Doing
// Update by Lonely

#include <ansi.h>
inherit F_CLEAN_UP;

string status_color(int current, int max);

int main(object me, string arg)
{
        object ob;
        mapping my;
        string sp;
        int craze;

        seteuid(getuid(me));

        if (arg && (arg == "-m"
           || sscanf(arg, "-m %s", arg)
           || sscanf(arg, "%s -m", arg)))
        {
                int ml, mn;
                mixed need;
                string combat_exp;
                int lv, level, exp;

                if (arg == "-m")
                        ob = me;
                else
                if( wizardp(me) || query("couple/child_id", me) )
                {
                        ob = present(arg, environment(me));

                        if (! ob || ! ob->is_character())
                                ob = find_player(arg);

                        if (! ob || ! ob->is_character())
                                ob = find_living(arg);

                        if (! ob || ! ob->is_character() || ! me->visible(ob))
                                return notify_fail("你要察看誰的狀態？\n");

                        if( !wizardp(me) && query("couple/child_id", me) != query("id", ob) )
                                return notify_fail("你要察看誰的狀態？\n");

                } else
                        return notify_fail("只有巫師能察看別人的狀態。\n");

                my = ob->query_entire_dbase();

                if (userp(ob) && (! stringp(my["born"]) || ! my["born"]))
                        return notify_fail("還沒有出生吶，察看什麼？\n");

                if (my["max_jing"] < 1 || my["max_qi"] < 1)
                        return notify_fail("無法察看" + ob->name(1) + "的狀態。\n");

                // 狂暴鐵拳增加加力上限
                if( query("special_skill/might", ob) )
                {
                        ml = (int)ob->query_skill("force") / 2;
                        ml += ml * 20 / 100; 
                }
                else
                        ml = (int)ob->query_skill("force") / 2;
                
                if( query("jingmai/finish", ob) )
                        ml += ZHOUTIAN_D->query_jingmai_effect("jiali");
                
                ml += query("jingmai/jiali", ob);
                       
                // 憤怒之心增加加怒上限
                if( query("special_skill/wrath", ob) )
                        mn = ob->query_max_craze() / 70;
                else
                        mn = ob->query_max_craze() / 100;

                exp=query("combat_exp", ob)/100;
                level = to_int(pow(to_float(exp), 1.0 / 3)) * 10 + 1;

                lv=query("level", ob);
                if (lv < 1) lv = 1;
                need=(lv+1)*(lv+1)*(lv+1)*10000-query("combat_exp", ob);

                if (need < 1) need = 1;

                sp = (ob == me ? "你" : ob->name()) + "目前的屬性上限如下：\n";
                sp += HIC "≡" HIY "───────────────────────"
                      "────────" HIC "≡\n" NOR;

                sp += sprintf(HIC "【精力上限】 " HIG " %-21d"
                              HIC "【內力上限】 " HIG " %d\n",
                      ob->query_current_jingli_limit(), ob->query_current_neili_limit());

                sp += sprintf(HIC "【潛能上限】 " HIG " %-21d"
                              HIC "【體會上限】 " HIG " %d\n",
                      ob->query_potential_limit()-query("learned_points", ob),
                      ob->query_experience_limit()-query("learned_experience", ob));

                sp += sprintf(HIC "【當前等級】 " NOR + WHT " %-21d"
                              HIC "【升級所需】 " NOR + WHT " %d\n", lv, need);

                sp += sprintf(HIC "【能力點數】 " NOR + WHT " %-21d"
                              HIC "【武功上限】 " NOR + WHT " %d\n",
                      query("ability", ob),level);

                if (mn > 0)
                        sp += sprintf(HIC "【最大加怒】 " NOR + WHT " %d\t\t   ", mn);
                else
                        sp += HIC "【最大加怒】 " NOR + WHT " ───\t\t   ";

                sp += sprintf(HIC "【最大加力】 " NOR + WHT " %d\n", ml);

#ifdef LONELY_IMPROVED
                sp += HIW "【死亡保護】  " NOR + sprintf("%-21s",
#else
                sp += HIW "【死亡保護】  " NOR + sprintf("%-37s",
#endif
                      (!query("combat/WPK", ob) && !query("no_newbie", ob) && (query("newbie", ob) || 
                      query("combat_exp", ob)<20000000))?HIY"保護中"NOR:
                      HIY "無保護" NOR);

                sp += HIW "【殺戮保護】  " NOR + sprintf("%s",
                      (query("die_protect/last_dead", me)+query("die_protect/duration", me)<time())?HIY"無保護\n"NOR:
                      HIY "保護中\n" NOR);

                sp += HIC "≡" HIY "───────────────────────"
                      "────────" HIC "≡\n" NOR;
                tell_object(me, sp);
                return 1;
        }

        if (arg && (arg == "-g"
           || sscanf(arg, "-g %s", arg)
           || sscanf(arg, "%s -g", arg)))
        {
                if (arg == "-g")
                        ob = me;
                else
                if( wizardp(me) || query("couple/child_id", me) )
                {
                        ob = present(arg, environment(me));

                        if (! ob || ! ob->is_character())
                                ob = find_player(arg);

                        if (! ob || ! ob->is_character())
                                ob = find_living(arg);

                        if (! ob || ! ob->is_character() || ! me->visible(ob))
                                return notify_fail("你要察看誰的狀態？\n");

                        if( !wizardp(me) && query("couple/child_id", me) != query("id", ob) )
                                return notify_fail("你要察看誰的狀態？\n");
                } else
                        return notify_fail("只有巫師能察看別人的狀態。\n");

                my = ob->query_entire_dbase();

                if (userp(ob) && (! stringp(my["born"]) || ! my["born"]))
                        return notify_fail("還沒有出生吶，察看什麼？\n");

                if (my["max_jing"] < 1 || my["max_qi"] < 1)
                        return notify_fail("無法察看" + ob->name(1) + "的狀態。\n");

                sp = (ob == me ? "你" : ob->name()) + "目前的天賦屬性如下：\n";
                sp += HIC "≡" HIY "───────────────────────"
                      "────────" HIC "≡\n" NOR;
                sp += HIY "【 種 類 】 " HIC "『初始』 『先天』 『成功』 『失敗』"
                      " 『故事』 『元神』\n" NOR;
                sp += HIC "≡" HIY "───────────────────────"
                      "────────" HIC "≡\n" NOR;

                sp += sprintf(HIW "【 膂 力 】 " NOR + WHT " [%3d]    ["
                      HIG "%3d" NOR + WHT "]    [" HIW "%3d" NOR + WHT "]    ["
                      HIR "%3d" NOR + WHT "]    [" HIM "%3d" NOR + WHT "]    ["
                      HIB "%3d" NOR + WHT "]\n",
                query("str", ob)-query("gift/str/succeed", ob)-query("gift/sun", ob),
                query("str", ob),
                query("gift/str/succeed", ob),
                query("gift/str/fail", ob),
                query("gift/sun", ob),
                query("tattoo/tattoo_str", ob));

                sp += sprintf(HIW "【 悟 性 】 " NOR + WHT " [%3d]    ["
                      HIG "%3d" NOR + WHT "]    [" HIW "%3d" NOR + WHT "]    ["
                      HIR "%3d" NOR + WHT "]    [" HIM "%3d" NOR + WHT "]    ["
                      HIB "%3d" NOR + WHT "]\n",
                query("int", ob)-query("gift/int/succeed", ob)-query("gift/water", ob),
                query("int", ob),
                query("gift/int/succeed", ob),
                query("gift/int/fail", ob),
                query("gift/water", ob),
                query("tattoo/tattoo_int", ob));

                sp += sprintf(HIW "【 根 骨 】 " NOR + WHT " [%3d]    ["
                      HIG "%3d" NOR + WHT "]    [" HIW "%3d" NOR + WHT "]    ["
                      HIR "%3d" NOR + WHT "]    [" HIM "%3d" NOR + WHT "]    ["
                      HIB "%3d" NOR + WHT "]\n",
                query("con", ob)-query("gift/con/succeed", ob)-query("gift/lighting", ob),
                query("con", ob),
                query("gift/con/succeed", ob),
                query("gift/con/fail", ob),
                query("gift/lighting", ob),
                query("tattoo/tattoo_con", ob));

                sp += sprintf(HIW "【 身 法 】 " NOR + WHT " [%3d]    ["
                      HIG "%3d" NOR + WHT "]    [" HIW "%3d" NOR + WHT "]    ["
                      HIR "%3d" NOR + WHT "]    [" HIM "%3d" NOR + WHT "]    ["
                      HIB "%3d" NOR + WHT "]\n",
                query("dex", ob)-query("gift/dex/succeed", ob)-query("gift/feng", ob),
                query("dex", ob),
                query("gift/dex/succeed", ob),
                query("gift/dex/fail", ob),
                query("gift/feng", ob),
                query("tattoo/tattoo_dex", ob));

                sp += sprintf(HIW "【 容 貌 】 " NOR + WHT " [%3d]    ["
                      HIG "%3d" NOR + WHT "]    [" HIW "%3d" NOR + WHT "]    ["
                      HIR "%3d" NOR + WHT "]    [" HIM "%3d" NOR + WHT "]    ["
                      HIB "%3d" NOR + WHT "]\n",
                query("per", ob)-query("gift/per/succeed", ob)-query("gift/pergive", ob),
                query("per", ob),
                query("gift/per/succeed", ob),
                query("gift/per/fail", ob),
                query("gift/pergive", ob),
                query("tattoo/tattoo_per", ob));

                sp += sprintf(HIW "【 福 緣 】 " NOR + WHT " [%3d]    ["
                      HIG "%3d" NOR + WHT "]    [" HIW "%3d" NOR + WHT "]    ["
                      HIR "%3d" NOR + WHT "]    [" HIM "%3d" NOR + WHT "]    ["
                      HIB "%3d" NOR + WHT "]\n",
                query("kar", ob)-query("gift/kar/succeed", ob)-query("gift/kargive", ob),
                query("kar", ob),
                query("gift/kar/succeed", ob),
                query("gift/kar/fail", ob),
                query("gift/kargive", ob),
                query("tattoo/tattoo_kar", ob));

                sp += HIC "≡" HIY "───────────────────────"
                      "────────" HIC "≡\n" NOR;
                tell_object(me, sp);
                return 1;
        }

        if (! arg)
                ob = me;
        else
        if( wizardp(me) || query("couple/child_id", me) || query("private_room", me) )
        {
                ob = present(arg, environment(me));
                if (! ob || (! ob->is_character() && ! ob->is_owner(me))) ob = find_player(arg);
                if (! ob || (! ob->is_character() && ! ob->is_owner(me))) ob = find_living(arg);
                if (! ob || (! ob->is_character() && ! ob->is_owner(me)) || ! me->visible(ob))
                        return notify_fail("你要察看誰的狀態？\n");

                if( !wizardp(me) && query("couple/child_id", me) != query("id", ob) && 
                    ! ob->is_owner(me))
                        return notify_fail("你要察看誰的狀態？\n");
        } else
                return notify_fail("只有巫師能察看別人的狀態。\n");

        my = ob->query_entire_dbase();

        if (userp(ob) && (! stringp(my["born"]) || ! my["born"]))
                return notify_fail("還沒有出生吶，察看什麼？\n");

        if (my["max_jing"] < 1 || my["max_qi"] < 1)
                return notify_fail("無法察看" + ob->name(1) + "的狀態。\n");

        sp = (ob == me ? "你" : ob->name()) + "目前的狀態屬性如下：\n";
        sp += HIC "≡" HIY "───────────────────────"
              "────────" HIC "≡\n" NOR;

        sp += sprintf(HIC "【 精 氣 】 %s%5d/ %5d %s(%3d%%)"
                      HIC "    【 精 力 】 %s%5d / %5d (+%d)\n",
                status_color(my["jing"], my["eff_jing"]), my["jing"], my["eff_jing"],
                status_color(my["eff_jing"], my["max_jing"]),
                             my["eff_jing"] * 100 / my["max_jing"],
                status_color(my["jingli"], my["max_jingli"]), my["jingli"],
                             my["max_jingli"], my["jiajing"] );

        sp += sprintf(HIC "【 氣 血 】 %s%5d/ %5d %s(%3d%%)"
                      HIC "    【 內 力 】 %s%5d / %5d (+%d)\n",
                status_color(my["qi"], my["eff_qi"]), my["qi"], my["eff_qi"],
                status_color(my["eff_qi"], my["max_qi"]),
                             my["eff_qi"] * 100 / my["max_qi"],
                status_color(my["neili"], my["max_neili"]), my["neili"],
                             my["max_neili"], my["jiali"] );

        sp += sprintf(HIW "【 食 物 】 %s%5d/ %5d      " HIW "     【 潛 能 】  %s%d\n",
                status_color(my["food"], ob->max_food_capacity()),
                my["food"], ob->max_food_capacity(),
                query("potential", ob) >= ob->query_potential_limit()?HIM:HIY,
                query("potential", ob)-query("learned_points", ob));

        sp += sprintf(HIW "【 飲 水 】 %s%5d/ %5d      " HIW "     【 體 會 】  %s%d\n",
                status_color(my["water"], ob->max_water_capacity()),
                my["water"], ob->max_water_capacity(),
                my["experience"] >= ob->query_experience_limit() ? HIM : HIY,
                my["experience"] - my["learned_experience"]);

        if (craze = me->query_craze())
        {
                if (me->is_most_craze())
                        sp += HIR "【 憤 " BLINK "怒" NOR HIR " 】  " +
                              sprintf("%-22s",query("character", me) == "光明磊落"?
                                               "豎發衝冠" : "怒火中燒");
                else
                        sp += sprintf(HIR "【 憤 怒 】 %5d/ %5d (+%-3d)    ",
                                      craze, me->query_max_craze(),
                                      query("jianu", me));
        } else
        {
                sp += HIC "【 平 和 】  ─────────    ";
        }
        sp += sprintf(HIW "【 經 驗 】  " HIC "%d\n", my["combat_exp"]);
        sp += HIC "≡" HIY "───────────────────────────────" HIC "≡\n" NOR;
        tell_object(me, sp);
        return 1;
}

string status_color(int current, int max)
{
        int percent;

        if (max > 0)
                percent = current * 100 / max;
        else
                percent = 100;

        if (percent > 100) return HIC;
        if (percent >= 90) return HIG;
        if (percent >= 60) return HIY;
        if (percent >= 30) return YEL;
        if (percent >= 10) return HIR;
        return RED;
}

int help(object me)
{
        write(@HELP
指令格式：hp [-m] [-g]
          hp [-m] [-g] <對象名稱>               （巫師專用）

這個指令可以顯示你或指定對象的精氣內力等數值。如果添加 -m 參
數則更詳細的列出各種數值的最大有效果值。如果添加 -g 參數則會
詳細的列出你的天賦屬性狀態。其中『原始』指你在投胎或轉世重生
後本身所具備的原始值。『先天』則是指該項先天屬性的總值，這項
屬性可以通過吃丹或是激發故事以獲得提升。而『成功』和『失敗』
是指你所吃增加先天屬性類仙丹的效果。『故事』是指你是否曾在遊
戲中通過某些故事提升過相應的先天屬性。最後的『轉世』則表示你
是否通過了轉世這個途徑來增加了後天屬性。

相關指令：score
HELP);
        return 1;
}
