#include <ansi.h>
inherit NPC;

string give_tools();

void create()
{
        set_name("武修文", ({"wu xiuwen", "wu", "xiuwen"}));
        set("title", HIY "郭靖二弟子" NOR);
        set("gender", "男性");
        set("age", 21);
        set("long", "他是郭靖的二弟子，精明強幹，專門負責後勤。\n");
        set("attitude", "peaceful");
        set("shen_type", 1);
        set("per", 24);
        set("str", 20);
        set("int", 20);
        set("con", 30);
        set("dex", 25);

        set("max_qi", 3000);
        set("max_jing", 2500);
        set("neili", 2800);
        set("max_neili", 2800);
        set("jiali", 50);
        set("combat_exp", 400000);
        set("score", 20000);
         
        set_skill("force", 160);
        set_skill("yijin-duangu", 160);
        set_skill("dodge", 160);
        set_skill("shexing-lifan", 160);
        set_skill("finger", 160);
        set_skill("sun-finger", 160);
        set_skill("sword", 160);
        set_skill("yuenv-jian", 160);
        set_skill("parry", 160);
        set_skill("literate", 140);
        set_skill("jingluo-xue", 160);
        set_skill("martial-cognize", 140);

        map_skill("force", "yijin-duangu");
        map_skill("dodge", "shexing-lifan");
        map_skill("finger", "sun-finger");
        map_skill("sword", "yuenv-jian");
        map_skill("parry", "jinyuan-gun");

        prepare_skill("finger", "sun-finger");

        create_family("郭府", 2, "弟子");

        set("inquiry", ([
                "黃蓉" : "那是我師母。",
                "郭靖" : "那是我師父。",
                "工具" : (: give_tools :),
                "tools" : (: give_tools :),
        ]));

        set("chat_chance_combat", 120);
        set("chat_msg_combat", ({
                (: perform_action, "finger.qian" :),
                (: perform_action, "finger.dian" :),
                (: perform_action, "dodge.gui" :),
                (: perform_action, "powerup" :),
                (: exert_function, "recover" :),
        }));

        setup();
        carry_object("/clone/misc/cloth")->wear();
}

void init()
{
        object ob;

        ::init();
        if (interactive(ob = this_player()) && ! is_fighting())
	{
                remove_call_out("greeting");
                call_out("greeting", 1, ob);
        }
}
	
string give_tools()
{
       	object tools, ob, me;

       	me = this_object();
       	ob = this_player();

       	if( query_temp("mark/工具", ob) )
		return "我不是已經給你了嗎，怎麼那麼羅嗦？";

       	if( query_temp("mark/還了", ob) )
		return "你還是先到耶律師兄那覆命了再說吧。";

       	if( !((query_temp("job_name", ob) == "鋸木頭" )
	 || (query_temp("job_name", ob) == "鋤草" )
            || (query_temp("job_name", ob) == "澆菜地" )
	 || (query_temp("job_name", ob) == "劈柴" )
	 || (query_temp("job_name", ob) == "打掃馬房")) )
             	return "你又沒有領工作，跑來要什麼工具？";

       	if( query_temp("job_name", ob) == "鋤草" )
		tools = new("/d/wuguan/obj/chutou");
       	else
	if( query_temp("job_name", ob) == "澆菜地" )
		tools = new("/d/wuguan/obj/piao");
        else
	if( query_temp("job_name", ob) == "鋸木頭" )
		tools = new("/d/wuguan/obj/juzi");
        else
	if( query_temp("job_name", ob) == "劈柴" )
		tools = new("/d/wuguan/obj/chaidao");
        else
		tools = new("/d/wuguan/obj/saozhou");

        tools->move(this_player());

        message_vision(HIC "$N" HIC "交給$n" HIC "一把工具。\n"
                       NOR, me, ob);
        set_temp("mark/工具", 1, ob);
        return "東西交給你了，可要小心保管，別弄丟了。";
}

int accept_object(object me, object obj)
{
      	object ob;
      	me = this_object();
      	ob = this_player();

      	if( !(query_temp("mark/劈完了", ob )
	 || query_temp("mark/澆完了", ob )
	 || query_temp("mark/鋤完了", ob )
	 || query_temp("mark/鋸完了", ob )
	 || query_temp("mark/掃完了", ob)) )
	{
              	command("say 你還沒完成工作，怎麼就回來還工具了，偷懶嗎？");
	      	return 0;
        }

        if( (query("id", obj) != "ju zi" )
	 && (query("id", obj) != "chu tou" )
	 && (query("id", obj) != "shui piao" )
	 && (query("id", obj) != "sao zhou" )
	 && (query("id", obj) != "chai dao") )
	{
              	command("say 你還錯東西了吧，我從沒有發過這樣工具。");
              	return 0;
        }

	if( !query_temp("job_name", ob) )
	{  
              	command("shake");
              	command("say 我沒有發給你過東西，你是不是還錯了？");
              	return 0;
        }
     	command("nod");
     	command("say 幹得不錯，你現在去耶律師兄那兒領取酬勞吧。");
        set_temp("mark/還了", 1, 	ob);
        destruct(obj);
     	return 1;
}

void greeting(object ob)
{
	if (! ob || environment(ob) != environment())
		return;

        if( query_temp("mark/劈完了", ob )
	 || query_temp("mark/澆完了", ob )
	 || query_temp("mark/鋤完了", ob )
	 || query_temp("mark/鋸完了", ob )
	 || query_temp("mark/掃完了", ob) )
	{
		command("nod "+query("id", ob));
         	command("say 你的工作做完了？那現在把工具還給我吧。");
         	return; 
        }

        if( query_temp("mark/工具", ob) )
		return 0; 

        if( (query_temp("job_name", ob) == "鋸木頭" )
	 || (query_temp("job_name", ob) == "鋤草" )
	 || (query_temp("job_name", ob) == "澆菜地" )
	 || (query_temp("job_name", ob) == "劈柴" )
	 || (query_temp("job_name", ob) == "打掃馬房") )
	{
       		command("nod "+query("id", ob));
       		command("say 你是來我這裡領工具(" HIY "ask wu xiuwen about 工具"
                        NOR + CYN ")的吧。" NOR);
       	}
}
