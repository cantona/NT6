inherit NPC;
#include <ansi.h>

void create()
{
        set_name("馬房管事", ({ "mafang guanshi", "guanshi" }) );
        set("gender", "男性" );
        set("age", 50);
        set("long", "他是馬房管事，專管馬房裡的大小雜事！\n");
        set("combat_exp", 2500);
        set("attitude", "friendly");
        set("inquiry", ([
                "打掃" : "你就在這老老實實給我打掃馬房，沒有我的滿意，你別想回去覆命！",
        ]) );
        setup();
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

void greeting(object ob)
{
        if (! ob || environment(ob) != environment()) return;
         
        if( query_temp("job_name", ob) != "打掃馬房")return ;

        if (! (present("sao zhou", ob)))
        {
        	command("hmm"+query("id", ob));
        	command("say 你還沒領工具吧，去東物品房找武爺要了再來。\n");
        	return;
        }

        if( !(query_temp("job_name", ob) != "打掃馬房") )
        {
        	command("nod"+query("id", ob));
                command("say 是耶律大爺吩咐你來的吧？那你就在這打掃(" HIY
                        "sao mafang" NOR + CYN ")好了。\n" NOR);
        }
}