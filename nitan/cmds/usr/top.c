// This program is a part of NT MudLIB
// Written by Lonely@nitan.org

#include <ansi.h>
#include <mudlib.h>

inherit F_CLEAN_UP;

string help = @HELP
蹈堤跪笱齬俴埤ㄩ

top gaoshou             - 岍賜詢忒齬俴埤
top average             - 岍賜詢忒褶髡厒僅齬俴埤
HELP;

int top_list(object ob1,object ob2);
int get_score(object ob);
int top_average(object ob1, object ob2);
string *get_average(object ob);
int main(object me, string arg)
{

        object *list,*ob;
        int i, n;
        string msg;
        string arg1, arg2, arg3;
        string *res;

        if( time()-query_temp("last_top", me)<10 )
              return notify_fail("炵苀揚剟華抩耋ㄩ鞣鞣懂 ....\n");

        if( !wizardp(me) )
                set_temp("last_top", time(), me);

        if( !arg )
                return notify_fail(help);

        if( sscanf(arg, "%s %s %s", arg1, arg2, arg3) == 3 )
        {
                if( arg3 == "all" )
                        n = 200;
                else
                        n = to_int(arg3);
        }
        else if( sscanf(arg, "%s %s", arg1, arg2) == 2 )
        {
                if( arg2 == "all" )
                        n = 200;
                else if( to_int(arg2) )
                {
                        n = to_int(arg2);
                        arg2= 0;
                }
                else
                        n = 30;
        }
        else
        {
                n = 10;
                arg1 = arg;
        }

        if( n < 1 || n > 200 )
                return notify_fail("珆尨齬靡杅講祥腕苤衾 1 麼湮衾 200﹝\n");

        switch( arg1 )
        {
        case "average":
                if( !wizardp(me) ) return notify_fail("褶髡遼齬靡脤戙髡夔祥勤俙模羲溫﹝\n");
                msg = NOR YEL"岍賜"HIY" "+n+" 褶髡遼"NOR YEL"齬俴埤ㄩ\n"NOR;
                msg += NOR WHT"岸岸岸岸岸岸岸岸岸岸岸岸岸岸岸岸岸岸岸岸岸岸岸岸岸岸岸岸岸岸岸岸岸岸岸岸岸岸岸岸\n"NOR;
                msg += sprintf(HIW"%4s %-28s %-12s %12s %12s\n"NOR, "齬靡", "俙模", "冪桄", "夔", "极頗");
                msg += NOR WHT"岸岸岸岸岸岸岸岸岸岸岸岸岸岸岸岸岸岸岸岸岸岸岸岸岸岸岸岸岸岸岸岸岸岸岸岸岸岸岸岸\n"NOR;

                ob = filter_array(users(), (: playerp($1) && living($1) && !wizardp($1) :));
                list = sort_array(ob, (: top_average :));
                for (i = 0 ;i < n ; i++)
                {
                        if( i >= sizeof(list))
                                msg += sprintf("岫  %-5s 婃奀諾﹝﹛﹛﹛﹛﹛﹛﹛﹛﹛﹛﹛﹛﹛﹛﹛岫\n"NOR,chinese_number(i+1));
                        else {
                                res = query_temp("average", list[i]);
                                if( list[i] == me ) msg += BBLU HIY;
                                msg+=sprintf("岫%-5s%-22s%-12d%12d%12d岫\n"NOR,chinese_number(i+1),query("name", list[i])+"("+
                                                        capitalize(query("id", list[i]))+")",
                                                        res[0],
                                                        res[1],
                                                        res[2]);
                        }
                }
                msg += "弩岸岸岸拵呇﹜剿盄﹜阯蹺﹜餉譎歙祥輛齬靡埤岸岸岸彼\n";
                msg += "  " + NATURE_D->game_time() + "暮﹝\n";
                write(msg);
                break;
        case "gaoshou":
                ob = filter_array(users(), (: playerp($1) && living($1) && !wizardp($1) :));
                list = sort_array(ob, (: top_list :));
                msg = HIR "\n\t  ======== 虷偭蔬綬婓盄詢忒齬俴埤 ========\n" NOR;
                msg += HIR "\t  /                                      \\\n" NOR;   
                msg += sprintf(HIY "%-10s%-20s%-22s%-20s\n" NOR, "詢忒齬靡", "郬俷湮靡", "垀扽藷巖", "歎");
                msg += HIM "---------------------------------------------------------------\n"NOR;
                for (i = 0 ;i < n ; i++)
                {
                        if( i >= sizeof(list))
                                msg += sprintf(HIW"   %-7s 婃奀諾﹝﹛﹛﹛﹛﹛﹛﹛﹛﹛﹛﹛﹛﹛﹛﹛\n"NOR,chinese_number(i+1));
                        else {
                                if( list[i] == me ) msg += BBLU HIY;
                                msg+=sprintf(HIW"   %-7s%-20s%-22s%-20s\n"NOR,chinese_number(i+1),query("name", list[i])+"("+
                                                        capitalize(query("id", list[i]))+")",
                                                        query("family/family_name", list[i])?list[i]->query_family():"籵啃俷",
                                                        "祥晞芵繞");
                        }
                }
                msg += HIM "---------------------------------------------------------------\n"NOR;
                msg += HIR "\t  \\                                      /\n" NOR;
                msg += HIR "\t  ========================================\n" NOR;
                msg += HIC + NATURE_D->game_time() + "暮﹝\n" NOR;
                write(msg);
                break;
        default:
                write(help);
                break;
        }
        return 1;

}

int top_list(object ob1, object ob2)
{
        int score1,score2;

        score1 = get_score(ob1);
        score2 = get_score(ob2);

        return score2 - score1;
}

int get_score(object ob)
{
        int tlvl,i,score;
        string *ski;
        mapping skills;

        reset_eval_cost();

        skills = ob->query_skills();
        if (!sizeof(skills)) return 1;
        ski  = keys(skills);
        for(i = 0; i<sizeof(ski); i++) {
                tlvl += skills[ski[i]];
        }  // count total skill levels
        score = tlvl/1;
        score+=query("max_neili", ob)/1;
        score += ob->query_str() + ob->query_int() + ob->query_dex() + ob->query_con();
        score+=query("combat_exp", ob)/10+query("reborn/times", ob)*1000000000;

        return score;
}

int top_average(object ob1, object ob2)

{
        string *score1, *score2;

        score1 = get_average(ob1);
        score2 = get_average(ob2);

        return to_int(score2[0]) - to_int(score1[0]);
}

string *get_average(object ob)
{
        int dexp, dpot, dmar, dt;
        string *res;

        dexp = query("combat_exp", ob) - query("last_examine/combat_exp", ob);
        dpot = query("potential", ob) - query("last_examine/potential", ob);
        dmar = query("experience", ob) - query("last_examine/experience", ob);
        dt = time() - query("last_examine/time", ob);
        res = ({ dexp * 60 / dt, dpot * 60 / dt, dmar * 60 /dt });
        set_temp("average", res, ob);
        return res;
}

