// chuanfu.c 老船夫

#include <ansi.h>
inherit NPC;

int  chu_hai();
void goto_dao(object ob);

void create()
{
          set_name("船家", ({ "chuan jia","chuan" }));
        set("gender", "男性");
        set("age", 56);
        set("long",
                "這是一個老船夫。飽經風霜的臉上透出一絲狡猾。他經常出海，以前曾經\n"
                "去過冰火島。現在他擁有一艘大船可以出海。\n",
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
                "冰火島" : "冰火島上危險重重，沒本事可不能亂闖! \n",
                "出海" :   (: chu_hai :),
        ]) );
        setup();
        carry_object("/clone/misc/cloth")->wear();
}
 
int chu_hai()
{
        object ob ;
        ob = this_player ( ) ;
        message_vision("老船夫上上下下打量了$N一下：什麼！出海？你不要命了？！\n"
                       "老船夫又想了一下：不過...如果給我一兩金子，或許可以考慮。\n",
                       ob);
        set_temp("出海", 1, ob);
        return 1;
}

int accept_object(object who, object ob)
{
        object myenv ;
        if( !query_temp("出海", who) )
        {
                message_vision("老船夫笑著對$N說：無功不受祿，您還是自己留著吧！\n", who);
                return 0 ;
        }
        if( query("money_id", ob) && ob->value() >= 10000 )
        {
                message_vision("老船夫對$N說：好！既然這位" + RANK_D->query_respect(who) +
                               "如此看得起我，\n那我也拼上這條破船，舍命陪君子便了！\n" , who);
                delete_temp("出海", this_player());
                message_vision("老船夫一招手，叫來幾個年輕船夫。\n", who);
                message_vision("年輕船夫和$N上了船，一聲「起錨」船就開走了，但老船夫卻沒上船......\n", who);
                myenv = environment (who);
                who->move ("/d/mingjiao/bhd/dahai");
                tell_room(myenv,
                        "老船夫看船走了，掂著手裡的金子笑了：去冰火島？送死的事情我可不幹。\n"
                        "只可惜我那幾個聽話的船夫，要被那幫人給吃掉了。嘿嘿，哈哈！\n") ;
                tell_object(who, BLU "你在海上航行了很久很久.......\n" NOR ) ;
                call_out("goto_shenlong", 10, who) ;
                return 1;
        }
        else  
                message_vision("老船夫皺眉對$N說：您給的也太少了吧？\n", who);
        return 0;
}

void goto_shenlong (object ob)
{
        tell_object(ob , "大船終于停在了一個小島邊。你走下船來。\n" ) ;
        ob->move ("/d/mingjiao/bhd/yanshi");
}
