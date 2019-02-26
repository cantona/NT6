#include <ansi.h>
inherit NPC;

inherit F_COAGENT;

void create()
{
        set_name("郭靖", ({ "guo jing", "guo", "jing" }));
        set("nickname", HIY "北俠" NOR);
        set("title", "襄陽城大將");
        set("gender", "男性");
        set("age", 41);
        set("long", @LONG
他就是人稱北俠的郭靖，既是蒙古成吉思汗的金刀
駙馬，又是江南七怪、全真派馬鈺道長、「北丐」
洪七公和「老頑童」周伯通等人的徒弟，身兼數門
武功。他身着一件灰色長袍，體態魁梧，敦厚的面
目中透出一股威嚴令人不由得產生一股欽佩之情。
LONG);
        set("attitude", "peaceful");
        set("shen_type", 1);
        set("str", 40);
        set("int", 14);
        set("con", 40);
        set("dex", 40);
        set("max_qi", 8000);
        set("max_jing", 6000);
        set("neili", 8000);
        set("max_neili", 8000);
        set("jiali", 300);
        set("combat_exp", 4000000);
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
        set_skill("xianglong-zhang", 320);
        set_skill("sword", 280);
        set_skill("yuenv-jian", 280);
        set_skill("parry", 320);
        set_skill("literate", 120);
        set_skill("zuoyou-hubo", 400);
        set_skill("martial-cognize", 320);
        set_skill("craft-cognize", 280);

        map_skill("force", "yijin-duangu");
        map_skill("strike", "xianglong-zhang");
        map_skill("unarmed", "changquan");
        map_skill("sword", "yuenv-jian");
        map_skill("dodge", "shexing-lifan");
        map_skill("parry", "xianglong-zhang");

        prepare_skill("strike", "xianglong-zhang");

        set("chat_chance", 1);
        set("chat_msg", ({
                CYN "郭靖歎了口氣道：蒙古兵久攻襄陽不下，一定會再出詭計。\n" NOR,
        }));

        set("inquiry", ([
                "周伯通" : "你見到我周大哥了？他現在可好？",
                "老頑童" : "周大哥一貫這樣，沒點正經。",
                "洪七公" : "師父除了吃，就是喜歡玩。到處玩，還是為了找吃的。",
                "黃藥師" : "那是我泰山大人。他雲遊四海，神龍見首不見尾的。",
                "歐陽鋒" : "這個老毒物，害死我六位師父，一待襄陽事了，決不與他干休。",
                "黃蓉"   : "蓉兒是我的愛妻，你問她做甚？",
                "蓉兒"   : "蓉兒就是蓉兒了。你問這麼多幹嘛？",
                "郭芙"   : "這個女兒，又笨又不聽話。",
                "郭襄"   : "襄兒生於亂世，這輩子又多艱厄。但願她能快樂一世。",
                "郭破虜" : "那是我的小兒子。",
                "楊過"   : "過兒確實有出息。",
                "馬鈺"   : "馬道長於我有半師之誼。",
                "丘處機" : "邱道長義薄雲天，是真豪傑。",
                "柯鎮惡" : "那是我大師父。",
                "朱聰"   : "那是我二師父。",
                "韓寶駒" : "那是我三師父。",
                "南希仁" : "那是我四師父。",
                "張阿生" : "那是我五師父。",
                "全金髮" : "那是我六師父。",
                "韓小瑩" : "那是我七師父。",
                "丐幫"   : "丐幫英雄幾百年了，守衞襄陽多虧了他們。\n",
                "拜師"   : "現在蒙古人圍攻襄陽，我哪有心情收徒啊！\n",
                "工作"   : "…嗯…這個你去找齊兒吧，他會幫你安排的。",
                "練功"   : "東西練武場都可以練的，你去那練吧。",
                "一燈大師" : "在下對大師好生感激。",
        ]));

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

        if (! clonep(this_object()))
        {
                move("/d/wuguan/guofu_dating");
                message_vision(CYN "\n$N" CYN "走了過來，環顧四"
                               "周，深深歎了口氣。\n" NOR,
                               this_object());
                set("startroom", "/d/wuguan/guofu_dating");
        }
        carry_object("/clone/misc/cloth")->wear();
}

void init()
{
     	object ob;
     	::init();

     	if (interactive(ob = this_player())
           && userp(ob)
	 && !query_temp("mark/guofu_wait", ob )
           && ! is_fighting())
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
        	if( query("combat_exp", ob)>100000 )
		{
            		command("say 現在國難當頭，蒙古人圍攻襄陽，我這裏事情繁多。");
            		command("say 恕郭某無禮，還請閣下回去。敦儒，修文，送客！");
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
            set("mark/guofu_over", 1, 		ob);
delete("mark/guofu_ok", 			ob);
            		tell_room(environment(ob), HIC "\n只見兩位青年架着" + ob->name() +
                                                   HIC "從郭府大廳走了過來。\n" NOR, ({ ob }));
            	} else
                // 隱藏情節：郭靖教授三門特殊武功
         	if( query("mark/guofu_ok", ob)//①確認被收容於郭府
		 && query("mark/guofu_job", ob)>200//②郭府工作總量大於兩百
		 && query("combat_exp", ob)>10000//③確認經驗值在一萬和兩萬之間
                    && query("combat_exp", ob)<20000
		 && !query_temp("job_name", ob)//④此時沒有領取工作
		 && !query("family/family_name", ob)//⑤沒有拜師
		 && !query("can_learn/3skills/guojing", ob)//⑤保證以前未觸發此情節
		   && ! stringp(ob->query_skill_mapped("force"))) //⑥ 沒有激發特殊內功
		{
	command("look"+query("id", ob));
            		command("yi");
                	command("whisper"+query("id", ob)+"你在我郭府內工作也有"
                                "一定的時間\n了，怎麼連一技之長也沒有？以後怎能行走江"
                                "湖啊？…嗯…這\n樣好了，從今日起，你每天到我這裏來，"
                                "我傳授你幾項簡單的\n特殊武功好了。\n" NOR);
set("can_learn/3skills/guojing", 1, 			ob);
            	}
         }
}

void attempt_apprentice(object ob)
{
        command("sigh");
        command("say 現在蒙古人圍攻襄陽，我哪有心情收徒啊。");
        return;
}

int recognize_apprentice(object ob, string skill)
{
        if( !query("can_learn/3skills/guojing", ob) )
        {
                command("say 現在蒙古人圍攻襄陽，我哪有心情授課啊。");
                command("say 等你將來拜師之後你師父自然會教你，不用心急。");
                return -1;
        }

        if( query("combat_exp", ob)>20000 )
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
        die();
}