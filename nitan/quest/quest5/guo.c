// Copyright (C) 2003, by Lonely. All rights reserved.
// This software can not be used, copied, or modified
// in any form without the written permission from authors.
// guojing.c 郭靖

inherit NPC;
#include <ansi.h>

string *degree_desc = ({
        BLU "士卒" NOR,
        BLU "遊擊" NOR,
        HIC "參將" NOR,
        HIC "裨將" NOR,
        HIY "佐將" NOR,
        HIY "副將" NOR,
        HIR "將軍" NOR,
        HIR "提督" NOR,
});

string clear_degree(string arg);
string ask_canjun(string arg);
string ask_jianlou();
string ask_lianzhu();
string ask_fuming();
string ask_shoucheng();
string ask_chetui();

int ask_degree();
int add_degree(object ob,int lv);

void create()
{
        set_name("郭靖", ({"guo jing", "guo", "jing"}));
        set("nickname", HIY "北俠" NOR);
        set("title", "襄陽城大將");
        set("gender", "男性");
        set("age", 41);
        set("long",
                "他就是人稱北俠的郭靖，既是蒙古成吉思汗的金刀駙馬，又是\n"
                "江南七怪、全真派馬鈺道長、「北丐」洪七公和「老頑童」周\n"
                "伯通等人的徒弟，身兼數門武功。他身着一件灰色長袍，體態\n"
                "魁梧，敦厚的面目中透出一股威嚴。\n");
        set("attitude", "friendly");
        set_max_encumbrance(100000000);
        set("per", 20);
        set("str", 40);
        set("int", 20);
        set("con", 30);
        set("dex", 25);
        set("chat_chance", 1);
        set("chat_msg", ({
                "郭靖歎了口氣道：“蒙古兵久攻襄陽不下，一定會再出詭計，蓉兒又不在身邊，這....\n",
                "郭靖説道：“華箏公主近來不知可好，抽空一定要回大漠去看看她。\n",
        }));

        set("inquiry", ([
                "周伯通" : "你見到我周大哥了？他現在可好？\n",
                "老頑童" : "周大哥一貫這樣，沒點正經！\n",
                "洪七公" : "師父除了吃，就是喜歡玩。到處玩，還是為了找吃的。\n",
                "黃藥師" : "那是我泰山大人。他雲遊四海，神龍見首不見尾的。\n",
                "一燈大師" : "在下對大師好生感激。\n",
                "歐陽鋒" : "這個老毒物，害死我六位師父，一待襄陽事了，決不與他干休。\n",
                "黃蓉"   : "蓉兒是我的愛妻，你問她做甚？\n",
                "蓉兒"   : "蓉兒就是蓉兒了。你問這麼多幹嘛？\n",
                "郭芙"   : "這個女兒，又笨又不聽話。\n",
                "郭襄"   : "襄兒生於亂世，這輩子又多艱厄。但願她能快樂一世。\n",
                "郭破虜" : "那是我的小兒子。\n",
                "楊過"   : "過兒確實有出息。\n",
                "馬鈺"   : "馬道長於我有半師之誼。\n",
                "丘處機" : "邱道長義薄雲天，是真豪傑。\n",
                "柯鎮惡" : "那是我大師父。\n",
                "朱聰"   : "那是我二師父。\n",
                "韓寶駒" : "那是我三師父。\n",
                "南希仁" : "那是我四師父。\n",
                "張阿生" : "那是我五師父。\n",
                "全金髮" : "那是我六師父。\n",
                "韓小瑩" : "那是我七師父。\n",
                "丐幫"   : "丐幫英雄幾百年了，守衞襄陽多虧了他們。\n",
                "拜師"   : "現在蒙古人圍攻襄陽，我哪有心情收徒啊！\n",
                "守城"   : (: ask_shoucheng :),
                "覆命"   : (: ask_fuming :),
                "撤退"   : (: ask_chetui :),
                "狙擊"   : (: ask_jianlou :),
                "連珠箭法":   (: ask_lianzhu :),
                "策封"   :   (: ask_degree :),
                "參軍"   :   (: ask_canjun :),
                ]));

        set("qi", 10000);
        set("max_qi", 10000);
        set("jing", 8000);
        set("max_jing", 8000);
        set("neili", 34000);
        set("max_neili", 34000);
        set("jiali", 500);

        set("combat_exp", 25000000);
        set("score", 200000);

        set_skill("force", 320);
        set_skill("xiantian-gong", 320);
        set_skill("yijin-duangu", 320);
        set_skill("guoshi-xinfa", 280);
        set_skill("dodge", 300);
        set_skill("feiyan-zoubi", 280);
        set_skill("jinyan-gong", 300);
        set_skill("shexing-lifan", 300);
        set_skill("unarmed", 300);
        set_skill("changquan", 300);
        set_skill("strike", 320);
        set_skill("dragon-strike", 320);
        set_skill("sword", 280);
        set_skill("yuenv-jian", 280);
        set_skill("parry", 320);
        set_skill("literate", 120);
        set_skill("zuoyou-hubo", 400);
        set_skill("martial-cognize", 320);
        set_skill("craft-cognize", 280);
        set_skill("array-cognize", 280);
        set_skill("arrow", 400);
        set_skill("lianzhu-arrow", 400);

        map_skill("arrow", "lianzhu-arrow");
        map_skill("force", "yijin-duangu");
        map_skill("strike", "dragon-strike");
        map_skill("unarmed", "changquan");
        map_skill("sword", "yuenv-jian");
        map_skill("dodge", "shexing-lifan");
        map_skill("parry", "xianglong-zhang");

        prepare_skill("strike", "dragon-strike");
        
        create_family("郭府", 1, "北俠");

        set("chat_chance_combat", 120);
        set("chat_msg_combat", ({
                (: command("perform strike.fei twice") :),
                (: command("perform strike.hui twice") :),
                (: command("perform strike.zhen twice") :),
                (: command("perform strike.qu and strike.hui") :),
                (: command("perform strike.fei and strike.hui") :),
                (: command("perform strike.zhen and strike.hui") :),
                (: command("perform strike.zhen and strike.fei") :),
                (: exert_function, "shield" :),
                (: exert_function, "powerup" :),
                (: exert_function, "recover" :),
        }));

        set_temp("apply/damage", 300);
        set_temp("apply/unarmed_damage", 300);
        set_temp("apply/armor", 500);

        setup();

        carry_object("/clone/misc/cloth")->wear();
}

void init()
{
        object me = this_player();
        object ob;
        ::init();

        if( query("jungong", me)>100 )
                add_action("do_study", "qingjiao");
                
        if (interactive(ob = this_player())
           && userp(ob)
           && !query_temp("mark/guofu_wait", ob )
           && !is_fighting())
        {
                if( query("mark/guofu_over", ob) )
                {
                        command("hmm");
                        command("say 我不是讓你另謀出路嗎？又跑回來幹嘛？");
                        command("say 敦儒，修文，送" + ob->name() + NOR + CYN "出去！");
                        message_vision(HIC "\n只見$N" HIC "一招手，頓時從正廳進來了兩"
                                       "位青年，將$n" HIC "架了出去。\n\n",
                                       this_object(), ob);
                        ob->move("/d/xiangyang/westjie1");
                        tell_room(environment(ob), HIC "\n只見兩位青年架着" + ob->name() +
                                                   HIC "從郭府大廳走了過來。\n" NOR, ({ ob }));
                } else
                if( query("mark/guofu_out", ob )
                 && query("combat_exp", ob)<100000 )
                {
                        command("say 你現在的武功已經有一定的底子了，應該多走動走動。");
                        command("say 別老是呆在我這裏，這對你幫助不大。敦儒，修文，送客！");
                        message_vision(HIC "\n只見$N" HIC "一招手，頓時從正廳進來了兩"
                                       "位青年，將$n" HIC "送了出去。\n\n",
                                       this_object(), ob);
                        ob->move("/d/xiangyang/westjie1");
                        tell_room(environment(ob), HIC "\n只見兩位青年陪着" + ob->name() +
                                                   HIC "從郭府大廳走了過來。\n" NOR, ({ ob }));
                } else
                if ((int)ob->query_condition("killer"))
                {
                        command("sigh");
                        command("say 你殺性如此之重，我這裏也留不得你，你還是走吧。");
                        command("say 敦儒，修文，送客！");
                        message_vision(HIC "\n只見$N" HIC "一招手，頓時從正廳進來了兩"
                                       "位青年，將$n" HIC "架了出去。\n\n",
                                       this_object(), ob);
                        ob->move("/d/xiangyang/westjie1");
                        set("mark/guofu_over", 1, ob);
                        delete("mark/guofu_ok", ob);
                        tell_room(environment(ob), HIC "\n只見兩位青年架着" + ob->name() +
                                                   HIC "從郭府大廳走了過來。\n" NOR, ({ ob }));
                } else
                // 隱藏情節：郭靖教授三門特殊武功
                if( query("mark/guofu_ok", ob)//①確認被收容於郭府
                   && query("mark/guofu_job", ob)>200//②郭府工作總量大於兩百
                   && query("combat_exp", ob)>10000//③確認經驗值在一萬和兩萬之間
                   && query("combat_exp", ob)<50000
                   && !query_temp("job_name", ob)//④此時沒有領取工作
                   && !query("family/family_name", ob)//⑤沒有拜師
                   && !query("can_learn/3skills/guojing", ob)//⑤保證以前未觸發此情節
                   && ! stringp(ob->query_skill_mapped("force"))) //⑥ 沒有激發特殊內功
                {
                        command("look "+query("id", ob));
                        command("yi");
                        command("whisper "+query("id", ob)+"你在我郭府內工作也有"
                                "一定的時間\n了，怎麼連一技之長也沒有？以後怎能行走江"
                                "湖啊？…嗯…這\n樣好了，從今日起，你每天到我這裏來，"
                                "我傳授你幾項簡單的\n特殊武功好了。\n" NOR);
                        set("can_learn/3skills/guojing", 1, ob);
                }
         }
}

string ask_shoucheng()
{
        object *ene;
        object me = this_player();

        if (is_fighting())
        {
                ene = query_enemy();

                if (sizeof(ene) > 1)
                        return "“請" + RANK_D->query_respect(me) + "稍等片刻，我先和這" +
                                sizeof(ene) + "位高手切磋幾下！”\n";
                if (sizeof(ene) == 1)
                        return "“請" + RANK_D->query_respect(me) + "稍等片刻，我先和" +
                                ene[0]->name() + "切磋幾下！”\n";
        }

        if( query_temp("guo_shoucheng/mark_shadi", me) )
                return "“" + RANK_D->query_respect(me) + "不是已有守城任務了嗎！”\n";

        if( query_temp("guo_shoucheng/mark_jianlou", me) )
                return "“" + RANK_D->query_respect(me) + "不是已有狙擊任務了嗎！”\n";

        if( query("combat_exp", me)<100000 )
                       return "“" + RANK_D->query_respect(me) + "手無縛雞之力，還是別領任務的為好！”\n";

               if ((int)me->query_skill("force", 1) < 60)
                       return "守城是件危險工作，我看" + RANK_D->query_respect(me) + "的基本內力不足！\n";

               if ((int)me->query_condition("jobshadi_failed"))
               {
                message_vision("$N對着$n搖了搖頭説：逃跑失敗了還來見我??\n", this_object(), me);
                return "“" + RANK_D->query_respect(me) + "你還是別領任務的為好！”\n";
               }

               if( query_temp("guo_shoucheng/failed", me) )
               {
                 delete_temp("guo_shoucheng", me);
                 me->apply_condition("jobshadi_failed", 4);
                 return "“臨陣脱逃，還敢回來見我！！？？”\n";
               }

              if ((int)me->query_condition("jobshadi_limit"))
               {
                message_vision("$N對着$n搖了搖頭説：你不是正做着守城任務嗎??\n", this_object(), me);
                return "“" + RANK_D->query_respect(me) + "你快點回你的崗位上去！”\n";
               }

               if ((int)me->query_condition("guojob2_busy"))
               {
                message_vision(CYN "$N對着$n搖了搖頭説：疲憊之師不利作戰！！\n" NOR,
                            this_object(), me);
                return "“" + RANK_D->query_respect(me) + "你還是休息一下再來吧！”\n";
               }

               if( query("shen", me)>0 )
               {
                switch (random(2)) {
                case 0:
                        set_temp("guo_shoucheng/mark_shadi", 1, me);
                        set_temp("guo_shoucheng/carry_location", "eastgate1", me);
                        return "“現在蒙古靼子侵犯中原，這位" +
                                RANK_D->query_respect(me) + "去玄武內門幫助宋軍守城吧。";

                       break;
                case 1:
                        set_temp("guo_shoucheng/mark_shadi", 2, me);
                        set_temp("guo_shoucheng/carry_location", "northgate1", me);
                        return "“現在蒙古靼子侵犯中原，這位" + RANK_D->query_respect(me) + "去青龍內門幫助宋軍守城吧。";

                               break;
                }
        }
        else
        {
        switch( random(2) ) {
                case 0:
                        set_temp("guo_shoucheng/mark_shadi", 3, me);
                        set_temp("guo_shoucheng/carry_location", "southgate1", me);
                return "“現在蒙古靼子侵犯中原，這位"+RANK_D->query_respect(me)+"去朱雀內門幫助宋軍守城吧。";

                       break;
                case 1:
                        set_temp("guo_shoucheng/mark_shadi", 4, me);
                        set_temp("guo_shoucheng/carry_location", "westgate1", me);
                return "“現在蒙古靼子侵犯中原，這位"+RANK_D->query_respect(me)+"去白虎內門幫助宋軍守城吧。";

                       break;
                }
        }
}


string ask_jianlou()
{
        object *ene;
        object me = this_player();

        if (is_fighting())
        {
                ene = query_enemy();

                if (sizeof(ene) > 1)
                        return "“請"+RANK_D->query_respect(me) +
                               "稍等片刻，我先和這" + sizeof(ene) + "位高手切磋幾下！”\n";
                if (sizeof(ene) == 1)
                        return "“請" + RANK_D->query_respect(me) + "稍等片刻，我先和"
                                + ene[0]->name() + "切磋幾下！”\n";
        }

        if( query_temp("guo_shoucheng/mark_shadi", me) )
                return "“"+RANK_D->query_respect(me)+"不是已有守城任務了嗎！”\n";

        if( query_temp("guo_shoucheng/mark_jianlou", me) )
                return "“"+RANK_D->query_respect(me)+"不是已有狙擊任務了嗎！”\n";

        if ((int)me->query_condition("jobshadi_failed"))
        {
                message_vision(
                        "$N對着$n搖了搖頭説：逃跑失敗了還來見我??\n", this_object(), me);
                return "“"+RANK_D->query_respect(me)+"你還是別領任務的為好！”\n";
        }

        if( query_temp("guo_shoucheng/failed", me) )
        {
                delete_temp("guo_shoucheng", me);
                me->apply_condition("jobshadi_failed",4);
                return "“臨陣脱逃，還敢回來見我！！？？”\n";
        }

        if ((int)me->query_skill("arrow", 1) < 50)
        {
                message_vision(CYN"$N對着$n搖了搖頭説：你的基本箭法太差了！\n"NOR,
                               this_object(), me);
                return "“"+RANK_D->query_respect(me)+"，我怕你難以勝任啊！”\n";
        }

        if ((int)me->query_condition("jobjianlou_limit"))
        {
                message_vision("$N對着$n搖了搖頭説：你不是正做着阻擊任務嗎？？\n",
                                this_object(), me);
                return "“"+RANK_D->query_respect(me)+"，請你快點回你的崗位上去！”\n";
        }

        if ((int)me->query_condition("guojob2_busy"))
        {
                message_vision(CYN"$N對着$n搖了搖頭説：疲憊之師不利作戰！！\n"NOR,
                                this_object(), me);
                return "“"+RANK_D->query_respect(me)+"你還是休息一下再來吧！”\n";
        }

        set_temp("guo_shoucheng/mark_jianlou", 2, me);
        set_temp("guo_shoucheng/where", "east_out", me);
        return "“那就有勞這位"+RANK_D->query_respect(me) +
               "前往青龍內門的東城箭樓，負責狙擊蒙古箭手的任務吧。\n”";
}

string ask_fuming()
{
        int job_pot, job_exp, job_sco, reward;
        int job_mar;
        object me = this_player();

        if( !me->query_condition("jobshadi_failed") && query_temp("guo_shoucheng/failed", me) )
        {
                delete_temp("guo_shoucheng", me);
                me->apply_condition("jobshadi_failed",4);
                return "“臨陣脱逃，還敢回來覆命！！？？”\n";
        }

        if( query_temp("guo_shoucheng/help_killed", me )
             && !query_temp("guo_shoucheng/job_over", me) )
        {
                job_exp=(query_temp("guo_shoucheng/help_killed", me))*80;
                job_pot = job_exp / 2;
                job_sco = job_pot / 2;
                job_mar = job_pot / 2;

                if (job_exp > 2000) job_exp = 2000;
                if (job_pot > 1000) job_pot = 1000;

/*
                if( query_temp("warquest/guard", me) )
                {
                        job_exp += 2000;
                        job_pot += 1000;
                        addn_temp("warquest/reward", 200, me);
                }
#ifdef DB_SAVE
                if (MEMBER_D->is_double_reward(me))
                {
                        job_exp *= 2;
                        job_pot *= 2;
                        job_mar *= 2;
                        job_sco *= 2;
                }
#endif
                addn("combat_exp", job_exp, me);
                addn("potential", job_pot, me);
                addn("score", job_sco, me);
                addn("experience", job_mar, me);
*/
                GIFT_D->bonus(me, ([ "exp" : job_exp, "pot" : job_pot, "mar" : job_mar, "score" : job_sco ]));

/*
                tell_object(me, HIW "你被獎勵了" + chinese_number(job_exp) + "點經驗值及" +
                                chinese_number(job_pot) + "點潛能和" + chinese_number(job_sco) + "點閲歷體會。\n" NOR);
*/
                delete_temp("guo_shoucheng", me);
                me->apply_condition("guojob2_busy", 2);
                //addn("guo_shoucheng/reward_exp", job_exp, me);
                //addn("guo_shoucheng/reward_potential", job_pot, me);

                return "“"+RANK_D->query_respect(me) + "，為國殺敵，不錯不錯！”\n";
        }

        if( !query_temp("guo_shoucheng/mark_shadi", me )
                 && !query_temp("guo_shoucheng/mark_jianlou", me )
                 || !query_temp("guo_shoucheng/job_over", me) )
                return "“你好像沒完成任務吧，還來複什麼命？”\n";

        if( query_temp("guo_shoucheng/killed_mgb", me)<1 )
        {
                delete_temp("guo_shoucheng", me);
                return "“你殺了幾個敵人啊，就從前線逃回來了？\n";
        }

        message_vision(CYN "$N對$n説道：“"+RANK_D->query_respect(me)+"辛苦了，去休息一下吧！”\n" NOR, this_object(), me);

        job_exp=(query_temp("guo_shoucheng/killed_mgb", me))*100;
        job_exp += query_temp("guo_jianlou/killed_mgb", me)*100;
        job_pot = job_exp / 2;
        job_sco = job_pot / 2;
        job_mar = job_pot / 2;

        if (job_exp > 3000) job_exp = 3000;
        if (job_pot > 1500) job_pot = 1500;
        if( query_temp("warquest/guard", me) )
        {
                job_exp += 1000;
                job_pot += 500;
                addn_temp("warquest/reward", 500, me);
        }

        reward=query_temp("guo_shoucheng/killed_mgb", me)/10+1;

/*
#ifdef DB_SAVE
                if (MEMBER_D->is_double_reward(me))
                {
                        job_exp *= 2;
                        job_pot *= 2;
                        job_mar *= 2;
                        job_sco *= 2;
                        reward  *= 2;
                }
#endif

        tell_object(me, HIW "你被獎勵了" + chinese_number(job_exp) + "點經驗值及" +
                        chinese_number(job_pot) + "點潛能和" + chinese_number(job_sco) + "點閲歷還有一些威望體會。\n" NOR);
*/

        GIFT_D->bonus(me, ([ "exp" : job_exp, "pot" : job_pot, "mar" : job_mar, "score" : job_sco, "weiwang" : 5 ]));

        me->apply_condition("guojob2_busy", 2);

/*
        addn("combat_exp", job_exp, me);
        addn("potential", job_pot, me);
        addn("weiwang", 5, me);
        addn("score", job_sco, me);
        addn("experience", job_mar, me);
*/

        //addn("guo_shoucheng/reward_exp", job_exp, me);
        //addn("guo_shoucheng/reward_potential", job_pot, me);
        addn("jungong", reward, me);

        delete_temp("guo_shoucheng", me);

        return "“" + RANK_D->query_respect(me) + "，為國殺敵，奮勇當先，當記軍功" HIY +
                chinese_number(reward) + NOR + CYN "策！！！”\n" NOR;
}

string ask_chetui()
{
        object me;

        me = this_player();

        if( !query_temp("guo_shoucheng/start_job", me )
                 && !query_temp("guo_shoucheng/mark_jianlou", me )
                 && !query_temp("guo_shoucheng/mark_shadi", me) )
                return "你沒有領任務,跑這裏瞎嚷嚷什麼？";

        me->apply_condition("jobshadi_limit", 0);
        me->apply_condition("jobjianlou_limit", 0);
        addn("combat_exp", -100+random(20), me);
        me->apply_condition("jobshadi_failed", 4);
        delete_temp("guo_shoucheng", me);

        return "沒關係，下次繼續努力 。";
}

string ask_lianzhu()
{
        object me = this_player(), ob = this_object();

        if( query("guo_shoucheng/reward", me)>100 )
        {
                message_sort(HIC "$N哈哈大笑道：“這套連珠箭法(lianzhu-arrow)我就" +
                             "傳於你了，望你奮勇殺敵，多立戰功，我也無憾了！\n" NOR, ob);
                return "時間緊迫，現在就開始學吧(qingjiao lianzhu-arrow)！\n";
        } else
        {
                message_sort(HIC "$N微微點頭道：“這套連珠箭法(lianzhu-arrow)是我的" +
                             "畢生心血之作，\n不便輕易相傳！！\n" NOR, ob);
                return "若閣下真有奮勇殺敵，助我大宋之心，日後必慷慨相送！\n";
        }
}

int do_study(string arg)
{
        string skill;
        object me = this_player(), ob = this_object();

        if (! arg || arg != "lianzhu-arrow")
                return notify_fail("你要向郭靖請教(qingjiao)什麼？\n");

        if (me->query_skill("lianzhu-arrow", 1) > me->query_skill("arrow", 1))
                return notify_fail("你的基本箭法太差了，無法繼續學習連珠箭法。\n");

        if (me->query_skill("lianzhu-arrow", 1) * me->query_skill("lianzhu-arrow", 1) > query("jungong", me)*50 )
                return notify_fail("你的守城軍功不夠多，郭靖不願繼續教你了！\n");

        if( query("learned_points", me) >= query("potential", me) )
                return notify_fail("你的潛能不夠了！\n");

        if( query("jing", me)<100 || query("qi", me)<100 )
                return notify_fail("你現在太累了，先休息一下吧！\n");

        me->receive_damage("qi", 10 + random(40));
        me->receive_damage("jing", 10 + random(40));
        addn("learned_points", 1, me);
        message_vision(HIC "$N指點了$n一些有關" HIW "「連珠箭法」" HIC "的問題，" +
                       "$n似乎有些心得。\n" NOR, ob, me);

        me->improve_skill("lianzhu-arrow", random(me->query_skill("arrow", 1)));

        return 1;
}

int ask_degree()
{
        int lv;
        object ob = this_player();

        if( query_temp("degree_jungong", ob) )
        {
                command("say " + RANK_D->query_respect(ob) + "稍安勿躁，" +
                        "我已經派人前往請封了！\n");
                return 1;
        }
        
        lv=query("degree_jungong", ob);
        if (lv >= sizeof(degree_desc))
        {
                command("say 草民豈敢為大人請封，大人若親自前往朝綱，前途自不限量！\n");
                return 1;
        }
                
        if( query("degree_jungong", ob) < 0 )
                delete("degree_jungong", ob);

        if( query("jungong", ob)>
            (100*(1+query("degree_jungong", ob))*(1+query("degree_jungong", ob))) )
                lv=query("degree_jungong", ob)+1;

        if( lv <= query("degree_jungong", ob) )
        {
                command("say"+query("name", ob)+"，要獲得更高的策封，必須多立軍功才可以啊！\n");
                return 1;
        }

        command("say " + RANK_D->query_respect(ob) + "請稍候，我即刻派人前往京城為" +
                RANK_D->query_respect(ob) + "請封！\n");

        call_out("add_degree", 10, ob, lv);
        set_temp("degree_jungong", 1, ob);
        message("channel:rumor", MAG "【大宋襄陽】" + CHINESE_D->chinese_date((time()-14*365*24*60*60)) +
                "，一匹快馬從襄陽出發，直奔大宋京城！\n" NOR, users());

        return 1;
}

int add_degree(object ob,int lv)
{
        string degree, old_degree;
        degree = degree_desc[lv-1];

        if( query("degree", ob) )
                old_degree=query("degree", ob);
        else old_degree = "";

        message("channel:rumor", HIY "【大宋京城】奉天承命，皇帝詔曰：" +
                "策封"+old_degree+""+HIW+query("name", ob)+
                HIY " 為大宋 " NOR + degree + HIY "，欽此！\n" NOR, users());

        delete_temp("degree_jungong", ob);

        if( query("degree", ob) )
        {
                if( query("degree_ask", ob) )
                        degree=HIM " ☆ " NOR+clear_degree(query("degree", ob))+
                                 HIM " ☆ " NOR + degree + HIM " ☆ " NOR;
                else
                        degree=HIM " ☆ " NOR+clear_degree(query("degree", ob))+
                                 degree + HIM " ☆ " NOR;
        } else
                degree = HIM " ☆ " NOR + degree + HIM " ☆ " NOR;

        set("degree_jungong", lv, ob);
        set("degree", degree, ob);
        addn("weiwang", lv*200, ob);
        return 1;
}

string clear_degree(string arg)
{
        if ((strsrch(arg, BLU "士卒" NOR) >= 0) ||
            (strsrch(arg, BLU "遊擊" NOR) >= 0) ||
            (strsrch(arg, HIC "參將" NOR) >= 0) ||
            (strsrch(arg, HIC "裨將" NOR) >= 0) ||
            (strsrch(arg, HIY "佐將" NOR) >= 0) ||
            (strsrch(arg, HIY "副將" NOR) >= 0) ||
            (strsrch(arg, HIR "將軍" NOR) >= 0) ||
            (strsrch(arg, HIR "提督" NOR) >= 0) ||
            (strsrch(arg, HIM " ☆ " NOR) >= 0))
        {
                arg = replace_string(arg, BLU "士卒" NOR,"");
                arg = replace_string(arg, BLU "遊擊" NOR,"");
                arg = replace_string(arg, HIC "參將" NOR,"");
                arg = replace_string(arg, HIC "裨將" NOR,"");
                arg = replace_string(arg, HIY "佐將" NOR,"");
                arg = replace_string(arg, HIY "副將" NOR,"");
                arg = replace_string(arg, HIR "將軍" NOR,"");
                arg = replace_string(arg, HIR "提督" NOR,"");
                arg = replace_string(arg, HIM " ☆ " NOR,"");
        }
        return arg;
}

string ask_canjun(string arg)
{
        object me = this_player();
        return WAR_D->join_kingwar(me);
}

int recognize_apprentice(object ob, string skill)
{
        if( !query("can_learn/3skills/guojing", ob) )
        {
                command("say 現在蒙古人圍攻襄陽，我哪有心情授課啊。");
                command("say 等你將來拜師之後你師父自然會教你，不用心急。");
                return -1;
        }

        if( query("combat_exp", ob)>50000 )
        {
                command("say 你經驗也不低了，應該多出去鍛鍊，呆在這對你幫助不大。\n");
                return -1;
        }

        if (skill != "force"
           && skill != "guoshi-xinfa"
	   && skill != "dodge"
           && skill != "feiyan-zoubi"
           && skill != "unarmed"
           && skill != "changquan")
        {
                command("shake");
                command("say 我最多傳授你幾項較為基本的特殊技能，複雜了你領悟不了。");
                command("say 你可以跟我學郭氏心法、飛檐走壁、太祖長拳和一些基本技能。\n");
                return -1;
        }

        if( !query_temp("can_learn/guojing", ob) )
        {
                command("nod2");
                command("say 念你勤奮刻苦，我便傳授你一些技能，可要認真記好了。");
                set_temp("can_learn/guojing", 1, ob);
        }
        return 1;
}

void unconcious()
{
        full_self();
        return;
}

varargs void die(object killer)
{
        full_self();
        return;
}
