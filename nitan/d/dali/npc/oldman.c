//updated by rama

inherit NPC;
#include <ansi.h>

int ask_xdh(object me, object ob);

void create()
{
        set_name("擺夷老叟",({ "old man", "old", "man" }) ); 
        set("gender", "男性" );
        set("age", 72);
        set("long", 
"一個擺夷老叟大大咧咧地坐在竹籬板舍門口，甩着三四個巴掌大的棕呂樹葉，瞧着道
上來來往往的人們，倒也快活自在。\n");
        set_temp("apply/defense", 5);
        set("combat_exp", 700);
        set("shen_type", 1);
        set("per", 13);
        set("str", 14);
        set("dex", 15);
        set("con", 16);
        set("int", 15);
        set("attitude", "friendly");
        set("inquiry",([  
                "小刀會" : (: ask_xdh :),  
                               ]) );  
        setup();
        carry_object("/clone/cloth/cloth")->wear();
}

int ask_xdh(object me, object ob) 
{ 
     me=this_player(); 
     ob=this_object(); 
     ob=this_object(); 
     if( query("bunch/bunch_name", me) != "小刀會" && query("shen", me) <= 0 )
     { 
           command("whisper"+query("id", me)+"兄弟是想加入咱們小刀會的吧！隨我來吧！");
           tell_object(me,HIB"擺夷老叟帶你到了後院，移開一塊石板，你順着石階走了下去。\n"NOR);
           message("vision", me->name() + "帶着擺夷老叟急急忙忙的走了。\n", 
                              environment(me), ({me}) ); 
           me->move("/d/dali/xdh_dlfb");
           return 1; 
     } 
     if( good_bunch(me) || query("shen", me)>0 )
     { 
           command("say 客官，我不明白你的意思。\n"); 
           return 1; 
     } 

     tell_object(me,"擺夷老叟説道：“既然是本幫兄弟，就隨我來吧！”\n");
     me->move("/d/dali/xdh_dlfb"); 
     return 1; 
} 
