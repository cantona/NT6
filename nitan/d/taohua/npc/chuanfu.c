// chuanfu.c 老船伕

#include <ansi.h>


inherit NPC;

int  chu_hai();
void goto_dao(object ob);

void create()
{
        set_name("老船伕", ({ "lao chuanfu","chuanfu" }));
        set("gender", "男性");
        set("age", 56);
        set("long",
        "這是一個老船伕。飽經風霜的臉上透出一絲狡猾。他經常出海，以前曾經\n"
        "去過桃花島。現在他擁有一艘大船可以出海。\n",
            );

        set("combat_exp", 1000000);
        set("shen_type", 1);

        set("eff_qi",2000);
        set("qi",2000);
        set("max_neili", 1000);
        set("neili", 1000);
        set("jiali", 100);

        set_skill("force", 200);
        set_skill("unarmed", 400);
        set_skill("dodge", 200);
        set_skill("parry", 200);
        set("inquiry", ([
                
                "桃花島" : "桃花島上是一羣妖魔！不過有個小妖女很美麗，嘖嘖！\n",
                "出海" :   (: chu_hai :),

        ]) );

        setup();
        carry_object("/clone/misc/cloth")->wear();
 }

int chu_hai()
{
  object ob, myenv;
  ob = this_player ( ) ;
  if( query("family/family_name", ob) == "桃花島" )
  {
        message_vision("老船伕一招手，叫來幾個年輕船伕。\n",ob);
        message_vision("年輕船伕和$N上了船，一聲「起錨」船就開走了，但老船伕卻沒上船......\n", ob);
        myenv = environment (ob) ;
        ob->move ("/d/taohua/dahai");
        tell_object(ob, BLU "你在海上航行了很久很久.......\n" NOR ) ;
        call_out("goto_taohua",10,ob) ;
               return 1;
  }
  else  
  message_vision("老船伕上上下下打量了$N一下：什麼！出海？你不要命了？！\n"
                 "老船伕又想了一下：不過...如果給我一兩金子，或許可以考慮。\n"
                 ,ob);
  set_temp("出海", 1, ob);
  return 1;
}

int accept_object(object who, object ob)
{
    object myenv ;
    if( !query_temp("出海", who) )
    {
        message_vision("老船伕笑着對$N説：無功不受祿，您還是自己留着吧！\n", who);
        return 0 ;
    }
    if( query("money_id", ob) && ob->value() >= 10000){
        message_vision("老船伕對$N説：好！既然這位" + RANK_D->query_respect(who) +
        "如此看得起我，\n那我也拼上這條破船，捨命陪君子便了！\n" , who);
        delete_temp("出海", this_player());
        message_vision("老船伕一招手，叫來幾個年輕船伕。\n", who);
        message_vision("年輕船伕和$N上了船，一聲「起錨」船就開走了，但老船伕卻沒上船......\n", who);
        myenv = environment (who) ;
        who->move ("/d/taohua/dahai");
        tell_room(myenv,
        "老船伕看船走了，掂着手裏的金子笑了：去桃花島？送死的事情我可不幹。\n"
        "只可惜我那幾個聽話的船伕，要被那幫人給吃掉了。嘿嘿，哈哈！\n") ;
        tell_object(who, BLU "你在海上航行了很久很久.......\n" NOR ) ;
        call_out("goto_taohua",10,who) ;
               return 1;
        }
    else  
        message_vision("老船伕皺眉對$N説：您給的也太少了吧？\n", who);
        return 0;
}

void goto_taohua (object ob)
{
        if (base_name(environment(ob)) != "/d/taohua/dahai")
                return;
   tell_object(ob , "大船終於停在了一個小島邊。你走下船來。\n" ) ;
   ob->move ("/d/taohua/haitan") ;
}