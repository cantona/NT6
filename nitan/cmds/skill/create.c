// Copyright (C) 2005, by Lonely. All rights reserved.
// This software can not be used, copied, or modified 
// in any form without the written permission from authors.
// 需要玩家輸入主要為以下四個部分
// c_name(e_name) 絕招檔名和絕招名稱
// pfm_attack_msg 絕招發招描述
// pfm_succeed_msg 絕招打中描述
// pfm_fail_msg 絕招失誤描述

#include <ansi.h>
#include <command.h>
#define  SYN "\""
#define  SYC ".c"
#define  NEED_LVL   1600

#define  PERFORM_MODEL_LIAN  "/clone/meskill/perform_model_lian.h"
#define  PERFORM_MODEL_DAN   "/clone/meskill/perform_model_dan.h"
#define  PERFORM_MODEL_HUN   "/clone/meskill/perform_model_hun.h"

inherit F_CLEAN_UP;

mapping valid_types = ([
        "unarmed":      "拳腳",
        "sword":        "劍法",
        // "arrow":        "箭法",
        "axe":          "斧法",
        "blade":        "刀法",
        "staff":        "杖法",
        "hammer":       "錘法",
        "club" :        "棍法",
        // "dodge":        "輕功",
        "whip":         "鞭法",
        "finger":       "指法",
        "hand":         "手法",
        "cuff":         "拳法",
        "claw":         "爪法",
        "strike":       "掌法",
]);

string *weapon_types = ({
        "sword", "arrow", "axe",
        "blade", "staff", "hammer",
        "club", "whip" , "spin",
});

string *msga = ({ 
        "冥冥之中，$N突然發現",
        "$N絞盡腦汁，似乎覺得",
        "$N靈台一片清明，想起",
        "$N苦思以前練功時的點點滴滴，似乎想起",
        "突然，$N腦海靈光一現，發現",
        "$N反覆比劃，發現",
});

string *msgb = ({ 
        "似有相通之處，不禁心中一亮。",
        "頗有一一印證之功，隨手演練，似有所悟。",
        "似乎可以融合貫通，頓時心內一陣狂喜！",
        "可以相互取長補短，開闢一種全新的境界。",
        "如果連續使出，似乎可以將威力發揮至極限。",
        "如果詳加修正，可以相互彌補箇中不足，創造出更完美的絕招。"
});

string *banned_name = ({
        "你", "你", "我", "他", "她", "它",
        "爸", "爺", "　", "媽",
        "屎", "尿", "糞",
});

string get_skill_name(object me, string skill);

void get_perform_model(string arg, object me, string base_skill, string skill);
void get_perform_name(string arg, object me, string base_skill, string skill, string model);
void get_perform_msg1(object me, string base_skill, string skill, string model, string c_name, string e_name, string msg);
void get_perform_msg2(object me, string base_skill, string skill, string model, string c_name, string e_name, string pfm_attack_msg, string msg);
void get_perform_msg3(object me, string base_skill, string skill, string model, string c_name, string e_name, string pfm_attack_msg, string pfm_succeed_msg, string msg);
void decide_input_perform(string arg, object me, string base_skill, string skill, string model, string c_name, string e_name, string pfm_attack_msg, string pfm_succeed_msg, string pfm_fail_msg);
void finish_write_perform(object me, string base_skill, string skill, string model, string c_name, string e_name, string pfm_attack_msg, string pfm_succeed_msg, string pfm_fail_msg);

int main(object me, string arg)
{
        mapping creates;
        string  skill, perform, base_skill;
        string  *types, *performs, *skills;
        object  weapon, where;
        mapping skills_map;
        string  msg, dir, *mut_skills = ({});
        int     i, j;
        int     flag = 0;
        
        seteuid(getuid());
        where = environment(me);
        
        if (! wizardp(me) && ! MEMBER_D->is_valid_member(query("id", me))) 
                return notify_fail("只有會員才可以自創任何絕招。\n");

        if( !arg ) {
                if( !mapp(creates=query("create", me)) )
                        return notify_fail("你目前還沒有任何自創絕招。\n");
                        
                skills = keys(creates);   
 
                msg = WHT "你目前共自創的武功絕招情況如下：\n" NOR;               
                for( i = 0; i < sizeof(skills); i++ ) {  
                        msg += HIC "\n" + skills[i] + " ：";          
                        performs = keys(creates[skills[i]]);
                        for( j = 0; j < sizeof(performs); j++ ) {
                                msg += performs[j];
                                msg += (j == (sizeof(performs) -1) ? NOR :  WHT " - " HIC);
                        }
                }
                
                msg += "\n\n";
                tell_object(me, msg);

                return 1;
        }

        if( sscanf(arg, "%s %s d", skill, perform) == 2 ) {                        
                object ob;
                if( !query("create/"+skill, me) )
                        return notify_fail("沒有自創這種武功絕招，請確認輸入的武功英文名稱。\n");
                
                if( !query("create/"+skill+"/"+perform, me) )
                        return notify_fail("沒有自創這種武功絕招，請確認輸入的絕招英文名稱。\n");
                
                tell_object(me, HIR "你刪除了自創" + to_chinese(skill) + "絕招" + to_chinese(perform) + "(" + perform + ")。\n" NOR);                                                
                CHINESE_D->remove_translate(perform);                        
                dir = SKILL_D(skill);
                if (dir[strlen(dir) - 1] != '/')
                        dir += "/";              
                if (SKILL_D(skill)->valid_enable("force"))
                        dir += "perform/";                             
                if (ob = get_object(dir + perform + SYC))
                        destruct(ob);
                rm( dir + perform + SYC );                        
                delete("can_perform/"+skill+"/"+perform, me);
                delete("create/"+skill+"/"+perform, me);
                if( !mapp(query("create/"+skill, me)) || 
                        sizeof(query("create/"+skill, me))<1 )
                        delete("create/"+skill, me);
                        
                if( !mapp(query("create", me)) || 
                        sizeof(query("create", me))<1 )
                        delete("create", me);
                        return 1;
        }
                
        if( me->is_busy() )
                return notify_fail("你還是先忙完手頭的事再説吧！\n");         
    
        if( query("pigging", where) )
                return notify_fail("你還是專心拱豬吧！\n");
                
        if( !query("no_fight", where) )
                return notify_fail("在這裏閉關？不太安全吧？\n");

        if( !query("sleep_room", where) )
                return notify_fail("你得找一個能夠休息的地方閉關。\n");
                
        if( !ultrap(me) )
                return notify_fail("你還沒有到大宗師的境界，還是好好學習鍛鍊吧。\n");

        if( query("reborn/times", me)<1 )
                return notify_fail("你還沒有經過轉世，還是好好學習鍛鍊吧。\n");

        if( query("potential", me)-query("learned_points", me)<1000000 )
                return notify_fail("你的潛能不夠，沒法閉關修行。\n");

        if( query("qi", me)*100/query("max_qi", me)<90 )
                return notify_fail("你現在的氣太少了，無法靜心閉關。\n");

        if( query("jing", me)*100/query("max_jing", me)<90 )
                return notify_fail("你現在的精太少了，無法靜心閉關。\n");

        if( query("max_neili", me)<4000 )
                return notify_fail("你覺得內力頗有不足，看來目前還難以"
                                   "進行長時間的閉關修煉。\n");

        if( query("neili", me)*100/query("max_neili", me)<90 )
                return notify_fail("你現在的內力太少了，無法靜心閉關。\n");

        if( !mapp(skills_map = me->query_skills() ) || sizeof(skills_map) < 1 )
                return notify_fail("你還是先去學點功夫再來吧。\n");

        if( undefinedp(skills_map[arg]) || skills_map[arg] < 1 )
                return notify_fail("你連基本的" + to_chinese(arg) + "都不會，從何談起？\n");

        if( me->query_skill("martial-cognize", 1) < NEED_LVL )
                return notify_fail("你的武學修養的修為還不夠高深。\n");

        if( skills_map[arg] < NEED_LVL )
                return notify_fail("你的" + to_chinese(arg) + "的修為還不夠高深。\n");
                                
        if( SKILL_D(arg)->type() != "martial" )
                return notify_fail("你無法為這種武功創造絕招。\n");

        dir = SKILL_D(arg) + "/";

        // if( file_size(dir) != -2 )
        //        return notify_fail("你無法為這種武功創造絕招。\n");
                        
        /*
        if( SKILL_D(arg)->is_invent_skill() ) {
                if( query("jieti/times", me)<2 )
                        return notify_fail("你目前還無法為這種自創武功創造絕招。\n"); 
        }  
        */
 
        types = keys(valid_types);        
        for( i = 0; i < sizeof(types); i++ ) 
        {
                if( SKILL_D(arg)->valid_enable(types[i]) ) 
                        continue;
                        
                types[i] = 0;
        }
        
        types -= ({ 0 });
        
        // if( sizeof(types) != 1 )
        if( sizeof(types) < 1)
                return notify_fail("你目前還無法為這種自創武功創造絕招。\n"); 
               
        base_skill = types[0];
        skill = arg;
        
        if( objectp(weapon=query_temp("weapon", me))){
                if( member_array(base_skill, weapon_types) == -1 ) {
                        if (sizeof(types) == 1)
                                return notify_fail("你必須空手才能自創" + to_chinese(skill) + "的絕招。\n");
                        else {
                                for (i = 1; i < sizeof(types); i++) {
                                        base_skill = types[i];
                                        if( member_array(base_skill, weapon_types) != -1 ) {
                                                flag = 1; // 可拿兵器
                                                break;
                                        }
                                }
                                if( flag != 1 ) return notify_fail("你必須空手才能自創" + to_chinese(skill) + "的絕招。\n");
                        }
                }
                if( member_array(base_skill, weapon_types) != -1 ) {
                        if( query("skill_type", weapon) != base_skill){
                                if (sizeof(types) == 1)
                                        return notify_fail("你所使用的武器不對，無法自創" + to_chinese(skill) + "的絕招。\n");
                                else {
                                        for (i = 1; i < sizeof(types); i++) {
                                                base_skill = types[i];  
                                                if( query("skill_type", weapon) == base_skill){
                                                        flag = 2;
                                                        break;
                                                }
                                        }
                                        if( flag != 2 )
                                                return notify_fail("你所使用的武器不對，無法自創" + to_chinese(skill) + "的絕招。\n");
                                }
                        }
                }
                        
        } else 
        if( member_array(base_skill, weapon_types) != -1 ) {
                if (sizeof(types) == 1)
                        return notify_fail("你必須拿起武器才能開始自創" + to_chinese(skill) + "的絕招。\n");
                else {
                        for (i = 1; i < sizeof(types); i++) {
                                base_skill = types[i]; 
                                if( member_array(base_skill, weapon_types) == -1 ) {
                                        flag = 3;
                                        break;
                                }
                        }
                        if( flag != 3 ) return notify_fail("你必須拿起武器才能開始自創" + to_chinese(skill) + "的絕招。\n");
                }
        }                                

        skills = keys(skills_map);

        foreach( string sk_tmp in skills ) {
                if( SKILL_D(sk_tmp)->valid_enable(base_skill) ) {
                        mut_skills += ({ sk_tmp });
                }
        }

        if( sizeof(mut_skills) < 3 )
                return notify_fail("你的" + valid_types[base_skill] + "修為還不夠廣博，再去多學習學習！\n");

        mut_skills = filter_array(mut_skills, (: $(skills_map)[$1] >= NEED_LVL :));

        if( sizeof(mut_skills) < 3 )
                return notify_fail("你在" + valid_types[base_skill] + "方面的修為還不夠高深。\n");
        
        if( sizeof(query("create/"+skill, me)) >= 3 )
                return notify_fail("你的" + to_chinese(skill) + 
                                   "絕招數量已經到了極限，無法再自創新絕招。\n");
        delete_temp("create", me);
                                
                
        message_vision("$N盤膝坐下，開始苦思冥想，專心的自創" + to_chinese(skill) + "絕招。\n", me);              

        set_temp("create/skill", skill, me);
        set_temp("create/base_skill", base_skill, me);
        set_temp("create/mut_skills", mut_skills, me);
        
        me->set_short_desc("正在全神貫注地自創" + to_chinese(skill) + "絕招。");

        me->start_busy(bind((:call_other, __FILE__, "inventing" :), me),
                       bind((:call_other, __FILE__, "halt_inventing" :), me));

        CHANNEL_D->do_channel(this_object(), "rumor",
                              sprintf("%s(%s)開始閉關自創%s。\n",
                              me->name(1),query("id", me),to_chinese(skill)+"新絕招"));
        return 1;
}

int inventing(object me)
{
        int     max, i;
        string  pot;
        string  base_skill, skill, *mut_skills, *skills_tmp,
                msg = "", *msgs = ({});
        
        pot=query("potential", me);
        if( pot <= query("learned_points", me) )
        {
                tell_object(me, "你的潛能耗盡，卻一無所獲，失望地站了。\n");
                message_vision("$N睜開雙目，緩緩吐了一口氣，站了起來。\n", me);
                me->set_short_desc(0);
                return 0;
        }

        if( me->add("learned_points",5000+random(10000))>pot )
                set("learned_points", pot, me);

        if( random(5) != 0) return 1;

        skill=query_temp("create/skill", me);
        base_skill=query_temp("create/base_skill", me);
        mut_skills=query_temp("create/mut_skills", me);

        if( random(20000)<query("int", me)){
                string *chinese_skills = ({});

                foreach(string mut_skill in mut_skills) {
                        chinese_skills += ({ to_chinese(mut_skill)});
                }
                
                message_sort("猛然間$N腦中略過種種招式，融合" + 
                                sprintf( HIG"%s" NOR "以及" HIG "%s"NOR, 
                                implode(chinese_skills[0..sizeof(chinese_skills)-2], NOR "、" HIG), 
                                chinese_skills[sizeof(chinese_skills)-1])
                                + "這" + chinese_number(sizeof(mut_skills)) + "種武功之精髓為"
                                + to_chinese(skill) + "創出新的絕招\n", me);

                me->clear_written();
                me->set_short_desc(0);   
                delete_temp("create", me);
                tell_object(me, HIW "\n任何時候輸入 ~q 則可終止自創絕招。\n" NOR);
                tell_object(me, HIW "\n\n你正在為" + to_chinese(skill) + "自創新的絕招。\n" NOR
                                "你可以為這個絕招選擇創建以下類型\n\n" NOR);                
                tell_object(me, "\t1> 創建一個為連招的絕招\n");
                tell_object(me, "\t2> 創建一個為單招的絕招\n");
                tell_object(me, "\t3> 創建一個為混合招的絕招\n");                   
                tell_object(me, "\t3> 請重新選擇1-3：");       
                    
                input_to( (: get_perform_model :), me, base_skill, skill );
                return 0;
        }

        skills_tmp = copy(mut_skills);

        max = 2 + random(sizeof(mut_skills)-2);
        if ( max > 5 ) max = 5;

        if( max < sizeof(mut_skills) ) {
                for( i = max; i < sizeof(mut_skills); i++ ) {
                        skills_tmp -= ({ skills_tmp[random(sizeof(skills_tmp))] });
                }
        }

        foreach(string sk_tmp in skills_tmp) {
                msgs += ({ get_skill_name(me, sk_tmp) });
        }

        msg = msga[random(sizeof(msga))] + sprintf("%s" NOR "以及%s", 
              implode(msgs[0..sizeof(msgs)-2], NOR "、"), msgs[sizeof(msgs)-1])
              + NOR + msgb[random(sizeof(msgb))] + "\n"NOR;

        message_sort(msg, me);

        return 1;
}

int halt_inventing(object me)
{
        me->set_short_desc(0);
        delete_temp("create", me);
        tell_object(me, HIG "你中止了自創絕招。\n" NOR);
        message_vision(HIY "$N" HIY "起身站立，神情充滿了失望。\n\n" NOR, me);
        return 1;
}

string get_skill_name(object me, string skill)
{
        mapping actions;
        string  skill_name, action;
        int     a, b;

        if( !find_object(SKILL_D(skill)) && !load_object(SKILL_D(skill)) )
                return HIG + to_chinese(skill);

        if( !mapp(actions=SKILL_D(skill)->query_action(me,query_temp("weapon", me))) )
                return HIG + to_chinese(skill);

        if( !undefinedp(actions["skill_name"]) )
                return HIG + actions["skill_name"];

        if( undefinedp(actions["action"]) )
                return HIG + to_chinese(skill);

        action = actions["action"];

        if( strsrch(action, "「") != -1 && strsrch(action, "」") != -1 ) {
                a = strsrch(action, "「");
                b = strsrch(action, "」");
                skill_name = action[a..b+1];
                return HIG + to_chinese(skill) + NOR + (random(2)?"的一招"YEL:"中的"YEL) + skill_name + NOR;
        } else if( strsrch(action, "【") != -1 && strsrch(action, "】") != -1 ) {
                a = strsrch(action, "【");
                b = strsrch(action, "】");
                skill_name = action[a..b+1];
                return HIG + to_chinese(skill) + NOR + (random(2)?"的一招"YEL:"中的"YEL) + skill_name + NOR;
        } else if( strsrch(action, "“") != -1 && strsrch(action, "”") != -1 ) {
                a = strsrch(action, "“");
                b = strsrch(action, "”");
                skill_name = action[a..b+1];
                return HIG + to_chinese(skill) + NOR + (random(2)?"的一招"YEL:"中的"YEL) + skill_name + NOR;
        } else return HIG + to_chinese(skill);
}

void get_perform_model(string arg, object me, string base_skill, string skill)
{
        string model;
        int n;
        
        if( arg == "" || arg == "~q" )
        {
                tell_object(me, "你放棄了自創絕招。\n"); 
                return;
        }
                
        n = to_int(atoi(arg));
        if (n < 1 || n > 3)
        {
                tell_object(me, "對不起，您只能選擇1-3，按下回車直接選擇連照。\n\n");
                tell_object(me, "\t1> 創建一個為連招的絕招\n");
                tell_object(me, "\t2> 創建一個為單招的絕招\n");
                tell_object(me, "\t3> 創建一個為混合招的絕招\n");   
                tell_object(me, "\t3> 請重新選擇1-3：");       
                input_to((: get_perform_model :), me, base_skill, skill);
                return;
        }
        
         switch(n)
        {
        case 1:
                model = "連招型";
                break;
        case 2:
                model = "單招型";
                break;
        case 3:
                model = "混合招型";
                break;
        }

        tell_object(me, HIW "\n\n\n你正在為" + to_chinese(skill) + "自創出了" + model + "的絕招。\n" NOR
                        "你可以為這個絕招取一個名字\n\n"
                        HIY "格式：" HIC "<英文名> <中文名>\n\n" NOR
                        HIW "勿用騷擾性或不雅的名字，否則將會被刪除。\n" NOR
                        "請輸入：");
        input_to( (: get_perform_name :), me, base_skill, skill, model );
}

void get_perform_name(string arg, object me, string base_skill, string skill, string model)
{
        string  c_name, e_name, file;
        int     i;
                       
        if( arg == "" || arg == "~q" )
        {
                tell_object(me, "你放棄了自創絕招。\n"); 
                return;
        }

        if( sscanf(arg, "%s %s", arg, c_name) != 2 )
        {
                tell_object(me, "對不起，請用：<英文名> <中文名> 的格式輸入。\n請重新輸入：");
                input_to((: get_perform_name :), me, base_skill, skill, model);
                return;
        }
        
        if ((strlen(arg) < 3) || (strlen(arg) > 10))
        {
                tell_object(me, "對不起，英文名必須是 3 到 10 個英文字母。\n請重新輸入：");
                input_to((: get_perform_name :), me, base_skill, skill, model);
                return;
        }

        while (i--)
        {
                if (arg[i] < 'a' || arg[i] > 'z' )
                {
                        tell_object(me, "對不起，英文名只能用英文字母。\n請重新輸入：");
                        input_to((: get_perform_name :), me, base_skill, skill, model);
                        return;
                }
        }
        
        e_name = arg;

        file = SKILL_D(skill);
        if( file[strlen(file) - 1] != '/' )
                file += "/";               
        if( SKILL_D(skill)->valid_enable("force") )
                file += "perform/";                       
        file += e_name;
        if( file_size(file + SYC) > 0 || get_object(file) ) {
                        tell_object(me, "對不起，已經有("+ arg +")這種絕招文件存在。\n請重新輸入：");
                        input_to((: get_perform_name :), me, base_skill, skill, model);
                        return;
        }

#ifdef CONFIG_NON_UTF8
        if( c_name && query_temp("big5", me) )
                c_name = LANGUAGE_D->toGB(c_name);
#endif

        if( !is_chinese(c_name) ) {
                        tell_object(me, "對不起，請用【中文】做中文名。\n請重新輸入：");
                        input_to((: get_perform_name :), me, base_skill, skill, model);
                        return;
        }

        if (member_array(c_name, banned_name) % 2 == 0)
        {
                tell_object(me, "對不起，這種名稱會造成其他人的困擾。\n請重新輸入：");
                input_to((: get_perform_name :), me, base_skill, skill, model);
                return;
        }

        if( strlen(c_name) > 20 ) {
                tell_object(me, "對不起，您設置的中文名太長，請選一個精湛一點的名字。\n請重新輸入：");
                input_to((: get_perform_name :), me, base_skill, skill, model);
                return;
        }
        
        tell_object(me, HIW "\n\n\n您成功為" + to_chinese(skill) + "新絕招設置好絕招名" 
                        HIW + c_name + "(" + e_name + ")" HIW "。\n" NOR);
                        
        tell_object(me, HIC "\n注意問題: $N 代表你 $n 代表敵人 $w 代表你的武器 \n\n" NOR);
        tell_object(me, HIC "例如：(拳腳類) \n" NOR);
        tell_object(me, HIM "$N" HIM "一聲怒嚎，將戰神心經提運極至，雙拳頓時攜着雷霆萬鈞之勢猛貫向$n" HIM "。\n" NOR);
        tell_object(me, HIC "例如：(武器類)\n" NOR); 
        tell_object(me, HIM "$N" HIM "手中$w寒氣逼人，刀身撕裂空氣，片片雪花飄落，刀未至氣先及，$n" HIM "眉毛都蒙上了薄薄白霜！\n\n" NOR);
        tell_object(me, HIC "請輸入發招時描述：（長度不超過200個漢字）\n" NOR);                         
        me->edit(bind((: call_other, __FILE__, "get_perform_msg1", me, base_skill, skill, model, c_name, e_name :), me));
}

void get_perform_msg1(object me, string base_skill, string skill, string model, string c_name, string e_name, string msg)
{
        string pfm_attack_msg;
                        
        if( !stringp( msg ) || msg == "" ) {
                tell_object(me, "這套武功絕招不可以沒有絕招描述！\n");
                me->edit(bind((: call_other, __FILE__, "get_perform_msg1", me, base_skill, skill, model, c_name, e_name :), me));
                return;
        }
        else {
                if( strlen(msg) > 400 ) {
                        tell_object(me, "您設定的描述太長了，請設定一個精簡的描述。\n");
                        me->edit(bind((: call_other, __FILE__, "get_perform_msg1", me, base_skill, skill, model, c_name, e_name :), me));
                        return;
                }
        }

        msg = replace_string(msg, "\"", "");
        msg = replace_string(msg, "\n", "");
        msg = replace_string(msg, "$w", "武器");
        msg = replace_string(msg, "你", "$N");
        msg = filter_color(msg);
                     
        pfm_attack_msg = msg;
                              
        tell_object(me, HIC "\nOK\n" NOR); 
        tell_object(me, HIC "\n注意問題: $N 代表你 $n 代表敵人 $w 代表你的武器 \n\n" NOR);
        tell_object(me, HIC "例如：(拳腳類) \n" NOR);
        tell_object(me, HIM "結果$n" HIM "閃避不及，$N" HIM "的拳力掌勁頓時透體而入，口中鮮血狂噴，連退數步。\n" NOR);
        tell_object(me, HIC "例如：(武器類)\n" NOR); 
        tell_object(me, HIM "只見$n" HIM "一聲慘叫，胸口給劈開一個巨大的口子，鮮血洶湧噴出！\n\n" NOR);
        tell_object(me, HIC "請輸入絕招打中時描述：（長度不超過100個漢字）\n" NOR);    
        me->edit(bind((: call_other, __FILE__, "get_perform_msg2", me, base_skill, skill, model, c_name, e_name, pfm_attack_msg :), me));
}

void get_perform_msg2(object me, string base_skill, string skill, string model, string c_name, string e_name, string pfm_attack_msg, string msg)
{
        string pfm_succeed_msg;
        
        if( !stringp( msg ) || msg == "" ) {
                tell_object(me, "這套武功絕招不可以沒有絕招描述！\n");
                me->edit(bind((: call_other, __FILE__, "get_perform_msg2", me, base_skill, skill, model, c_name, e_name, pfm_attack_msg :), me));
                return;
        }
        else {
                if( strlen(msg) > 200 ) {
                        tell_object(me, "您設定的描述太長了，請設定一個精簡的描述。\n");
                        me->edit(bind((: call_other, __FILE__, "get_perform_msg2", me, base_skill, skill, model, c_name, e_name, pfm_attack_msg :), me));
                        return;
                }
        }
 
        msg = replace_string(msg, "\"", "");
        msg = replace_string(msg, "\n", "");
        msg = replace_string(msg, "$w", "武器");
        msg = replace_string(msg, "你", "$N");
        msg = filter_color(msg);
               
        pfm_succeed_msg = msg;
                              
        tell_object(me, HIC "\nOK\n" NOR);   
        tell_object(me, HIC "\n注意問題: $P 代表你 $p 代表敵人 $w 代表你的武器 \n" NOR);
        tell_object(me, HIC "例如：(拳腳類) \n" NOR);
        tell_object(me, HIM "可是$p" HIM "識破了$P" HIM "這一招，斜斜一躍避開。\n" NOR);
        tell_object(me, HIC "例如：(武器類)\n" NOR); 
        tell_object(me, HIM "$p" HIM "見勢不妙，抽身急退，險險避過$P" HIM "的這記殺招，塵土飛揚中，地上裂開了一道大口子！\n\n" NOR);        
        tell_object(me, HIC "請輸入絕招失誤時描述：（長度不超過100個漢字）\n" NOR);   
        me->edit(bind((: call_other, __FILE__, "get_perform_msg3", me, base_skill, skill, model, c_name, e_name, pfm_attack_msg, pfm_succeed_msg :), me));
}

void get_perform_msg3(object me, string base_skill, string skill, string model, string c_name, string e_name, string pfm_attack_msg, string pfm_succeed_msg, string msg)
{
        string pfm_fail_msg;
        
        if( !stringp( msg ) || msg == "" ) {
                tell_object(me, "這套武功絕招不可以沒有絕招描述！\n");
                me->edit(bind((: call_other, __FILE__, "get_perform_msg3", me, base_skill, skill, model, c_name, e_name, pfm_attack_msg, pfm_succeed_msg :), me));
                return;
        }
        else {
                if( strlen(msg) > 200 ) {
                        tell_object(me, "您設定的描述太長了，請設定一個精簡的描述。\n");
                        me->edit(bind((: call_other, __FILE__, "get_perform_msg3", me, base_skill, skill, model, c_name, e_name, pfm_attack_msg, pfm_succeed_msg :), me));
                        return;
                }
        }

        msg = replace_string(msg, "\"", "");
        msg = replace_string(msg, "\n", "");
        msg = replace_string(msg, "$w", "武器");
        msg = replace_string(msg, "你", "$N");
        msg = filter_color(msg);
                
        pfm_fail_msg = msg;                            
        
        tell_object(me, HIW "\n你成功的為" + to_chinese(skill) + "新創的絕招設置以下相關信息。\n\n" NOR
                        HIC "絕招類型：" NOR HIC + model + "\n" NOR
                        HIC "中文名稱：" NOR HIC + c_name + "\n" NOR
                        HIC "英文名稱：" NOR HIC + e_name + "\n" NOR
                        HIC "發招描述：" NOR HIC + pfm_attack_msg + "\n" NOR
                        HIC "打中描述：" NOR HIC + pfm_succeed_msg + "\n" NOR
                        HIC "失誤描述：" NOR HIC + pfm_fail_msg + "\n" NOR
                        HIW "你確定嗎？(Y/N)" NOR);
                                
        input_to( (: decide_input_perform :), me, base_skill, skill, model, c_name, e_name, pfm_attack_msg, pfm_succeed_msg, pfm_fail_msg );
}

void decide_input_perform(string arg, object me, string base_skill, string skill, string model, string c_name, 
                          string e_name, string pfm_attack_msg, string pfm_succeed_msg, string pfm_fail_msg)
{
        object ob;
        string dir;
                
        if( arg == "y" || arg == "Y" ) {
                if( objectp( ob = get_object(SKILL_D(skill) + "/" + e_name) ) ) {
                        tell_object(me, "BUG！請聯繫巫師！\n");
                        return;
                }
                finish_write_perform(me, base_skill, skill, model, c_name, e_name, pfm_attack_msg, pfm_succeed_msg, pfm_fail_msg);

                log_file("create", sprintf("%s(%s) create %s's perform %s(%s) (%s)\n",
                                           query("name", me),
                                           query("id", me),
                                           skill,
                                           c_name,
                                           e_name,
                                           ctime(time())));
                
                dir = SKILL_D(skill);
                if (dir[strlen(dir) - 1] != '/')
                        dir += "/";
                
                if (SKILL_D(skill)->valid_enable("force"))
                        dir += "perform/";
                
                if( get_object(dir + e_name) ) {
                        CHANNEL_D->do_channel(this_object(), "rumor",
                                           sprintf("%s(%s)將生平所學融合吸收，為" NOR HIW + "《" + to_chinese(skill) + "》" NOR
                                           HIM "創出新的絕招" NOR HIC + "《" + c_name + "》" NOR + HIM "。" , 
                                           me->name(1),query("id", me)));
                        
                        me->force_me("chat*admire2"+query("id", me));
                        
                        CHINESE_D->add_translate(e_name, c_name);                        
                                        
                        set("create/"+skill, 1, get_object(SKILLS_D));
                        set("create/"+skill+"/"+e_name, 1, me);
                        set("can_perform/"+skill+"/"+e_name, 1, me);
                        me->save();
                }

        } else {
                tell_object(me, HIW "\n\n\n你為" + to_chinese(skill) + "自創出了新的絕招。\n" NOR
                                "你可以重新選擇為這個絕招選擇創建以下類型\n\n" NOR);      
                tell_object(me, "\t1> 創建一個為連招的絕招\n");
                tell_object(me, "\t2> 創建一個為單招的絕招\n");
                tell_object(me, "\t3> 創建一個為混合招的絕招\n");   
                tell_object(me, "\t3> 請重新選擇1-3：");       
 
                input_to((: get_perform_model :), me, base_skill, skill);
        }                       
}

void finish_write_perform(object me, string base_skill, string skill, string model, string c_name, 
                          string e_name, string pfm_attack_msg, string pfm_succeed_msg, string pfm_fail_msg)
{
        string result, header1, header2;
        string dir;
        
        result  = "";
        header1 = "";
        header2 = "";
     
        header1 += "// This is player's own perform (Write by Lonely@nt2)\n";
        header1+="//Createby"+query("name", me)+"("+capitalize(geteuid(me))+")at"+ctime(time())+"\n";
        header1 += "// " + c_name + "(" + e_name + ")\n"; 

        if( model == "連招型" ) 
                header2 = read_file(PERFORM_MODEL_LIAN);
        else if( model == "單招型" )
                header2 = read_file(PERFORM_MODEL_DAN);
        else
                header2 = read_file(PERFORM_MODEL_HUN);          
 
        header2 = replace_string(header2, "<絕招名>", c_name);
        header2 = replace_string(header2, "<PFM發招描述>", pfm_attack_msg); 
        header2 = replace_string(header2, "<PFM打中描述>", pfm_succeed_msg); 
        header2 = replace_string(header2, "<PFM失誤描述>", pfm_fail_msg);
        header2 = replace_string(header2, "E_NAME", e_name);
        header2 = replace_string(header2, "BASE_SKILL", base_skill);
        header2 = replace_string(header2, "SKILL", skill);
        
        result = header1 + header2;
        
        dir = SKILL_D(skill);
        if (dir[strlen(dir) - 1] != '/')
                dir += "/";
                
        if (SKILL_D(skill)->valid_enable("force"))
                dir += "perform/";
                
        assure_file(dir); 
        write_file(dir + e_name + SYC, result, 1);
        write(HIC "絕招創建成功，以後請使用 " + HIY "perform " + e_name +  HIC " 使用該絕招。\n" NOR );
}

int help(object me)
{
        write(@HELP
                                         
指令格式: create                           查看自己自創武功絕招的情況
          create <武功名稱>                為該武功自創新的絕招
          create <武功名稱> <絕招名稱> d   刪除該武功的已創武功之絕招

HELP );
        return 1;
}
