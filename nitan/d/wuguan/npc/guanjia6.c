inherit NPC;
#include <ansi.h>

void create()
{
        set_name("菜園管事", ({ "caiyuan guanshi", "guanshi" }) );
        set("gender", "男性" );
        set("age", 50);
        set("long", "他是菜園管事，專管菜園裏大小雜事！\n");
        set("combat_exp", 2500);
        set("attitude", "friendly");
        set("inquiry", ([
        	"澆水" : "你就在這老老實實給我澆水，沒有我的滿意，你別想回去覆命！",
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
         
        if( query_temp("job_name", ob) != "澆菜地")return ;

        if (! (present("shui piao", ob)))
        {
        	command("hmm"+query("id", ob));
        	command("say 你還沒領工具吧，去東物品房找武爺要了再來。\n");
        	return;
        }

        if( !(query_temp("job_name", ob) != "澆菜地") )
        {
        	command("nod"+query("id", ob));
                command("say 是耶律大爺吩咐你來的吧？那你就在這澆水(" HIY
                        "jiao shui" NOR + CYN ")好了。\n" NOR);
        }
}