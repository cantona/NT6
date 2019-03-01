inherit NPC;
#include <ansi.h>

void create()
{
        set_name("柴房管事", ({ "chaifang guanshi", "guanshi" }) );
        set("gender", "男性" );
        set("age", 50);
        set("long", "他是柴房管事，專管柴房！\n");
        set("combat_exp", 2500);
        set("attitude", "friendly");
        set("inquiry", ([
             	"劈柴" : "你就在這老老實實劈柴，我不滿意，你就別想回去覆命！",
               
        ]) );
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

void greeting(object ob)
{
        if (! ob || environment(ob) != environment()) return;
         
        if( query_temp("job_name", ob) != "劈柴")return ;

        if (! (present("chai dao", ob)))
        {
        	command("hmm"+query("id", ob));
        	command("say 你還沒領工具吧，去東物品房找武爺要了再來。\n");
        	return;
        }

        if( !(query_temp("job_name", ob) != "劈柴") )
        {
        	command("nod"+query("id", ob));
                command("say 是耶律大爺吩咐你來的吧？那你就在這劈柴(" HIY
                        "pi chai" NOR + CYN ")好了。\n" NOR);
        }
}