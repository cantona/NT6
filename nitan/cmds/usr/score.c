// This program is a part of NT MudLIB

#include <ansi.h>
#include <combat.h>
#include <net/dns.h>
#include <mudlib.h>

inherit F_CLEAN_UP;
string bar_string = "■■■■■■■■■■■■";
string blank_string = "□□□□□□□□□□□□";
string blank_string3 = "□□□□□□□□□□□□";
string blank_string2 = "　　　　　　　　　　　　";

mapping oprank = ([
        "宗師"     : HIW "★★★★★",
        "登峰造極" : HIY "★★★★☆",
        "超凡脫俗" : HIY "★★★★  ",
        "臻至化境" : HIR "★★★☆  ",
        "爐火純青" : HIR "★★★    ",
        "已有大成" : HIC "★★☆    ",
        "非同凡響" : HIC "★★      ",
        "出類拔萃" : HIG "★☆      ",
        "身手不凡" : HIG "★        ",
        "已有小成" : HIM "☆        ",
]);

string display_attr(int gift, int value);
string status_color(int current, int max);
string tribar_graph(int val, int eff, int max, string color);
string tribar_graph2(int val, int eff, int max, string color);
string tribar_graph3(int a);
void create() { seteuid(ROOT_UID); }

int main(object me, string arg)
{
        object ob;
        mapping my,mci;
        string line , skill_type;
        object weapon;
        int jings, qis, j, i, x, cnt;
        int attack_points, dodge_points, parry_points;
        string jbd, msg;
        int can_score = 0;
        int age, month;
        string startroom = "";
        object the_room = 0;
        int len = 0;

        seteuid(getuid(me));

        if( !arg ) ob = me;
        else ob = present(arg, environment(me));

        if( !ob ) ob = find_player(arg);
        if( !ob ) ob = find_living(arg);
        if( !ob || !me->visible(ob) ) return notify_fail("你要察看誰的狀態？\n");

        if( wizardp(me) || ob == me )
                can_score = 1;
        else
        if( ob->is_pet() && query("owner", ob) == query("id", me) )
                can_score = 1;
        else
        if( query("couple/child_id", me) == query("id", ob) )
                can_score = 1;
        else
        if( stringp(startroom=query("startroom", ob)) && 
            objectp(the_room = load_object(startroom)) &&
            query("room_owner_id", the_room) == query("id", me) )
                can_score = 1;
        if( !can_score )
                return notify_fail("只有巫師能察看別人的狀態。\n");

        my = ob->query_entire_dbase();
        mci = my["combat"];
        if( !mci) mci = ([ ]);

        if( playerp(ob) && (!stringp(my["born"]) || !my["born"]) )
                return notify_fail("還沒有出生吶，察看什麼？\n");

        jings = (my["eff_jing"] * 12 / my["max_jing"]) * 2;
        qis = (my["eff_qi"] * 12 / my["max_qi"]) * 2;
        // line = sprintf("                          【" + MUD_NAME + "】個人檔案                      \n\n", ob->query("language"),);
        line = sprintf( BOLD "\n%s" NOR "%s\n", RANK_D->query_rank(ob), ob->short(1) );
        // ob->update_age();

        line += sprintf( YEL "□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□\n" NOR );

        if( playerp(ob) ) {
                age=query("age", ob);
                month=query("mud_age", ob);
/*
                if( age >= 60 ) {
                        month -= (age - 60) * 86400 * 4;
                        month = (month - 118 * 86400) / 7200 / 4 + 1;
                } else
                if( age >= 30 ) {
                        month -= (age - 30) * 86400 * 3;
                        month = (month - 28 * 86400) / 7200 / 3 + 1;
                } else
                if( age >= 18 ) {
                        month -= (age - 18) * 86400 * 2;
                        month = (month - 4 * 86400) / 7200 / 2 + 1;
                } else {
*/              {
                        month -= (age - 11) * 525600;
                        month = month / 43800 + 1;
                }

                // not show invalid month
                if( month > 12 || month < 1 )
                        month = 1;

                line += sprintf( YEL "□" HIY "【年齡】" NOR "%-24s  " YEL "  □" NOR ,
                        chinese_number(age) + "歲" +
                        chinese_number(month) + "個月");
        } else
                line += sprintf( YEL "□" HIY "【年齡】" NOR "%-24s  " YEL "  □" NOR ,
                        chinese_number(query("age", ob))+"歲"+
                        chinese_number((query("mud_age", ob)-(query("age", ob)-14)*86400)/7200+1)+"個月");

        if( objectp(weapon=query_temp("weapon", ob))){
                skill_type=query("skill_type", weapon);
                attack_points = COMBAT_D->skill_power(ob, skill_type, SKILL_USAGE_ATTACK);
        } else {
                mapping prepare;
                string *sk;

                prepare = me->query_skill_prepare();
                if( !prepare ) prepare = ([]);
                sk = keys(prepare);

                if( sizeof(sk) == 0 ) skill_type = "unarmed";
                else skill_type = sk[0];
                attack_points = COMBAT_D->skill_power(ob, skill_type, SKILL_USAGE_ATTACK);
                if( sizeof(prepare) == 2 ) {
                        mixed temp;
                        temp = COMBAT_D->skill_power(ob, sk[1], SKILL_USAGE_ATTACK);

                        if( attack_points < temp)
                                attack_points = temp;
                }
        }

        parry_points = COMBAT_D->skill_power(ob, "parry", SKILL_USAGE_DEFENSE);
        dodge_points = COMBAT_D->skill_power(ob, "dodge", SKILL_USAGE_DEFENSE);

        line += sprintf( HIW "【戰鬥攻擊力】" NOR "%12d" YEL "□\n" NOR ,
                attack_points + 1);

        line += sprintf( YEL "□" HIY "【性別】" NOR "%-26.8s" YEL "  □" NOR ,
                    query("gender", ob)+query("race", ob));

        line += sprintf( HIW "【戰鬥防御力】" NOR "%12d" YEL "□\n" NOR ,
                dodge_points + (weapon? parry_points: (parry_points/10)) + 1);

        line += sprintf( YEL "□" HIY "【性格】" NOR "%-28.28s" YEL "□" NOR ,
                query("character", ob)?query("character", ob):"還未確定");

        line += sprintf( HIW "【戰鬥傷害力】" NOR "%12d" YEL "□\n" NOR ,
                weapon?query_temp("apply/damage", ob )
                               :query_temp("apply/unarmed_damage", ob));

        line += sprintf( YEL "□" HIY "【生辰】" MAG "%-28.28s" NOR+YEL "□" NOR ,
                CHINESE_D->chinese_date(query("birthday", ob)));

        line += sprintf( HIW "【戰鬥保護力】" NOR "%12d" YEL "□\n" NOR ,
                query_temp("apply/armor", ob));

        line += sprintf( YEL "□                          □□□□□□□□□□□□□□□□□□□□\n" NOR,);

        line += sprintf( YEL "□" HIG "【門派】" NOR "%-18.8s" YEL "□" NOR,
                ob->query_family()?ob->query_family():"普通百姓" );

        line += sprintf( HIY "【膂力】" HIW "%2d |%4d  " HIY "【悟性】" HIW "%2d |%4d" NOR+YEL "  □\n" NOR ,
                query("str", ob),
                ob->query_str(),
                query("int", ob),
                ob->query_int());

        line += sprintf( YEL "□" HIG "【師承】" NOR "%-18.18s" YEL "□" NOR,
                                ob->query_master()?ob->query_master():"你還沒有拜師" );

        line += sprintf( HIY "【根骨】" HIW "%2d |%4d  " HIY "【身法】" HIW "%2d |%4d" NOR+YEL "  □\n" NOR ,
                query("con", ob),
                ob->query_con(),
                query("dex", ob),
                ob->query_dex());

        line+=sprintf(YEL"□"HIW"【幫派】"NOR"%-18.18s",stringp(query("bunch/bunch_name", ob))?query("bunch/bunch_name", ob):"自由人士");
        line += sprintf( YEL "□" HIC "【拳腳】" NOR "%s" HIC "【兵器】" NOR "%s" NOR YEL "□\n" NOR,query("opinion/unarmed", ob)? oprank[query("opinion/unarmed", ob)]:CYN "無評價    " NOR,query("opinion/weapon", ob)? oprank[query("opinion/weapon", ob)]:CYN "無評價    " NOR);
        if( stringp(query("degree", ob)) )
        {
#ifndef LONELY_IMPROVED
                len=color_len(query("degree", ob));
#endif
                line+=sprintf(YEL"□"HIW"【職務】"NOR"%"+sprintf("%d",18+len)+"-s",query("degree", ob));
        }
        else
        if( stringp(query("bunch/title", ob)) )
                line+=sprintf(YEL"□"HIW"【職務】"NOR"%"+sprintf("%d",18+color_len(query("bunch/title", ob)))+"-s",query("bunch/title", ob));
        else
                line += sprintf( YEL "□" HIW "【職務】" NOR "無                " );
        line += sprintf( YEL "□" HIC "【內功】" NOR "%s" HIC "【輕功】" NOR "%s" NOR YEL "□\n" NOR,query("opinion/force",ob)? oprank[query("opinion/force",ob)]:CYN "無評價    " NOR,query("opinion/dodge",ob)? oprank[query("opinion/dodge",ob)]:CYN "無評價    " NOR);
        line+=sprintf(YEL"□"HIR"【軍功】"NOR"%-10s        ",query("jungong", ob)?query("jungong", ob)+" 策":"0 策");
        line += sprintf( YEL "□" HIY "【經驗】" HIW "%-10d" HIY "【潛能】" NOR "%s%-10d" NOR YEL "□\n" NOR ,my["combat_exp"],(int)query("potential",ob)>=(int)ob->query_potential_limit()?HIM:HIW,(int)query("potential",ob) - (int)query("learned_points",ob) );
        line+=sprintf(YEL"□"HIM"【職業】"NOR"%-18s"YEL"□"NOR,query("is_vendor", ob)?"商人":"無");
        line += sprintf( HIY "【%s】" HIW "%-10d" HIY "【體會】" HIW "%s%-10d" NOR YEL "□\n" NOR ,(query("shen",ob)>=0)?"正氣":"邪氣",query("shen",ob)?query("shen",ob):0,my["combat_exp"] < 100000 ? HIR :
                        my["experience"] < ob->query_experience_limit() ? HIW : HIM,
                        my["experience"] - my["learned_experience"] );
        line+=sprintf(YEL"□"HIC"【元神】"NOR"%-18.8s",query("yuanshen_level", ob)?query("yuanshen_level", ob)+" 級":"無");
        line += sprintf( YEL "□" HIY "【功績】" HIW "%-10d" HIY "【靈惠】" NOR HIW "%-10d" NOR YEL "□\n" NOR , query("family/gongji",ob) ,my["magic_points"] - my["magic_learned"] );
        if( !query("private_room", ob) )
                line += sprintf( YEL "□" HIW "【住宅】" NOR "%-18.8s" , "流浪街頭");
        else
                line+=sprintf(YEL"□"HIW"【住宅】"NOR"%-18.8s",query("private_room/name", ob));
        line += sprintf( YEL "□" HIY "【威望】" HIW "%-10d" HIY "【閱歷】" NOR HIW "%-10d" NOR YEL "□\n" NOR , query("weiwang",ob) ,query("score",ob) );
        /*
        if( mapp(my["couple"]))
        {
                line += sprintf( YEL "□" HIW "【婚姻】" NOR "%-18.8s" , "結婚" + chinese_number(my["couple"]["married"]) + "次");
                line+=sprintf(YEL"□"HIY"【閱歷】"NORHIW"%-10d"NORHIY"【戾氣】"NORHIW"%-10d"NORYEL"□\n"NOR,query("score", ob)?query("score", ob):0,query("total_hatred", ob)?query("total_hatred", ob):0);
                if( my["couple"]["have_couple"])
                {
                        line += sprintf( YEL "□" HIW "【%s】" NOR "%-18.8s" YEL "□□□□□□□□□□□□□□□□□□□□\n" NOR , my["couple"]["couple_gender"],my["couple"]["couple_name"] + "(" + my["couple"]["couple_id"]  + ")");
                } else
                {
                        line += sprintf( YEL "□" HIW "【伴侶】" NOR "%-18.8s" YEL "□□□□□□□□□□□□□□□□□□□□\n" NOR , "沒有");
                }
                line += sprintf( YEL "□" HIW "【子女】" NOR "%-56s" NOR YEL "□\n", mapp(my["couple"]["child"]) ? my["couple"]["child"]["name"] : "沒有");
        }
        */
        if( mapp(my["couple"]))
        {
                line += sprintf( YEL "□" HIW "【婚姻】" NOR "%-18.8s" , my["couple"]["couple_name"] ? "結婚" : "離異");
                line += sprintf( YEL "□" HIR "【榮譽】" NOR HIW "%-10d" NOR HIR "【戾氣】"NOR HIW "%-10d" NOR YEL "□\n" NOR ,query("honors",ob)?query("honors",ob):0,query("total_hatred",ob)?query("total_hatred",ob):0 );
                if( my["couple"]["couple_name"])
                {
                        line += sprintf( YEL "□" HIW "【%s】" NOR "%-18s" YEL "□□□□□□□□□□□□□□□□□□□□\n" NOR , "伴侶",my["couple"]["couple_name"] + "(" + my["couple"]["couple_id"]  + ")");
                } else
                {
                        line += sprintf( YEL "□" HIW "【伴侶】" NOR "%-18.8s" YEL "□□□□□□□□□□□□□□□□□□□□\n" NOR , "沒有");
                }
                line += sprintf( YEL "□" HIW "【子女】" NOR "%-56s" NOR YEL "□\n", my["couple"]["child_name"] ? my["couple"]["child_name"] : "沒有");
        }
        else
        {
                line += sprintf( YEL "□" HIW "【婚姻】" NOR "單身              " );
                line += sprintf( YEL "□" HIR "【榮譽】" NOR HIW "%-10d" NOR HIR "【戾氣】"NOR HIW "%-10d" NOR YEL "□\n" NOR ,query("honors",ob)?query("honors",ob):0,query("total_hatred",ob)?query("total_hatred",ob):0 );
                line += sprintf( YEL "□" HIW "【伴侶】" NOR "沒有              " YEL "□□□□□□□□□□□□□□□□□□□□\n" NOR );
                line += sprintf( YEL "□" HIW "【子女】" NOR "%-56s" NOR YEL "□\n", "沒有" );
        }

        if( my["gender"] == "無性")
                line += sprintf( YEL "□" HIW "【兩性】" NOR "%-56s" NOR YEL "□\n","你是個太監。" );
        else if( !query("sex/times", ob) )
        {
                if( my["gender"] == "女性")
                        line += sprintf( YEL "□" HIW "【兩性】" NOR "%-56s" NOR YEL "□\n","你還是處女。" );
                else
                        line += sprintf( YEL "□" HIW "【兩性】" NOR "%-56s" NOR YEL "□\n","你還是童男。" );
        } else
        {
                string *ks;
                ks=keys(query("sex", ob));
                ks -= ({ "times", "first", "" });
                if( sizeof(ks) >= 5)
                        line += sprintf( YEL "□" HIW "【兩性】" NOR "%-56s" NOR YEL "□\n",
                                         "你曾經和數不清的人發生過關系，連自己都忘了有誰。");
                else
                {
                        msg = "你曾經和" + implode(ks,"、") + "發生過關系。";
#ifndef LONELY_IMPROVED
                        len = color_len(msg);
#endif
                        line += sprintf( YEL "□" HIW "【兩性】" NOR "%" + sprintf("%d", (56 + len)) + "-s" NOR YEL "□\n",
                                         "你曾經和" + implode(ks,"、") + "發生過關系。");
                }
        }

        line += sprintf( YEL "□" HIW "【坐騎】" NOR "%-56s" NOR YEL "□\n", mapp(query("can_whistle",ob)) ? "擁有" : "沒有");

        if( !query("balance", ob) )
                line += sprintf( YEL "□" HIY "【錢莊】" HIY "沒有積蓄                                                " NOR+YEL "□\n" NOR );
        else
        {
                line += sprintf ( YEL "□"  HIY "【錢莊】" NOR );
                line += sprintf (HIY"%-56.56s"NOR,
                MONEY_D->money_str(query("balance", ob)));
                line += sprintf ( NOR+YEL "□\n" NOR );
        }
        line += sprintf( YEL "□                                                                □\n" NOR );

        if( my["max_jing"] >= my["eff_jing"])
                line += sprintf( YEL "□" HIC" 精  "NOR"：%-24s   ", tribar_graph(my["jing"], my["eff_jing"], my["max_jing"], status_color(my["jing"], my["max_jing"])) + tribar_graph3(jings));
        else
                line += sprintf( YEL "□" HIC" 精  "NOR"：%-24s   " , tribar_graph2(my["jing"], my["max_jing"], my["max_jing"], status_color(my["jing"], my["max_jing"]))+ tribar_graph3(jings));

        if( my["max_jingli"] > 0 )
                line += sprintf( HIC "精力"NOR"：%-24s"+ NOR+YEL+"□\n"NOR, tribar_graph(my["jingli"], my["max_jingli"], my["max_jingli"], status_color(my["jingli"], my["max_jingli"])));
        else
                line += sprintf( HIC "精力"NOR "：" HIG "%-24s"+ NOR+YEL+"□\n"NOR, blank_string );

        if( my["max_qi"] >= my["eff_qi"])
                line += sprintf( YEL "□" HIC" 氣  "NOR"：%-24s   ", tribar_graph(my["qi"], my["eff_qi"], my["max_qi"], status_color(my["qi"], my["max_qi"])) + tribar_graph3(qis));
        else
                line += sprintf( YEL "□" HIC" 氣  "NOR"：%-24s   ", tribar_graph2(my["qi"], my["max_qi"], my["max_qi"], status_color(my["qi"], my["max_qi"])) + tribar_graph3(qis));

        if( my["max_neili"] > 0 )
                line += sprintf( HIC "內力"NOR"：%-24s"+ NOR+YEL+"□\n"NOR, tribar_graph(my["neili"], my["max_neili"], my["max_neili"], status_color(my["neili"], my["max_neili"])));
        else
                line += sprintf( HIC "內力"NOR "：" HIG "%-24s"+ NOR+YEL+"□\n"NOR, blank_string );

        if( ob->max_food_capacity() > 0 )
                line += sprintf( YEL "□" HIC" 食物"NOR"：%-24s   ", tribar_graph(my["food"], ob->max_food_capacity(), ob->max_food_capacity(), YEL));
        else
                line += sprintf( YEL "□" HIC" 食物"NOR"："YEL   "%-24s"+ NOR+YEL+"□\n"NOR, blank_string );

        if( ob->max_water_capacity() > 0 )
                line += sprintf( HIC "飲水"NOR"：%-24s"+ NOR+YEL+"□\n"NOR , tribar_graph(my["water"], ob->max_water_capacity(), ob->max_water_capacity(), CYN));
        else
                line += sprintf( HIC "飲水"NOR CYN"：%-24s"+ NOR+YEL+"□\n"NOR, blank_string );

        line += sprintf( YEL "□                                                                □\n" NOR );
        line += sprintf( YEL "□" NOR HIY " 武學宗師： %s" NOR HIY "    大小周天： %s" NOR HIY "   元嬰出世： %s" NOR HIY "    生死玄關：%s " NOR YEL "□\n" NOR,
                ultrap(ob)?"○":HIC"×",query("breakup", ob)?"○":HIC"×",query("animaout", ob)?"○":HIC"×",query("death", ob)?"○":HIC"×");

        line += sprintf( YEL "□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□\n" NOR );

        line += sprintf( YEL "□" HIB "【殺生次數】" NOR HIR"%6d位"NOR,
                (int)mci["MKS"] + (int)mci["PKS"]);
        line += sprintf( YEL "□" HIB "【殺死玩家】" NOR HIR"%6d位"NOR,
                (int)mci["PKS"]);
        line += sprintf( YEL "□" HIB "【有意殺害】" NOR HIR"%6d位"NOR,
                (int)mci["WPK"]);
        line += YEL "□\n" NOR;

        line += sprintf( YEL "□" HIB "【擊暈玩家】" NOR HIR"%6d位"NOR,
                (int)mci["DPS"]);
        line += sprintf( YEL "□" HIB "【正派人士】" NOR HIR"%6d位"NOR,
                (int)mci["DPS_GOOD"]);
        line += sprintf( YEL "□" HIB "【邪派人士】" NOR HIR"%6d位"NOR,
                (int)mci["DPS_BAD"]);
        line += YEL "□\n" NOR;

        line += sprintf( YEL "□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□\n" NOR );

        line += sprintf( YEL "□" NOR HIB " 你目前的殺戮值是：%s%-45d"NOR YEL "□\n" NOR,
                         (query("pk_score", ob) >= 3)?HIM:(query("pk_score", ob) >= 1)?HIR:HIW,
                         query("pk_score", ob));

        msg = "";
        if( (int)mci["dietimes"])
                msg = sprintf(HIB " 你到目前為止總共到黑白無常那裡"
                                "串門%s次。" NOR,
                                chinese_number(mci["dietimes"]));
        if( msg != "")
        {
#ifndef LONELY_IMPROVED
                len = color_len(msg);
#endif
                line += sprintf( YEL "□" NOR "%" + sprintf("%d",(64 + len)) + "-s" NOR YEL "□\n" NOR, msg );
        }

        msg = "";
        if( stringp(mci["last_die"]))
                        msg += sprintf(HIB " 你最後一次是%s。" NOR,
                                        mci["last_die"]);
        if( msg != "")
        {
#ifndef LONELY_IMPROVED
                len = color_len(msg);
#endif
                line += sprintf( YEL "□" NOR "%" + sprintf("%d",(64 + len)) + "-s" NOR YEL "□\n" NOR, msg );
        }
        line += YEL "□□□□□□□□□□□□□□□□□□□□□□□□□□【個人檔案】□□\n" NOR;

        line += sprintf( WHT " □%s在" HIG + CHINESE_MUD_NAME + NOR "裡的遊戲時間是:" HIY "%s \n\n" NOR,
                         ob == me ? "你" : ob->name(1), time_period((int)query("online_time",ob)) );
        write(line);
        return 1;
}


string display_attr(int gift, int value)
{
        if( value > gift ) return sprintf( HIY "%6s" NOR, chinese_number(value) );
        else if( value < gift ) return sprintf( CYN "%6s" NOR, chinese_number(value) );
        else return sprintf("%6s", chinese_number(value));
}

string status_color(int current, int max)
{
        int percent;

        if( max ) percent = current * 100 / max;
        else percent = 100;

        if( percent > 100 ) return HIC;
        if( percent >= 90 ) return HIG;
        if( percent >= 60 ) return HIY;
        if( percent >= 30 ) return YEL;
        if( percent >= 10 ) return HIR;
        return HIB;
}

string tribar_graph(int val, int eff, int max, string color)
{
        return color + bar_string[0..(val*12/max)*2-1]
                + ((eff > val) ? blank_string[(val*12/max)*2..(eff*12/max)*2-1] : "") + NOR;
}
string tribar_graph2(int val, int eff, int max, string color)
{
        return color + bar_string[0..(val*12/max)*2-1]
                + ((eff > val) ? blank_string2[(val*12/max)*2..(eff*12/max)*2-1] : "") + NOR;
}
string tribar_graph3(int a)
{
        return BLU + blank_string3[0..(23-a)] + NOR;
}
int help(object me)
{
        write(@HELP
指令格式 : score
           score <對象名稱>                   (巫師專用)

這個指令可以顯示你(你)或指定對象(含怪物)的基本資料。
基本資料的設定請參閱 'help setup'。

see also : hp
HELP
    );
    return 1;
}
