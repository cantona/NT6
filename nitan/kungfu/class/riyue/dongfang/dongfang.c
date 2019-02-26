#include <ansi.h>
#include <command.h>
#include "/kungfu/skill/eff_msg.h";

inherit NPC;
inherit F_MASTER;

mixed ask_kuihua();
mixed ask_skill1();
mixed ask_skill2();
mixed ask_skill3();
mixed ask_skill4();
mixed ask_skill5();
mixed ask_skill6();

int p, j;

void create()
{
        object ob;
	set_name(HIR "東方不敗" NOR, ({ "dongfang bubai", "dongfang", "bubai" }));
	set("long", " 她就是東方不敗，看起來不男不女，樣子卻甚為妖媚。\n");
	set("gender", "無性");
	set("age", 30);
	set("shen_type", -1);
	set("str", 51);
	set("int", 39);
	set("con", 50);
	set("dex", 62);
	
	set("max_qi", 10000);
	set("max_jing", 10000);
    set("max_jingli", 10000);
    set("jingli", 10000);
	set("max_neili", 12000);
	set("neili", 12000);
	set("jiali", 550);
	set("combat_exp", 5000000);
	set("score", 1200000);

	set_skill("force", 450);
    set_skill("parry", 450);
    set_skill("dodge", 450);
    set_skill("sword", 450);
    set_skill("unarmed", 450);
    set_skill("literate", 350);
    set_skill("martial-cognize", 400);
    set_skill("kuihua-mogong", 450);

	map_skill("force", "kuihua-mogong");
	map_skill("dodge", "kuihua-mogong");
	map_skill("unarmed", "kuihua-mogong");
	map_skill("sword", "kuihua-mogong");
        map_skill("parry", "kuihua-mogong");

	prepare_skill("unarmed", "kuihua-mogong");

	create_family("日月神教", 2, "弟子");

        set("inquiry", ([
                "楊蓮亭"    :    "蓮弟 ……\n",
                "任我行"    :    "哼 ……，我當初真該殺了他。\n",
                "葵花魔功"  :    (: ask_kuihua :),
                "無聲無息"  :    (: ask_skill1 :),
                "無窮無盡"  :    (: ask_skill2 :),
                "無邊無際"  :    (: ask_skill3 :),
                "無法無天"  :    (: ask_skill4 :),
                "毀天滅地"  :    (: ask_skill5 :),
		"分身化影"  :    (: ask_skill6 :),
                
        ]));

	set("chat_chance_combat", 120);
	set("chat_msg_combat", ({
		(: perform_action, "dodge.sheng" :),
		(: perform_action, "sword.bian" :),
		(: perform_action, "sword.tian" :),
		(: perform_action, "sword.qiong" :),
		(: perform_action, "sword.zhenwu" :),
                (: perform_action, "dodge.sheng" :),
                (: perform_action, "unarmed.bian" :),
                (: perform_action, "unarmed.tian" :),
                (: perform_action, "unarmed.qiong" :),
                (: perform_action, "sword.hui" :),
		(: exert_function, "recover" :),
		(: exert_function, "powerup" :),
		(: exert_function, "shield" :),
		(: exert_function, "roar" :),
	}) );

	setup();

        if (clonep())
        {
                     ob = find_object("/clone/lonely/book/kuihua-jianpu"); 
                     if (! ob) ob = load_object("/clone/lonely/book/kuihua-jianpu");
      
                     if (! environment(ob) && random(20) == 1) 
                             ob->move(this_object()); 
        }

        carry_object(__DIR__"zhen")->wield();
        carry_object(__DIR__"changpao")->wear();
}

mixed ask_kuihua()
{
        object ob = this_object();
        object me = this_player();
        int lv = me->query_skill("pixie-jian", 1);

        if( query_temp("teach_kh", me) )
        {
            command("shake");
            
            return 1;
        }
        
        if( query("gender", me) != "無性" && !query("special_skill/guimai", me) )
        {
             command("heng");
             ob->kill_ob(me);
             return 1;
        }

	if (me->query_skill("kuihua-mogong", 1))
	{
		command("heng");
		return 1;
	}
	
        if (lv < 300)
        {
             if (me->query_skill("pixie-jian", 1))
             {
                     command("say 下去好好練習，別來煩我！");
                     return 1;
             }
             command("say 滾開！就憑你也配問這個？！");
             return 1;
        }

        command("nod");
        command("heihei");
        command("say 好吧，我就傳你葵花魔功，你可小心了！");
        tell_object(me, HIG "\n東方不敗猛然尖嘯一聲，聲音激盪刺耳，令人心馳神搖。你覺得胸口一震，一口鮮血噴出。\n" NOR);
        tell_object(me, HIC "然而你卻無法捕捉到東方不敗的動向！\n" NOR);

        set_temp("teach_kh", 1, me);

        if( query("qi", me)<2000 )
        {
              me->unconcious();
              delete_temp("teach_kh", me);
              return 1;              
        }
        
        me->receive_wound("qi",query("qi", me)/2);
        addn("neili", -(2000-lv), me);
        me->start_busy(2 + random(2));
        p=query("qi", me)*100/query("max_qi", me);
        tell_object(me, "(你" + eff_status_msg(p) + ")\n\n");
   
        j = 0;
    
    	me->start_busy(60);
    	
        remove_call_out("teach_kuihua");
        call_out("teach_kuihua", 2, me, lv);
        
        return 1;        
}

void teach_kuihua(object me, int lv)
{
        int sz;
	int qi;
	
        string* teach_words = ({
        HIG "忽然間東方不敗身法陡然加快，呼嘯着在你周圍旋轉，你感覺胸悶氣短。\n" NOR,
        HIG "霎那間一道銀光閃過，東方不敗手中銀針頓時化分為萬千幻影，纏繞在你周圍，你漸漸覺得頭暈目眩。\n" NOR,
        HIG "漸漸地，東方不敗身法越來越快，已化身為無數她的身影，東方不敗尖嘯一聲，從不同的角度向你襲來。\n" NOR,
        HIG "東方不敗長袖一拂，一道銀光劃過，猛然間在你眼前一亮，你頓覺得胸口刺痛無比。\n" NOR,
        });

        if (environment(me) != environment(this_object())
            || ! environment(me))
              return;

        sz = sizeof(teach_words);

        tell_object(me, teach_words[random(sz)]);
        tell_object(me, HIC "然而你卻無法捕捉到東方不敗的動向！\n" NOR);
        
	qi = 1400 - lv;
	if (qi < 100)qi = 100;
	
        if( query("qi", me) <= (1400-lv) )
        {
               me->unconcious();
               delete_temp("teach_kh", me);
               return;
        }

        me->receive_wound("qi", qi);
        addn("neili", -(1600-lv), me);
        p=query("qi", me)*100/query("max_qi", me);
        tell_object(me, "( 你" + eff_status_msg(p) + ")\n\n");
        j ++;

        // 能學葵花魔功了
        if (j >= 6 + random(2))
        {
              message_sort(HIW "東方不敗尖嘯一聲，又回到了原地，似乎從未離開過。\n" NOR, me);

              message_sort(HIW "東方不敗再未有任何言語，只是玩弄着自己的指甲 ……\n" NOR, me);

              if (random(10) > 7)return;
              
              write(HIM "你仔細回味剛才那驚心動魄的一幕，回想東方不敗施展的各種招式，猛然間你一聲長歎，"
                        "心中疑慮頓然消除 ……\n" NOR);
              if (me->can_improve_skill("force"))
                    me->improve_skill("force", 1500000);
              if (me->can_improve_skill("dodge"))
                    me->improve_skill("dodge", 1500000);
              if (me->can_improve_skill("parry"))
                    me->improve_skill("parry", 1500000);
              me->improve_skill("martial-cognize", 1500000);

	      me->set_skill("pixie-jian", 0);
              me->delete_skill("pixie-jian");
              delete_temp("teach_kh", me);

              if( query("can_perform/pixie-jian/po", me) )
                       set("can_perform/kuihua-mogong/qiong", 1, me);
              me->set_skill("kuihua-mogong", 200 + (lv - 300) / 2 );
              tell_object(me, HIG "你學會了「葵花魔功」！\n" NOR);
              
              me->save();
              
              me->interrupt_me(me);
              
              return;
        }

        remove_call_out("teach_kuihua");
        call_out("teach_kuihua", 3, me, lv);
                       
}

mixed ask_skill1()
{
        object me = this_player();
        
        if( query("gender", me) != "無性" && !query("special_skill/guimai", me) )
        {
               command("heng");
               this_object()->kill_ob(me);
               return 1;
        }
        if( query("can_perform/kuihua-mogong/sheng", me) )
        {
               command("say 我不是已經傳了你這招嗎？怎麼又來問我！");
               return 1;
        }
        command("nod");
        command("heihei");
        tell_object(me, HIR "\n東方不敗身子忽進忽退，身形詭祕異常，在你身邊飄忽不定，不久又回到了原地。\n");
        command("say 看清楚了？！");
        if (me->can_improve_skill("dodge"))
              me->improve_skill("dodge", 1500000);
        if (me->can_improve_skill("kuihua-mogong"))
              me->improve_skill("kuihua-mogong", 1500000);
        me->improve_skill("martial-cognize", 1500000);

        set("can_perform/kuihua-mogong/sheng", 1, me);
        tell_object(me, HIG "你學會了「無聲無息」。\n");

        return 1;
}

mixed ask_skill2()
{       
        object me = this_player();
        
        if( query("gender", me) != "無性" && !query("special_skill/guimai", me) )
        {
               command("heng");
               this_object()->kill_ob(me);
               return 1;
        }
        if( query("can_perform/kuihua-mogong/qiong", me) )
        {
               command("say 我不是已經傳了你這招嗎？怎麼又來問我！");
               return 1;
        }
        if (me->query_skill("kuihua-mogong", 1) < 250)
        {
               command("say 你葵花魔功還不夠嫻熟，還不快下去多加練習。");
               return 1;
        }
      
        command("heihei");
        tell_object(me, HIR "\n東方不敗尖嘯一聲，猛然進步欺前，一招竟直襲向虛空，速度之快，令人稱奇。\n" NOR);
        command("say 看清楚了？！");
        command("say 這招精要在於快、準、狠，對於實戰經驗較低的人可能會一招使其斃命！");
        command("say 你下去一定要勤加練習。");

        if (me->can_improve_skill("force"))
              me->improve_skill("force", 1500000);
        if (me->can_improve_skill("kuihua-mogong"))
              me->improve_skill("kuihua-mogong", 1500000);
        me->improve_skill("martial-cognize", 1500000);

        set("can_perform/kuihua-mogong/qiong", 1, me);
        tell_object(me, HIG "你學會了「無窮無盡」。\n");

        return 1;
}

mixed ask_skill3()
{
        object me = this_player();
        
        if( query("gender", me) != "無性" && !query("special_skill/guimai", me) )
        {
               command("heng");
               this_object()->kill_ob(me);
               return 1;
        }
        if( query("can_perform/pixie-jian/po", me) )
        {
               command("say 下去好好練習吧，沒事別來煩我！");
               return 1;
        }
        if (me->query_skill("kuihua-mogong", 1) < 260)
        {
               command("say 你葵花魔功還不夠嫻熟，還不快下去多加練習。");
               return 1;
        }      
        command("heihei");
        tell_object(me, HIR "\n東方不敗一聲尖嘯，身體猛然旋轉不定，霎那間似乎有千萬根銀針，齊齊卷向虛空 ……\n" NOR);
        command("say 這招威力巨大，能傷對方丹元，使其短期內不能施展任何外功！");
        command("say 你下去一定要勤加練習。");

        if (me->can_improve_skill("force"))
              me->improve_skill("force", 1500000);
        if (me->can_improve_skill("kuihua-mogong"))
              me->improve_skill("kuihua-mogong", 1500000);
        me->improve_skill("martial-cognize", 1500000);

        set("can_perform/pixie-jian/po", 1, me);
        tell_object(me, HIG "你學會了「無邊無際」。\n");

        return 1;

}

mixed ask_skill4()
{
        object me = this_player();
        
        if( query("gender", me) != "無性" && !query("special_skill/guimai", me) )
        {
               command("heng");
               this_object()->kill_ob(me);
               return 1;
        }
        if( query("can_perform/kuihua-mogong/tian", me) )
        {
               command("say 我不是已經傳了你這招嗎？怎麼又來問我！");
               return 1;
        }
        if (me->query_skill("kuihua-mogong", 1) < 220)
        {
               command("say 你葵花魔功還不夠嫻熟，還不快下去多加練習。");
               return 1;
        }      
        command("heihei");
        command("say 看好了！");
        tell_object(me, HIR "\n東方不敗默運葵花魔功，身形變得奇快無比，接連從不同的方位向虛空攻出數招！\n" NOR);
        command("say 這招以快取勝，以快制敵。");
        command("say 你下去一定要勤加練習。");

        if (me->can_improve_skill("force"))
              me->improve_skill("force", 1500000);
        if (me->can_improve_skill("kuihua-mogong"))
              me->improve_skill("kuihua-mogong", 1500000);
        me->improve_skill("martial-cognize", 1500000);

        set("can_perform/kuihua-mogong/tian", 1, me);
        tell_object(me, HIG "你學會了「無法無天」。\n");

        return 1;
}


mixed ask_skill5()
{
        object me = this_player();
        string msg;

        if( query("gender", me) != "無性" && !query("special_skill/guimai", me) )
        {
               command("heng");
               this_object()->kill_ob(me);
               return 1;
        }
        if( query("can_perform/kuihua-mogong/hui2", me) )
        {
               command("say 我不是已經傳了你這招嗎？怎麼又來問我！");
               return 1;
        }
        if (me->query_skill("kuihua-mogong", 1) < 320)
        {
               command("say 你葵花魔功還不夠嫻熟，還不快下去多加練習。");
               return 1;
        }
        if( query("max_neili", me)<4000 )
        {
               command("say 你內力修為還不足，還不快下去多加修煉。");
               return 1;
        }

        // 未學會毀天式，第一次學習
        if( !query("can_perform/kuihua-mogong/hui", me) )
        {
               command("heihei");
               msg = HIW "東方不敗對$N" HIW "説道：好，既然這樣我就傳你葵花魔功最高境「毀天滅地」！"
                     "毀天滅地分兩招，第一招「毀天式」，第二招「滅地訣」，必須要將這兩招學全方能領"
                     "悟出「毀天滅地」！現在我先傳你第一招「毀天式」，待你下去將此招運用得熟練了我"
                     "再傳你「滅地訣」。你只要在戰鬥中使用 " HIR "perform sword.hui" HIW " 並且打中"
                     "對方，該招的熟練度就會提升！\n" NOR;

               message_sort(msg, me);
               tell_object(me, HIM "東方不敗將「毀天式」的口訣告訴了你！\n" NOR);
               command("say 下去好好練習吧！");
               tell_object(me, HIG "你學會了「毀天式」。\n" NOR);
               set("can_perform/kuihua-mogong/hui", 1, me);
               if (me->can_improve_skill("force"))
                    me->improve_skill("force", 1500000);
               if (me->can_improve_skill("kuihua-mogong"))
                    me->improve_skill("kuihua-mogong", 1500000);
               me->improve_skill("martial-cognize", 1500000);
               
               return 1;
               
        }
        else // 準備學習滅地訣
        {
               if( query("can_perform/kuihua-mogong/hui1", me)<200 )
               {
                      command("shake");
                      command("say 你還是先將「毀天式」運用熟練了再來吧！");
                      return 1;
               }
               command("nod");
               msg = HIW "東方不敗對$N" HIW "説道：不錯，不錯！你「毀天式」已經運用得很熟練了，該是"
                     "你學習「滅地訣」的時候了，你可看好了。猛然間東方不敗身形一晃，已沒了蹤跡，剎"
                     "那間，你只覺得地動山搖，風起雲湧，正猶豫間，東方不敗已躥至你身後，輕輕地拍了"
                     "拍你的頭。\n" NOR;

               message_sort(msg, me);
               command("say 明白了？");
               command("say 下去好好練習吧！");
               tell_object(me, HIG "你學會了「滅地訣」。\n" NOR);
               set("can_perform/kuihua-mogong/hui2", 1, me);
               if (me->can_improve_skill("force"))
                    me->improve_skill("force", 1500000);
               if (me->can_improve_skill("kuihua-mogong"))
                    me->improve_skill("kuihua-mogong", 1500000);
               me->improve_skill("martial-cognize", 1500000);
               
               return 1;
        }
}

mixed ask_skill6()
{
        object me = this_player();
        
        if( query("gender", me) != "無性" && !query("special_skill/guimai", me) )
        {
               command("heng");
               this_object()->kill_ob(me);
               return 1;
        }
        if( query("can_perform/kuihua-mogong/fenshen", me) )
        {
               command("say 我不是已經傳了你這招嗎？怎麼又來問我！");
               return 1;
        }
        if (me->query_skill("kuihua-mogong", 1) < 460)
        {
               command("say 你葵花魔功還不夠嫻熟，還不快下去多加練習。");
               return 1;
        }
 	if( query("max_neili", me)<6000 )
	{
                command("say 你內力修為不夠，無法領會此招。\n");
		return 1;
	}
        command("heihei");
        command("say 看好了！");
        tell_object(me, HIR "\n東方不敗冷笑一聲，幻化出無數的身影，令你眼花繚亂，不明方向。\n" NOR);
        command("say 明白了？");

        if (me->can_improve_skill("force"))
              me->improve_skill("force", 1500000);
        if (me->can_improve_skill("dodge"))
              me->improve_skill("dodge", 1500000);
        if (me->can_improve_skill("kuihua-mogong"))
              me->improve_skill("kuihua-mogong", 1500000);
        me->improve_skill("martial-cognize", 1500000);

        set("can_perform/kuihua-mogong/fenshen", 1, me);
        tell_object(me, HIG "你學會了「分身化影」。\n");

        return 1;
}

void unconcious()
{
        ::die();
}