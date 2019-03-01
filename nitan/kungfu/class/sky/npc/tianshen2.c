// 通天老仙 掌管轉世
// Create By Rcwiz 09/2003

#include <ansi.h>

inherit NPC;

#define MEMBER_D   "/adm/daemons/memberd"

mixed start_thborn();

void create()
{
        set_name(HIY "炎黃天神" NOR, ({ "yanhuang tianshen", "yanhuang", "tianshen" }));
        set("long", HIY "    炎黃天神威風凜凜，在此恭候您多時了，你似乎不想打攪他，希望靜\n"
                        "靜地聽完一守曲子，。\n" NOR);

        set("gender", "男性");
        set("age", 9999);
        set("attitude", "friendly");
        set("shen_type", 1);
        set("str", 100);
        set("int", 100);
        set("con", 100);
        set("dex", 100);

        set("max_qi", 200000);
        set("max_jing", 50000);
        set("max_neili", 30000);
        set("neili", 30000);
        set("jiali", 200);
        set("combat_exp", 90000000);

        set_skill("dodge", 550);
        set_skill("parry",550);
        set_skill("unarmed", 550);
        set_skill("yinyang-shiertian", 550);
        set_skill("force", 550);
        set_skill("martial-cognize", 550);
        set_skill("literate", 550);

        map_skill("force", "yinyang-shiertian");
        map_skill("dodge", "yinyang-shiertian");
        map_skill("parry", "yinyang-shiertian");
        map_skill("unarmed", "yinyang-shiertian");
        
        set("inquiry", ([
                "超脫"   :   (: start_thborn :),
        ]));
        set("chat_chance_combat", 120);
        set("chat_msg_combat", ({
                (: exert_function, "powerup" :),
                (: exert_function, "shield" :),
        }) );
        setup();

        carry_object(__DIR__"obj/xianpao")->wear();
        carry_object(__DIR__"obj/tianlai-zhiyuan")->hand();
}

mixed start_thborn()
{
        object me = this_player();
        
        mapping job_special;
        string *key_job_special;
        int i, job_add, sk_12t_add, sk_bd_add, sk_lhj_add, total_lhd;
        mapping skills_status;
        string *myskills;
        
        string user, login;
        
        if (me->query("thborn/ok"))
        {
                if (! me->query("thborn/repeat")) // 有repeat標志可再次2轉
                        return "你不是已經二轉過了嗎，快快離開吧，不要打攪我的雅興！\n";
        }

        // 判斷負重，超過30%不能轉
        if ((int)me->query_encumbrance() * 100 / (int)me->query_max_encumbrance() > 30)
                return "為了你物品數據安全，負重不能超過30%，請清理一下背包再來吧！\n";

        // 數據已經清理完畢，職業如果已經選擇即可2轉
        if (me->query("check_yhjob"))
        {
                if (! me->query("yhjob/job"))
                        return "請選擇職業（指令：yhjob <職業>）後再來找我吧！\n";

                if (! me->query("thborn/ok")) // 非重新2轉才做提示和設置special
                {
                        CHANNEL_D->do_channel(this_object(), "rumor", HIY + me->name() + "(" + me->query("id") + ")" HIY "借助天神"
                                                                      "之力，超脫意識，完成了第二次轉生！\n" NOR);
                        tell_object(me, HIC "\n恭喜你二轉成功：你獲得了特殊技能「日月齊輝」！\n" NOR);
                        me->set("special_skill/riyue", 1);
                }
                
                me->set("thborn/ok", 1);
                
                command("say 後會有期，祝你好運！");
                me->move("/d/city/wumiao");
                me->delete("thborn/repeat"); // 刪除允許重新2轉標志
                me->set("thborn/times", time()); // 記錄2轉時間
                
               // 十周年活動期間，轉世成功獲得特殊獎勵
               me->add("combat_exp", 10000000);
               me->add("potential", 10000000);
               me->add("experience", 2000000);
               me->set_skill("force", 300);
               tell_object(me, HIG "恭喜，炎黃風雨十年活動期間，第二次轉世成功，你獲得了1000萬經驗和潛能，200萬武學修\n"
                               "養及300級基本內功獎勵！\n" NOR);
                       
                me->save();
                return 1;
        }
        else
        {
                // 備份數據
                user =  me->query("id");
                user = "/data/user/" + user[0..0] + "/" + user + ".o";
                login = "/data/login/" + user[0..0] + "/" + user + ".o";
                "/adm/daemons/scbornd"->beifen_thborn(me, user, login);
        }

        // 補償左右互博10點悟性
        if (! me->query("thborn/ok") && me->query("scborn/ok") && 
            me->query_skill("zuoyou-hubo", 1) >= 385 && ! me->query("buchang-hubo"))
        {
                log_file("buchang-hubo", me->query("id") + " " + ctime(time()) + " 獲得10點INT補償。\n");
                me->add("int", 10);
                me->set("buchang-hubo", 1);
                me->add("int", 10);
                tell_object(me, HIM "\n天道循環，陰陽平衡：你獲得了十點先天悟性的補償！\n");
                me->save();
        }
        
        if (! me->query("thborn/ok")) // 再次2轉不返回輪回點
        {
                // 清除LHD使用加成，單指先天悟性，因為技能和SPECIALJOB技能都要DELETE
                // 1、計算12T花費的LHD
                if (me->query_skill("yinyang-shiertian", 1))
                {
                        sk_12t_add += 5;
                        if (me->query("yinyang-shiertian/yinyang"))
                                sk_12t_add += 2;
                        if (me->query("yinyang-shiertian/qiankun"))
                                sk_12t_add += 3;
                        if (me->query("yinyang-shiertian/shier"))
                                sk_12t_add += 4;
                }
                // 2、計算霸刀花費的LHD
                if (me->query_skill("badao", 1))
                {
                        sk_bd_add += 7;
                        if (me->query("can_perform/badao/san"))
                                sk_bd_add += 8;
                }
                // 3、計算輪回劍花費的LHD
                if (me->query_skill("lunhui-sword", 1))
                {
                        sk_lhj_add += 6;
                        if (me->query("can_perform/lunhui-sword/zhen"))
                                sk_lhj_add += 6;
                }
                // 4、清除強化職業special的LHD
                job_special = me->query("lhpoint/special");
                job_add = 0;
                if (sizeof(job_special))
                {
                        key_job_special = keys(job_special);
                        for (i = 0; i < sizeof(key_job_special); i ++)
                        {
                                job_add = job_add + job_special[key_job_special[i]];
                        }        
                }
        
                total_lhd = sk_12t_add + sk_bd_add + sk_lhj_add + job_add;
                
                // 反還輪回點
                if (total_lhd >= 18)
                {
                        total_lhd = 18;
                        log_file("thborn_lhd", me->query("id") + " " + ctime(time()) + " " + sk_12t_add + " " + sk_bd_add + " " + sk_lhj_add + " " + job_add + " \n");
                        //return "輪回點數據出錯，請聯系遊戲管理員！\n";        
                }        
                
                // 清除輪回點使用記錄
                me->delete("lhpoint/special");        
                        
                if (total_lhd + me->query("scborn/cur_lunhui_point") >= 18)
                        me->set("scborn/cur_lunhui_point", 18);
                else
                        me->add("scborn/cur_lunhui_point", total_lhd);
                        
                tell_object(me, HIY "\n你總共獲得" + chinese_number(total_lhd) + "點輪回點返還。\n" NOR);
                
                // 輪回點總數設置為18，2轉後就不會再獲得
                me->set("scborn/total_lunhui_point", 18);
        }
        else// 重新2轉的單獨返回職業技能的輪回點
        {
                // 4、清除強化職業special的LHD
                job_special = me->query("lhpoint/special");
                job_add = 0;
                if (sizeof(job_special))
                {
                        key_job_special = keys(job_special);
                        for (i = 0; i < sizeof(key_job_special); i ++)
                        {
                                job_add = job_add + job_special[key_job_special[i]];
                        }        
                }
        
                total_lhd = job_add;

                // 反還輪回點
                if (total_lhd >= 18)
                {
                        total_lhd = 18;
                        log_file("thborn_lhd", me->query("id") + " " + ctime(time()) + " " + sk_12t_add + " " + sk_bd_add + " " + sk_lhj_add + " " + job_add + " \n");
                        //return "輪回點數據出錯，請聯系遊戲管理員！\n";        
                }

                // 清除輪回點使用記錄
                me->delete("lhpoint/special");

                if (total_lhd + me->query("scborn/cur_lunhui_point") >= 18)
                        me->set("scborn/cur_lunhui_point", 18);
                else
                        me->add("scborn/cur_lunhui_point", total_lhd);

                tell_object(me, HIY "\n你總共獲得" + chinese_number(total_lhd) + "點輪回點返還。\n" NOR);

                // 輪回點總數設置為18，2轉後就不會再獲得
                me->set("scborn/total_lunhui_point", 18);                
        }
        
        // 清除相關數據
        skills_status = me->query_skills();
        if (sizeof(skills_status))
        {
                myskills = keys(skills_status);
                for (i = 0; i < sizeof(myskills); i ++)
                {
                        // 如果是2次轉世，修養保留
                        if (me->query("thborn/ok") && myskills[i] == "martial-cognize")
                                continue;
                                
                        me->delete_skill(myskills[i]);
                }
        }
        // 清除絕招
        me->delete("can_perform");
        me->delete("yinyang-shiertian");
        me->delte("can_learn");
        
        // 刪除自創武功
        me->delete("pmskills");
        
        //清除學習記錄
        me->delete("marks");
        
        // 清除tuoli2記錄
        me->delete("thborn/tuoli");
        
        // lhj 記錄 
        me->delete("lunhui-sword_quest");
        
        // 清除判師，脫離記錄
        me->delete("detach");
        me->delete("betrayer");
        
        // 清除經驗，潛能，等
        me->set("combat_exp", 0);
        me->set("learned_points", 0);
        me->set("potential", 0);
        me->set("gongxian", 0);
        me->set("weiwang", 0);
        me->set("score", 0);
        me->set("shen", 0);
        me->set("max_neili", 0);
        me->set("neili", 0);
        me->set("experience", 0);  
        me->set("learned_experience", 0);
        me->set("max_jing", 100);     
        me->set("eff_jing", 100); 
        me->set("jing", 100); 
        me->set("max_qi", 100);      
        me->set("eff_qi", 100);  
        me->set("qi", 100);      
        me->set("max_jingli", 0);
        me->set("jingli", 0);
        me->delete("combat");
        me->set("shaqi", 0);
        me->set("age", 5);
        me->set("mud_age", 0);
        me->set("jiali", 0);
        me->delete("family");
        
        if (me->query("gender") == "無性")
                me->set("gender", "男性");
        

        // 清除職業及SPECIAL
        if (me->query("yhjob/job") == "俠客")
        {
                me->delete("special_skill/haoran");
                me->delete("special_skill/xiagu");
                me->delete("special_skill/shewo");
        }
        else if (me->query("yhjob/job") == "魔師")
        {
                me->delete("special_skill/moxin");
                me->delete("special_skill/youran");
                me->delete("special_skill/haoling");
        }
        else // 隱士
        {
                me->delete("special_skill/haina");
                me->delete("special_skill/xianyun");
                me->delete("special_skill/tianxia");
        }        
        me->delete("yhjob");
        
        // 刪除獨孤無招
        me->delete("can_learn/dugu-jiujian/nothing");
        
        // 提示重新選擇職業
        tell_object(me, HIG "\n相關數據清理完畢，請重新選擇職業（指令：yhjob <職業>）後再于天神對話！\n" NOR); 
        me->set("check_yhjob", 1);
        me->delete("chose_yhjob");
        
        me->delete("class");
        me->delete("can_learn");
        
        me->save();

        return 1;
}

void init()
{
        add_action("do_yhjob", "yhjob");
        command("hand tianlai zhiyuan");
}

// 選擇職業
int do_yhjob(string arg)
{
        object me;
        string msg;

        me = this_player();

        if (me->query("chose_yhjob"))
        {
                return notify_fail("你已經選擇好職業了，不能再重新選擇！\n");
        }
        
        if (! me->query("check_yhjob"))
                return notify_fail("請先與天神對話，清理相關數據，完成後才能選擇職業！\n");
        
        if (me->query("thborn/ok") && ! me->query("thborn/ok"))
                return notify_fail("你已經二轉過了，不需要再選擇職業！\n");
                
            // 介紹
        if (! arg)
        {
                // 職業介紹
                msg  = HIR "\n您目前可以選擇以下職業作為您轉世後的職業：\n" NOR;
                msg += HIC "俠客：令江湖中人景仰的職業，擁有正氣類攻擊特技。\n" NOR;
                msg += HIM "魔師: 令世人畏懼的職業，擁有邪異類攻擊特技。\n" NOR;
                msg += HIG "隱士: 被世人所遺忘，隱居世外，擁有多種輔助類特技。\n" NOR;
                msg += HIY "具體職業介紹請參見轉世職業幫助文件 help scborn_yhjob\n" NOR;
                msg += HIY "請輸入指令" HIR " yhjob 職業 " HIY "來選擇您轉世後的職業，選擇前請認真閱讀轉世職業幫助文件。\n\n" NOR;

                write(msg);
                return 1;        
        }

        if (arg != "俠客" && arg != "魔師" && arg != "隱士")
                return notify_fail("請選擇正確的職業：俠客、魔師、隱士。\n");
        
        if (sizeof(me->query("yhjob/job")))
                return notify_fail("對不起，您現在還不能重新選擇職業。\n");

        write(HIG "您選擇了 " + arg + " 的職業。\n");
        me->set("chose_yhjob", 1);
        me->set("yhjob/job" , arg);
        
        // 給予相關特技
        // 設置職業技能
        if (arg == "俠客")
        {
                me->set("special_skill/haoran",1);
                me->set("special_skill/xiagu",1);
                me->set("special_skill/shewo",1);
        }
        else if (arg == "魔師")
        {
                me->set("special_skill/moxin",1);
                me->set("special_skill/youran",1);
                me->set("special_skill/haoling",1);
        }
        else // 隱士
        {
                me->set("special_skill/haina",1);
                me->set("special_skill/xianyun",1);
                me->set("special_skill/tianxia",1);
        }
        
        me->save();

        return 1;
}

void unconcious()
{
        die();
}
