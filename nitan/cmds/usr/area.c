// Copyright (C) 2005, by Lonely. All rights reserved.
// This software can not be used, copied, or modified
// in any form without the written permission from authors.

#include <ansi.h>

inherit F_CLEAN_UP;

int do_area_kaifa(object me, string arg);
int do_area_tisheng(object me, string arg);
int show_area_all(object me, string arg);

int sort_areas(string f1, string f2, mapping fame)
{
        if (fame[f2]["bunch_name"] != fame[f1]["bunch_name"])
                return strcmp(fame[f2]["bunch_name"], fame[f1]["bunch_name"]);

        return strcmp(fame[f2]["bunch_name"], fame[f1]["bunch_name"]);
}

void create() { seteuid(getuid()); }

int main(object me, string arg)
{
        object *obs;
        string fname;
        array args;

        if (! arg) arg = "all";
        args = explode(arg, " ");
        if (sizeof(args) > 1)
                arg = implode(args[1..<1], " ");
        else
                arg = 0;

        switch (args[0])
        {
        case "kaifa":
                return do_area_kaifa(me, arg);

        case "tisheng":
                return do_area_tisheng(me, arg);

        case "all":
                return show_area_all(me, arg);

        }

        write("無效的參數。\n");
        return 1;
}

mixed select_bunch(object me, string arg)
{
        string fam;
        object ob;

        if (! wizardp(me))
                // only wizard can show every league's list
                fam = 0;
        else
        if (stringp(arg) && arg != "")
        {
                if( !arrayp(query(arg+"/member", get_object(BUNCH_D))) )
                        fam = 0;
                else
                        fam = arg;

                if (! stringp(fam) && objectp(ob = UPDATE_D->global_find_player(arg)))
                {
                        // 沒有 arg 這個同盟，查看是否有該玩家
                        fam=query("bunch/bunch_name", ob);
                        UPDATE_D->global_destruct_player(ob);
                        if (! stringp(fam))
                                return notify_fail("這人現在沒有加入任何幫派。\n");
                }

                if (! stringp(fam))
                        return notify_fail("沒有這個玩家，不能查閱相關的同盟。\n");
        }

        if (! fam)
        {
                // select my league
                if( !stringp(fam=query("bunch/bunch_name", me)) )
                        return notify_fail("你現在還沒有加入任何幫派呢。\n");
        }

        return fam;
}

int do_area_kaifa(object me, string arg)
{
        string fam;
        array member;
        string area;
        string msg;
        mapping data;
        int j, kaifa, money;
        object npc;

        if( !stringp(fam=query("bunch/bunch_name", me)) )
                return notify_fail("你沒有加入任何幫會，無法開發幫會所屬地盤。\n");

        if (! arrayp(member = BUNCH_D->query_bunch_areas(fam)))
        {
                write("現在幫派" + fam + "沒有任何地盤。\n");
                return 1;
        }

        member -= ({ 0 });

        if (sizeof(member) < 1)
                return notify_fail(fam + "現在沒有任何地盤。\n");

        if (! wizardp(me))
        {
                if( query("jing", me)<50 )
                        return notify_fail("你現在精神不濟，無法打聽這些消息。\n");

                if (me->is_busy())
                        return notify_fail("你現在正忙，沒有時間打聽這些消息。\n");

                me->receive_damage("jing", 50);
                me->start_busy(3);
        }

        if (! arg)
        {
                msg = sprintf(HIC "\n%-18s%-28s%-8s%-8s%-18s\n" NOR,
                                "地盤名稱", "駐守幫眾", "開發度", "忠誠度", "上月收入");

                msg += HIY "───────────────────────────────────\n" NOR;

                j = 0;
                foreach (area in member)
                {
                        data = BUNCH_D->query_area_info(area, "dbase");

                        if (! mapp(data)) continue;

                        j++;
                        msg += sprintf(HIC "%-18s%-28s%-8s%-8s%-18s\n" NOR,
                                        data["area_name"],
                                        data["npc_name"] + "(" + data["npc_id"] + ")",
                                        data["kaifa"] + "%",
                                        data["zhongcheng"] + "%",
                                        data["last_money"] / 100 + " 兩");
                }

                if (j < 1)
                        return notify_fail(arg + "現在沒有任何地盤。\n");

                msg += "\n目前" + HIM + fam + NOR + "共有" + HIM + chinese_number(j) + NOR + "處地盤。\n";
                msg += HIY "───────────────────────────────────\n" NOR;

                write(msg);
                return 1;
        }

        area = base_name(environment(me));

        if (arg != environment(me)->short())
                return notify_fail("你必須到實地才能進行地盤開發！\n");

        if (BUNCH_D->query_area_info(area, "bunch_name") != fam)
                return notify_fail("這裡不屬于你的幫派地盤，你費什麼勁啊！\n");

        if (BUNCH_D->query_area_info(area, "npc_id"))
                npc = present(BUNCH_D->query_area_info(area, "npc_id"), environment(me));

        if (! objectp(npc))
                return notify_fail("負責" + arg + "地盤開發的ＮＰＣ並未就位，無法進行開發！\n");

        data = BUNCH_D->query_all_areas();
        kaifa = data[area]["kaifa"];

        if (kaifa >= 100)
                return notify_fail(arg + "的開發度已達到最大，不需再開發。\n");

        money = kaifa * 10000;

        if( query("balance", me)<money )
        {
                return notify_fail("你帳上的錢不夠，開發" + arg + "至少要" +
                                   MONEY_D->money_str(money) + "！\n");
        }

        addn("balance", -money, me);
        me->save();

        BUNCH_D->add_area_info(area, "kaifa", 1);

        write("你花費了" + MONEY_D->money_str(money) + "將地盤" + arg + "的開發度上升了一點！\n");
        return 1;
}

int do_area_tisheng(object me, string arg)
{
        string bunch;
        string someone;
        array member;
        mapping data;
        int amount;
        int money;
        object ob;
        string area;
        string msg;
        int j;

        if( !stringp(bunch=query("bunch/bunch_name", me)) )
                return notify_fail("你沒有參加任何幫會，無法提升任何ＮＰＣ。\n");

        if (! arrayp(member = BUNCH_D->query_bunch_areas(bunch)))
        {
                write("現在幫派" + bunch + "沒有任何地盤駐守幫眾，你想提升誰的忠誠度呢。\n");
                return 1;
        }

        member -= ({ 0 });

        if (sizeof(member) < 1)
                return notify_fail(bunch + "現在沒有任何地盤駐守幫眾，你想提升誰的忠誠度呢。\n");

        if (! wizardp(me))
        {
                if( query("jing", me)<50 )
                        return notify_fail("你現在精神不濟，無法打聽這些消息。\n");

                if (me->is_busy() || me->is_fighting())
                        return notify_fail("你現在正忙，沒有時間打聽這些消息。\n");

                me->receive_damage("jing", 50);
                me->start_busy(3);
        }

        if (! arg)
        {
                msg = sprintf(HIC "\n%-18s%-28s%-8s%-8s%-18s\n" NOR,
                                "地盤名稱", "駐守幫眾", "開發度", "忠誠度", "上月收入");

                msg += HIY "───────────────────────────────────\n" NOR;

                j = 0;
                foreach (area in member)
                {
                        data = BUNCH_D->query_area_info(area, "dbase");

                        if (! mapp(data)) continue;

                        j++;
                        msg += sprintf(HIC "%-18s%-28s%-8s%-8s%-18s\n" NOR,
                                        data["area_name"],
                                        data["npc_name"] + "(" + data["npc_id"] + ")",
                                        data["kaifa"] + "%",
                                        data["zhongcheng"] + "%",
                                        data["last_money"] / 100 + " 兩");
                }

                if (j < 1)
                        return notify_fail(arg + "現在沒有任何地盤駐守幫眾。\n");

                msg += "\n目前" + HIM + bunch + NOR + "共有" + HIM + chinese_number(j) + NOR + "處地盤駐守幫眾。\n";
                msg += HIY "───────────────────────────────────\n" NOR;

                write(msg);
                return 1;
        }

        if (sscanf(arg, "%d %s", amount, someone) != 2)
                return notify_fail("命令錯誤，請查看此命令。\n");

        if (amount < 0 || amount > 10)
                return notify_fail("每次提升的值不能小于零也不能大于十點。\n");

        if (! ob = present(someone, environment(me)))
                return notify_fail("這兒沒有這麼個人。\n");

        if (! ob->is_character())
                return notify_fail("看清楚，它不是生物。\n");

        if (userp(ob))
                return notify_fail("你只能提升本幫ＮＰＣ幫眾的技能。\n");

        if (! living(ob))
                return notify_fail("你得先把"+query("name", ob)+"弄醒再說。\n");

        if (ob->is_fighting() || ob->is_busy())
                return notify_fail(query("name", ob)+"正忙著呢。\n");

        if( bunch != query("bunch/bunch_name", ob) )
                return notify_fail("你只能提升本幫會內的ＮＰＣ幫眾。\n");

        if (! ob->is_bunch_npc())
                return notify_fail(query("name", ob)+"似乎現在不接受你的提升命令。\n");

        area = base_name(environment(ob));

        if (BUNCH_D->query_area_info(area, "bunch_name") != bunch ||
            BUNCH_D->query_area_info(area,"npc_id") != query("id", ob) )
                return notify_fail(query("name", ob)+"似乎現在不接受你的提升命令。\n");

        if ((int)BUNCH_D->query_area_info(area, "zhongcheng") >=
            query("bunch/max_zhongcheng", ob) )
                return notify_fail(query("name", ob)+"的忠誠度已經達到最大，不需要進行提升了。\n");

        money = amount * 10000;

        if( query("balance", me)<money )
                return notify_fail("你帳上的錢不夠，"+query("name", ob)+
                                   "的忠誠度每提升一點需要一兩黃金！\n");

        addn("balance", -money, me);
        me->save();

        if ((int)BUNCH_D->query_area_info(area, "zhongcheng") + amount >= 100)
        {
                BUNCH_D->set_area_info(area, "zhongcheng", 100);
                set("bunch/zhongcheng",query("bunch/max_zhongcheng",  ob), ob);
        } else
        {
                BUNCH_D->add_area_info(area, "zhongcheng", amount);
                addn("bunch/zhongcheng", amount, ob);
        }

        write("你花了"+money/10000+"兩黃金，將"+query("name", ob)+"的忠誠度提升了"+amount+"點！\n");

        return 1;
}

int show_area_all(object me, string arg)
{
        mapping all_areas;
        array areas;
        string  area, msg;
        mapping data;
        int     j;

        if (! mapp(all_areas = BUNCH_D->query_all_areas()))
        {
                write("現在泥潭沒有任何地盤可被幫派利用。\n");
                return 1;
        }

        areas = keys(all_areas);

        if (sizeof(areas) < 1)
                return notify_fail("泥潭現在沒有任何地盤可被幫派利用。\n");

        if (! wizardp(me))
        {
                if( query("jing", me)<50 )
                        return notify_fail("你現在精神不濟，無法打聽這些消息。\n");

                if (me->is_busy())
                        return notify_fail("你現在正忙，沒有時間打聽這些消息。\n");

                me->receive_damage("jing", 50);
                me->start_busy(3);
        }

        areas = sort_array(areas, (: sort_areas :), all_areas);
        msg = sprintf(HIC "\n%-18s%-28s%-14s%-10s\n" NOR,
                      "地盤名稱", "駐守幫眾", "所屬幫派", "資金(黃金)");

        msg += HIY "───────────────────────────────────\n" NOR;

        j = 0;
        foreach (area in areas)
        {
                data = BUNCH_D->query_area_info(area, "dbase");

                if (! mapp(data)) continue;

                j++;
                msg += sprintf(HIC "%-18s%-28s%-16s%6d\n" NOR,
                               data["area_name"],
                               data["npc_name"] + "(" + data["npc_id"] + ")",
                               stringp(data["bunch_name"]) ? data["bunch_name"] : "獨 立 中",
                               data["money"] / 10000);
        }

        if (j < 1)
                return notify_fail("現在泥潭沒有任何地盤可被幫派利用。\n");

        msg += "\n目前泥潭共有" + HIM + chinese_number(j) + NOR + "處地盤。\n";
        msg += HIY "───────────────────────────────────\n" NOR;

        write(msg);
        return 1;
}

int help(object me)
{
        write(@HELP
指令格式: area kaifa [地盤名] | tisheng [地盤幫眾ID] | all

查看目前你所在幫派地盤的各種信息，其中：

kaifa   ：開發幫會中地盤，增加幫會收入。
tisheng ：提升所屬幫會中駐守地盤NPC的忠誠度。
all     : 查看所有的地盤信息。

see also: bunch
HELP );
        return 1;
}
