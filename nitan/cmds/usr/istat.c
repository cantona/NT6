// This program is a part of NT MudLIB
// stats cmds

#include <ansi.h>
#include <mudlib.h>
#include <command.h>

inherit F_CLEAN_UP;

int jingmai_effect(object ob, string str)
{
        if( query("jingmai/finish", ob) )
                return ZHOUTIAN_D->query_jingmai_effect(str);
        else
                return query("jingmai/" + str, ob);
}               

int main(object me, string arg)
{
        object ob;
        string sp;

        seteuid(getuid(me));

        if( !wizardp(me) && time()-query_temp("last_stats", me)<5 )
                return notify_fail("系統氣喘噓地歎道：慢慢來 ....\n");

        set_temp("last_stats", time(), me);
        MYGIFT_D->check_mygift(me, "newbie_mygift/istat");
        if (arg && arg != "")
        {
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
        } else
                ob = me;

        sp = HIM + (ob == me ? "你" : ob->name(1)) + "目前的各附加屬性效果一覽\n" NOR;
        sp += HIC "≡" HIY "───────────────────────────────" HIC "≡\n" NOR;

        sp += sprintf(HIC "【臂力附加】" HIG " %9d / %-9d"
                      HIC "【悟性附加】" HIG " %9d / %d\n"
                      HIC "【根骨附加】" HIG " %9d / %-9d"
                      HIC "【身法附加】" HIG " %9d / %d\n",
                      jingmai_effect(ob, "str")+query_temp("apply/attribute", ob)+query_temp("apply/str", ob),1000,
                      jingmai_effect(ob, "int")+query_temp("apply/attribute", ob)+query_temp("apply/int", ob),1000,
                      jingmai_effect(ob, "con")+query_temp("apply/attribute", ob)+query_temp("apply/con", ob),1000,
                      jingmai_effect(ob, "dex")+query_temp("apply/attribute", ob)+query_temp("apply/dex", ob),1000);

        sp += sprintf(HIC "【潛能上限】" HIM " %9d / %-9d"
                      HIC "【體會上限】" HIM " %9d / %d\n"
                      HIC "【內力上限】" HIM " %9d / %-9d"
                      HIC "【精力上限】" HIM " %9d / %d\n"
                      HIC "【氣血上限】" HIM " %9d / %-9d"
                      HIC "【精氣上限】" HIM " %9d / %d\n",
                      jingmai_effect(ob, "pot")+query_temp("apply/max_potential", ob),10000000,
                      jingmai_effect(ob, "mar")+query_temp("apply/max_experience", ob),10000000,
                      jingmai_effect(ob, "neili")+query_temp("apply/max_neili", ob),1000000,
                      jingmai_effect(ob, "jingli")+query_temp("apply/max_jingli", ob),5000000,
                      jingmai_effect(ob, "qi")+query_temp("apply/max_qi", ob),1000000,
                      jingmai_effect(ob, "jing")+query_temp("apply/max_jing", ob),500000);

        sp += sprintf(HIC "【研究次數】" HIY " %9d / %-9d"
                      HIC "【研究效果】" HIY " %9s / %s\n"
                      HIC "【練習次數】" HIY " %9d / %-9d"
                      HIC "【練習效果】" HIY " %9s / %s\n"
                      HIC "【學習次數】" HIY " %9d / %-9d"
                      HIC "【學習效果】" HIY " %9s / %s\n"
                      HIC "【汲取消耗】" HIY " %9d / %-9d"
                      HIC "【汲取效果】" HIY " %9s / %s\n",
                      jingmai_effect(ob, "research_times")+query_temp("apply/research_times", ob),3000,
                      jingmai_effect(ob, "research_effect")+query_temp("apply/research_effect", ob)+"%","1500%",
                      jingmai_effect(ob, "practice_times")+query_temp("apply/practice_times", ob),3000,
                      jingmai_effect(ob, "practice_effect")+query_temp("apply/practice_effect", ob)+"%","1500%",
                      jingmai_effect(ob, "learn_times")+query_temp("apply/learn_times", ob),3000,
                      jingmai_effect(ob, "learn_effect")+query_temp("apply/learn_effect", ob)+"%","1500%",
                      jingmai_effect(ob, "derive_times")+query_temp("apply/derive_times", ob),3000,
                      jingmai_effect(ob, "derive_effect")+query_temp("apply/derive_effect", ob)+"%","1500%");

        sp += sprintf(WHT "【攻擊等級】" HIW " %9d / %-9d"
                      WHT "【防禦等級】" HIW " %9d / %d\n"
                      WHT "【躲閃等級】" HIW " %9d / %-9d"
                      WHT "【招架等級】" HIW " %9d / %d\n"
                      WHT "【絕招命中】" HIW " %9s / %-9s"
                      WHT "【絕招防禦】" HIW " %9s / %s\n"
                      WHT "【兵器傷害】" HIG " %9d / %-9d"
                      WHT "【空手傷害】" HIG " %9d / %d\n"
                      WHT "【絕招傷害】" HIG " %9s / %-9s"
                      WHT "【戰鬥保護】" HIG " %9d / %d\n"
                      WHT "【附加傷害】" HIG " %9d / %-9d"
                      WHT "【附加保護】" HIG " %9d / %d\n"
                      /*
                      WHT "【改造傷害】" HIG " %9d / %-9d"
                      WHT "【改造保護】" HIG " %9d / %d\n"
                      */
                      WHT "【無視招架】" HIY " %9s / %-9s"
                      WHT "【無視躲閃】" HIY " %9s / %s\n"
                      WHT "【無視攻擊】" HIY " %9s / %-9s"
                      WHT "【無視內功】" HIY " %9s / %s\n",
                      jingmai_effect(ob, "attack")+query_temp("apply/attack", ob),3000,
                      jingmai_effect(ob, "defense")+query_temp("apply/defense", ob),3000,
                      query_temp("apply/dodge", ob),3000,query_temp("apply/parry", ob),3000,
                      query_temp("apply/ap_power", ob)+"%","200%",query_temp("apply/dp_power", ob)+"%","200%",
                      jingmai_effect(ob, "damage")+query_temp("apply/damage", ob),200000,
                      jingmai_effect(ob, "damage")+query_temp("apply/unarmed_damage", ob),200000,
                      jingmai_effect(ob, "da_damage")+query_temp("apply/da_power", ob)+"%","200%",
                      jingmai_effect(ob, "armor")+query_temp("apply/armor", ob),200000,
                      query_temp("apply/damage1", ob),200000,query_temp("apply/armor1", ob),200000,
                      //query_temp("apply/damage2", ob),200000,query_temp("apply/armor2", ob),200000,
                      query_temp("apply/avoid_parry", ob)+"%","90%",query_temp("apply/avoid_dodge", ob)+"%","90%",
                      query_temp("apply/avoid_attack", ob)+"%","90%",query_temp("apply/avoid_force", ob)+"%","90%");

        sp += sprintf(RED "【毒 傷 害】" RED " %9s / %-9s"
                      RED "【抗    毒】" RED " %9s / %s\n"
                      RED "【金 傷 害】" RED " %9s / %-9s"
                      RED "【抗    金】" RED " %9s / %s\n"
                      RED "【木 傷 害】" RED " %9s / %-9s"
                      RED "【抗    木】" RED " %9s / %s\n"
                      RED "【水 傷 害】" RED " %9s / %-9s"
                      RED "【抗    水】" RED " %9s / %s\n"
                      RED "【火 傷 害】" RED " %9s / %-9s"
                      RED "【抗    火】" RED " %9s / %s\n"
                      RED "【土 傷 害】" RED " %9s / %-9s"
                      RED "【抗    土】" RED " %9s / %s\n",
                      query_temp("apply/add_poison", ob)+"%","90%",query_temp("apply/reduce_poison", ob)+"%","90%",
                      query_temp("apply/add_metal", ob)+"%","90%",query_temp("apply/avoid_metal", ob)+"%","90%",
                      query_temp("apply/add_wood", ob)+"%","90%",query_temp("apply/avoid_wood", ob)+"%","90%",
                      query_temp("apply/add_water", ob)+"%","90%",query_temp("apply/avoid_water", ob)+"%","90%",
                      query_temp("apply/add_fire", ob)+"%","90%",query_temp("apply/avoid_fire", ob)+"%","90%",
                      query_temp("apply/add_earth", ob)+"%","90%",query_temp("apply/avoid_earth", ob)+"%","90%");
                              
        sp += sprintf(HIB "【內力恢復】" HIB " %9d / %-9d"
                      HIB "【生命恢復】" HIB " %9d / %d\n"
                      HIB "【精氣恢復】" HIB " %9d / %-9d"
                      HIB "【傷轉內力】" HIB " %9s / %s\n"
                      HIB "【偷取內力】" HIB " %9s / %-9s"
                      HIB "【偷取生命】" HIB " %9s / %s\n"
                      HIB "【額外獎勵】" HIB " %9s / %-9s"
                      HIB "【額外經驗】" HIB " %9s / %s\n"
                      HIB "【額外潛能】" HIB " %9s / %-9s"
                      HIB "【額外體會】" HIB " %9s / %s\n"
                      HIB "【額外真氣】" HIB " %9s / %-9s"
                      HIB "【忽視忙亂】" HIB " %9s / %s\n",
                      query_temp("apply/ref_neili", ob),500,query_temp("apply/ref_qi", ob),200,
                      query_temp("apply/ref_jing", ob),200,query_temp("apply/qi_vs_neili", ob)+"%","90%",
                      query_temp("apply/suck_neili", ob)+"%","90%",query_temp("apply/suck_qi", ob)+"%","90%",
                      query_temp("apply/add_reward", ob)+"%","120%",query_temp("apply/add_exp", ob)+"%","210%",
                      query_temp("apply/add_pot", ob)+"%","210%",query_temp("apply/add_mar", ob)+"%","210%",
                      query_temp("apply/add_force", ob)+"%","210%",query_temp("apply/avoid_busy", ob)+"%","90%");
                      
        sp += sprintf(WHT "【尋 金 率】" HIM " %9s / %-9s"
                      WHT "【尋 寶 率】" HIM " %9s / %s\n"
                      WHT "【殺    戮】" CYN " %9s / %-9s"
                      WHT "【破    氣】" CYN " %9s / %s\n"
                      WHT "【雙倍傷害】" CYN " %9s / %-9s"
                      WHT "【破    甲】" CYN " %9s / %s\n"
                      WHT "【致    盲】" CYN " %9s / %-9s"
                      WHT "【忽視致盲】" CYN " %9s / %s\n"
                      WHT "【天魔附體】" CYN " %9s / %-9s"
                      WHT "【戰神附體】" CYN " %9s / %s\n",
                      query_temp("apply/gold_find", ob)+"%","100%",
                      jingmai_effect(ob, "magic_find")+query_temp("apply/magic_find", ob)+"%","300%",
                      query_temp("apply/slaughter", ob)+"%","90%",query_temp("apply/clear_force", ob)+"%","90%",
                      query_temp("apply/double_damage", ob)+"%","200%",query_temp("apply/through_armor", ob)+"%","90%",
                      query_temp("apply/add_blind", ob)+"%","90%",query_temp("apply/avoid_blind", ob)+"%","90%",
                      query_temp("apply/absorb_blood", ob)+"%","90%",query_temp("apply/full_self", ob)+"%","90%");
                      

        sp += sprintf(HIY "【冰    凍】" HIM " %9s / %-9s"
                      HIY "【忽視冰凍】" HIM " %9s / %s\n"
                      HIY "【眩    暈】" HIM " %9s / %-9s"
                      HIY "【忽視眩暈】" HIM " %9s / %s\n"
                      HIY "【遺    忘】" HIM " %9s / %-9s"
                      HIY "【忽視遺忘】" HIM " %9s / %s\n"
                      HIY "【忙    亂】" HIM " %9d / %-9d"
                      HIY "【化解忙亂】" HIM " %9d / %d\n"
                      HIY "【虛    弱】" HIM " %9s / %-9s"
                      HIY "【忽視虛弱】" HIM " %9s / %s\n"
                      HIY "【追加傷害】" HIM " %9s / %-9s"
                      HIY "【化解傷害】" HIM " %9s / %s\n"
                      HIY "【傷害反噬】" HIM " %9s / %-9s"
                      HIY "【浴血重生】" HIM " %9s / %s\n"                      
                      HIY "【必 殺 率】" HIM " %9s / %-9s"
                      HIY "【提升技能】" HIM " %9d / %d\n",
                      query_temp("apply/add_freeze", ob)+"%","90%",query_temp("apply/avoid_freeze", ob)+"%","90%",
                      query_temp("apply/add_dizziness", ob)+"%","90%",query_temp("apply/avoid_dizziness", ob)+"%","90%",                    
                      query_temp("apply/add_forget", ob)+"%","90%",query_temp("apply/avoid_forget", ob)+"%","90%",
                      query_temp("apply/add_busy", ob),90,query_temp("apply/reduce_busy", ob),90,
                      query_temp("apply/add_weak", ob)+"%","90%",query_temp("apply/avoid_weak", ob)+"%","90%",
                      query_temp("apply/add_damage", ob)+"%","200%",
                      jingmai_effect(ob, "reduce_damage")+query_temp("apply/reduce_damage", ob)+"%","90%",
                      query_temp("apply/counter_damage", ob)+"%","90%",query_temp("apply/avoid_die", ob)+"%","90%",
                      query_temp("apply/fatal_blow", ob)+"%","90%",query_temp("apply/add_skill", ob),3000);

        sp += HIC "≡" HIY "───────────────────────────────" HIC "≡\n" NOR;

        sp += sprintf(HIG + (ob == me ? "你" : ob->name()) + HIG "在%s裏已經歷練了 " NOR + HIC "%s\n" NOR,
                        LOCAL_MUD_NAME(), time_period(query("online_time", ob)));

        /*
        if (MEMBER_D->is_valid_member(ob))
                sp += sprintf(HIG + (ob == me ? "你" : ob->name()) + HIG "可用來離線練功時間還有 " NOR + HIY "無限制\n" NOR);
        else
        */
        {
                if( query("online_time", ob)/3<query("offline_time", ob) )
                        set("offline_time",query("online_time",  ob)/3, ob);
                sp += sprintf(HIG + (ob == me ? "你" : ob->name()) + HIG "可用來離線練功時間還有 " NOR + HIY "%s\n" NOR,
                              time_period(query("online_time", ob)/3-query("offline_time", ob)));
        }

        sp += sprintf(HIG + (ob == me ? "你" : ob->name()) + HIG "今天的雙倍經驗時間還餘 " NOR + HIW "%s\n" NOR,
                      time_period(query("time_reward/quest", ob)));
        sp += sprintf(HIG + (ob == me ? "你" : ob->name()) + HIG "今天的高效練功時間還餘 " NOR + HIM "%s\n" NOR,
                      time_period(query("time_reward/study", ob)));


        me->start_more(sp);
        return 1;
}
