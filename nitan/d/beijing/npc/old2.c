//keeper.c
//updated by rama

inherit NPC;
#include <ansi.h>

int ask_hbd(object me, object ob);

void create()
{
        set_name("老漢", ({ "old man", "old", "man" }) );
        set("gender", "男性" );
        set("age", 63);
        set("shen_type", 1);
        set("combat_exp", 10000);
        set("str", 20);
        set("dex", 20);
        set("con", 20);
        set("int", 20);
        set("attitude", "peaceful");
        set("inquiry",([  
                "黑白道" : (: ask_hbd :),  
                               ]) );  
        setup();
        carry_object("/d/beijing/npc/obj/cloth")->wear();
}

int ask_hbd(object me, object ob) 
{ 
     me=this_player(); 
     ob=this_object(); 
     ob=this_object(); 
     if( query("bunch/bunch_name", me) != "黑白道" && query("shen", me) <= 0 )
     { 
           command("whisper"+query("id", me)+"兄弟是想加入咱們黑白道的吧！隨我來吧！");
           tell_object(me,HIB"老漢帶你到了後院，移開一塊石板，你順着石階走了下去。\n"NOR);
           message("vision", me->name() + "帶着老漢急急忙忙的走了。\n", 
                              environment(me), ({me}) ); 
           me->move("/d/beijing/hbd_bjzb");
           return 1; 
     } 
     if( good_bunch(me) || query("shen", me)>0 )
     { 
           command("say 客官，我不明白你的意思。\n"); 
           return 1; 
     } 

     tell_object(me,"老漢説道：“既然是本幫兄弟，就隨我來吧！”\n");
     me->move("/d/beijing/hbd_bjzb"); 
     return 1; 
} 
