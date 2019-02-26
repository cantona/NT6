// skills.c
// 增加巫師察看不在線玩家技能的功能。

#include <ansi.h>

inherit F_CLEAN_UP;

string *skill_level_desc = ({
        BLU"不堪一擊",BLU"毫不足慮",BLU"不足掛齒",BLU"初學乍練",BLU"勉勉強強",
        HIB"初窺門徑",HIB"初出茅廬",HIB"略知一二",HIB"普普通通",HIB"平平淡淡",
        CYN"平淡無奇",CYN"粗通皮毛",CYN"半生不熟",CYN"馬馬虎虎",CYN"略有小成",
        HIC"已有小成",HIC"鶴立雞羣",HIC"駕輕就熟",HIC"青出於藍",HIC"融會貫通",
        HIG"心領神會",HIG"爐火純青",HIG"瞭然於胸",HIG"略有大成",HIG"已有大成",
        YEL"豁然貫通",YEL"出類拔萃",YEL"無可匹敵",YEL"技冠羣雄",YEL"神乎其技",
        HIY"出神入化",HIY"非同凡響",HIY"傲視羣雄",HIY"登峯造極",HIY"無與倫比",
        RED"所向披靡",RED"一代宗師",RED"精深奧妙",RED"神功蓋世",RED"舉世無雙",
        WHT"驚世駭俗",WHT"撼天動地",WHT"震古鑠今",WHT"超凡入聖",WHT"威鎮寰宇",
        HIW"空前絕後",HIW"天人合一",MAG"深藏不露",HIM"深不可測",HIR"返璞歸真"
});

string *knowledge_level_desc = ({
        BLU"新學乍用",BLU"初窺門徑",HIB"略知一二",HIB"半生不熟",
        CYN"馬馬虎虎",CYN"已有小成",HIC"融會貫通",HIC"心領神會",
        GRN"瞭然於胸",GRN"豁然貫通",YEL"非同凡響",YEL"舉世無雙",
        HIY"震古鑠今",RED"無與倫比",WHT"超凡入聖",HIW"空前絕後",
});
// 基本武功和特殊武功查不出區別 暫時列表處理
string *all_basic= ({
        "force",
        "dodge",
        "unarmed",
        "leg",
        "cuff",
        "strike",
        "finger",
        "hand",
        "claw",
        "sword",
        "blade",
        "staff",
        "hammer",
        "club",
        "whip",
        "hook",
        "dagger",
        "throwing",
        "parry",
        "magic",
        "medical",
        "poison",
        "array",
        "chuixiao-jifa",
        "tanqin-jifa",
        "guzheng-jifa",
        "cooking",
});
string skill_level(string, int);

int main(object me, string arg)
{
        object ob;
        mapping skl, lrn, map;
        string *sname, *mapped, str, skill1;
        string msg_sk_know="",msg_sk_basic="",msg_sk_sp="",msg_sk_other="";
        string str_this;
        int num_know=0, num_basic=0, num_sp=0, num_other=0;
        int i, flag = 0, parents = 0;

        seteuid(getuid());

        if( !arg || arg == query("id", me) )
                ob = me;
        else
        {
                ob = present(arg, environment(me));
                if (!ob)
                {
                        if( sscanf(arg,"of %s",arg)!=1 )
                        if( sscanf(arg,"%s of %s",skill1,arg)!=2 )
                        if( sscanf(arg, "%s %s", arg, skill1)>2 )
                                return notify_fail("你要察看什麼？\n");

                        if (!ob) ob = present(arg, environment(me));
                        if (!ob) ob = find_player(arg);
                        if (!ob) ob = find_living(arg);
                        if (wizardp(me))
                        {
                                if (!ob)
                                {
                                        ob = new(USER_OB);
                                        seteuid(arg);
                                        export_uid(ob);
                                        flag = 1;
                                        if (!ob->restore())
                                        {
                                                destruct(ob);
                                                return notify_fail("沒有這個玩家。\n");
                                        }
                                }
                        }else
                        {
                                if (!ob || !me->visible(ob)) return notify_fail("你要察看誰的技能？\n");
                                        if( query("parents", ob) )
                                                if( member_array(query("id", me),query("parents", ob)) >= 0 )
                                                        parents = 1;
                                                else return notify_fail("只有爹孃能察看寶寶的技能。\n");
                        }
                }
        }

        if( ob!=me && !wizardp(me) && !ob->is_apprentice_of(me) && !ob->is_owner(me) &&
                !me->is_apprentice_of(ob) && parents != 1 && query("couple/couple_id", me) != query("id", ob) )
                return notify_fail("只有巫師或有師徒或親情關係的人能察看他人的技能。\n");

        skl = ob->query_skills();
        if (skill1 && !ob->query_skill(skill1))
        {
                write( (ob==me ? "你" : ob->name()) + "並沒有學會這項技能。\n");
                if (flag==1) destruct(ob);
                return 1;
        }
        if(!sizeof(skl))
        {
                write( (ob==me ? "你" : ob->name()) + "目前並沒有學會任何技能。\n");
                if (flag==1) destruct(ob);
                return 1;
        }
        sname = sort_array( keys(skl), (: strcmp :) );

        map = ob->query_skill_map();
        if( mapp(map) ) mapped = values(map);
        if( !mapped ) mapped = ({});

        lrn = ob->query_learned();
        if( !mapp(lrn) ) lrn = ([]);
        str = "\n";
//        str += HIC"≡"HIY"─────────────────────────────────"HIC"≡\n"NOR;
        if (!skill1)
        {
                str+=(ob==me ? "你" : ob->name()) +"目前共學過"+chinese_number(sizeof(skl))+"項技能：\n\n";
                for(i=0; i<sizeof(skl); i++)
                {
                        str_this=sprintf(NOR"│%s%s%-33s"NOR" - %-10s "NOR"%5d/%9d│"HIM"%s"NOR"\n",
                                (lrn[sname[i]] >= (skl[sname[i]]+1) * (skl[sname[i]]+1)) ? HIM : "",
                                (member_array(sname[i], mapped)==-1? "  ": "□"),
                                to_chinese(sname[i]) + " (" + sname[i] + ")",
                                skill_level(SKILL_D(sname[i])->type(), skl[sname[i]]),
                                skl[sname[i]], (int)lrn[sname[i]],
                                (wizardp(me) ? chinese_number((65-SKILL_D(sname[i])->learn_bonus()-SKILL_D(sname[i])->practice_bonus())/6) : "  "));
                        if(member_array(sname[i], all_basic)>-1)
                        {
                                msg_sk_basic+=str_this;
                                num_basic+=1;
                        }
                        else
                        switch (SKILL_D(sname[i])->type())
                         {
                                case "knowledge":
                                {
                                msg_sk_know+=str_this;
                                num_know+=1;
                                break;
                                }
                                case "martial":
                                {
                                msg_sk_sp+=str_this;
                                num_sp+=1;
                                break;
                                }
                                default:
                                {
                                msg_sk_other+=str_this;
                                num_other+=1;
                                }
                        }//end switch
        }//end for
                if (num_know>0)
                {
                        str+=sprintf(NOR"%s%|20s%s"NOR,
                        "┌──"+HIY,
                        chinese_number(num_know)+"項知識技能",
                        NOR+"────────────────────┐\n");
                        str+=msg_sk_know;
                        str+=NOR"└────────────────────────────────┘\n";
                }
                if (num_basic>0)
                {
                        str+=sprintf(NOR"%s%|20s%s"NOR,
                        "┌──"+HIY,
                        chinese_number(num_basic)+"項基本技能",
                        NOR+"────────────────────┐\n");
                        str+=msg_sk_basic;
                        str+=NOR"└────────────────────────────────┘\n";
                }
                if (num_sp>0)
                {
                        str+=sprintf(NOR"%s%|20s%s"NOR,
                        "┌──"+HIY,
                        chinese_number(num_sp)+"項特殊技能",
                        NOR+"────────────────────┐\n");
                        str+=msg_sk_sp;
                        str+=NOR"└────────────────────────────────┘\n";
                }
                if (num_other>0)
                {
                        str+=sprintf(NOR"%s%|20s%s"NOR,
                        "┌──"+HIY,
                        chinese_number(num_other)+"項其它技能",
                        NOR+"────────────────────┐\n");
                        str+=msg_sk_other;
                        str+=NOR"└────────────────────────────────┘\n";
                }


        }
        else
        {
                str+=(ob==me ? "你" : ob->name()) +"目前學習"+to_chinese(skill1)+"技能的情況如下：\n";
                        str+="┌────────────────────────────────┐\n";
                        str += sprintf(NOR"│%s%s%-33s"NOR" - %-10s "NOR"%3d/%9d│"HIM"%s"NOR"\n",
                        (lrn[skill1] >= (skl[skill1]+1) * (skl[skill1]+1)) ? HIM : "",
                        (member_array(skill1, mapped)==-1? "  ": "□"),
                        to_chinese(skill1) + " (" + skill1 + ")",
                        skill_level(SKILL_D(skill1)->type(), skl[skill1]),
                        skl[skill1], (int)lrn[skill1],
                        (wizardp(me) ? chinese_number((65-SKILL_D(skill1)->learn_bonus()-SKILL_D(skill1)->practice_bonus())/6) : ""));
                        str+=NOR"└────────────────────────────────┘\n";
        }
//        write("\n");
//        str += HIC"≡"HIY"─────────────────────────────────"HIC"≡\n"NOR;
        str += sprintf("%s", flag?"該玩家目前不在線上。\n":"");
        str = column_string(str, SKILLS_D->skill_mix_stats(ob), 80);
//        me->start_more(str);
        write(str);
        if (flag)
                destruct(ob);
        return 1;
}

string skill_level(string type, int level)
{
        int grade;


        switch(type)
        {
                case "knowledge":
                        grade = level / 200;
                        if( grade >= sizeof(knowledge_level_desc) )
                                grade = sizeof(knowledge_level_desc)-1;
                        return knowledge_level_desc[grade];
                default:
                        grade = level / 100;
                        if( grade < 0 ) grade = 0;
                        if( grade >= sizeof(skill_level_desc) )
                                grade = sizeof(skill_level_desc)-1;
                        return skill_level_desc[grade];
        }
}
// 寵物的技能。本命令不引用。在pet程序中引用。
string pet_skill(object ob)
{
        string desc;
        object *list, couple_ob;
        mapping skl, lrn, map;
        string *sname, *mapped,target,cardname;
        int i, marry_flag;

        seteuid(getuid());
        skl = ob->query_skills();
        if(!sizeof(skl)) {
                desc = ob->name() + "目前並沒有學會任何技能。\n";
                return desc;
        }
                desc = ob->name() +"目前所學過的技能：\n\n";
        sname = sort_array( keys(skl), (: strcmp :) );

        map = ob->query_skill_map();
        if( mapp(map) ) mapped = values(map);
        if( !mapped ) mapped = ({});

        lrn = ob->query_learned();
        if( !mapp(lrn) ) lrn = ([]);

        for(i=0; i<sizeof(skl); i++)
        {
                desc += sprintf("%s%s%-40s" NOR " - %-10s "NOR"%3d/%5d\n",
                        (lrn[sname[i]] >= (skl[sname[i]]+1) * (skl[sname[i]]+1)) ? HIM : "",
                        (member_array(sname[i], mapped)==-1? "  ": "＊"),
                        to_chinese(sname[i]) + " (" + sname[i] + ")",
                        skill_level(SKILL_D(sname[i])->type(), skl[sname[i]]),
                        skl[sname[i]], (int)lrn[sname[i]],);
        }
        return desc +"\n";
}

int help(object me)
{
        write(@HELP
指令格式 : skills|cha [<某人>] [<技能名>]
           skills|cha [<技能名>] of <某人>

    這個指令可以讓你查詢所學過的技能。

    你也可以指定一個和你有師徒關係的對象，用此命令可以查知對方
的技能狀況。

    巫師可以查詢任何人或 NPC 的技能狀況。

HELP
        );
        return 1;
}
