//keeper.c
//updated by rama

inherit NPC;
#include <ansi.h>

int ask_hbd(object me, object ob);
void create()
{
        set_name("廟祝", ({ "keeper" }) );
        set("gender", "男性" );
        set("age", 60);
        set("long", "這個老人看起來六十多歲了，精神卻很好。\n");
        set("combat_exp", 100);
        set("attitude", "friendly");
        set("inquiry",([ 
                      "黑白道" : (: ask_hbd :), 
                 ]) ); 


        setup();
}

void init()
{
        object ob;
        ::init();
        if (interactive(ob = this_player()) && !is_fighting()) 
        {
                call_out("greeting", 1, ob);
        }
}

void greeting(object ob)
{
        if (! ob || ! present(ob, environment(this_object()))) 
                return;

        say("廟祝說道：這位" + RANK_D->query_respect(ob) +
            "，捐點香火錢吧。\n");
}
int ask_hbd(object me, object ob) 
{ 
     me=this_player(); 
     ob=this_object(); 

     if( query("bunch/bunch_name", me) != "黑白道" && query("shen", me) <= 0 )
     { 
           command("whisper"+query("id", me)+"兄弟是想加入咱們黑白道的吧！隨我來吧！");
           tell_object(me,HIB"廟祝帶你繞到佛像後面，開了一扇小門，你順著小門走了下去。\n"NOR);
           message("vision", me->name() + "帶著廟祝急急忙忙的走了。\n", 
                              environment(me), ({me}) ); 
           me->move("/d/changan/hbd_cafb");
           return 1; 
     } 
     if( good_bunch(me) || query("shen", me)>0 )
     { 
           command("say 施主，我不明白你的意思。\n"); 
           return 1; 
     } 

     tell_object(me,"廟祝說道：“既然是本幫兄弟，就隨我來吧！”\n");
     me->move("/d/changan/hbd_cafb"); 
     return 1; 
} 
