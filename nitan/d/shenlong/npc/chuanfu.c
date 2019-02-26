#include <ansi.h>
inherit KNOWER;

int  chu_hai();
void goto_dao(object ob);

void create()
{
        set_name("老船伕", ({ "lao chuanfu","chuanfu","lao" }));
        set("gender", "男性");
        set("age", 56);
        set("long", @LONG
這是一個老船伕。飽經風霜的臉上透出一絲狡猾。他經常出海，以前
曾經去過神龍島。現在他擁有一艘大船可以出海。
LONG );

        set("combat_exp", 1000000);
        set("shen_type", 1);

        set("eff_qi", 2000);
        set("qi", 2000);
        set("max_neili", 1000);
        set("neili", 1000);
        set("jiali", 100);

        set_skill("force", 200);
        set_skill("unarmed", 400);
        set_skill("dodge", 200);
        set_skill("parry", 200);
        set("inquiry", ([
                "靈蛇島" : "靈蛇島上有一幫大惡人，千萬不能去！\n",
                "神龍島" : "神龍島上有一幫大惡人，千萬不能去！\n",
                "出海" :   (: chu_hai :),
        ]));

        setup();
        carry_object("/clone/misc/cloth")->wear();
 }

int chu_hai()
{
        object ob, myenv;
        ob = this_player();
        if( query("party/party_name", ob) == "神龍教" )
        {
                message_vision("老船伕一招手，叫來幾個年輕船伕。\n", ob);
                message_vision("年輕船伕和$N上了船，一聲「起錨」船就開走了，但"
                               "老船伕卻沒上船......\n", ob);
                myenv = environment (ob);
                ob->move ("/d/shenlong/dahai");
                tell_object(ob, BLU "你在海上航行了很久很久.......\n" NOR);
                call_out("goto_shenlong", 10, ob);
                return 1;
        } else  
                message_vision("老船伕上上下下打量了$N一下：什麼！出海？你"
                               "不要命了？！\n老船伕又想了一下：不過...如"
                               "果給我一兩金子，或許可以考慮。\n", ob);
        set_temp("出海", 1, ob);
        return 1;
}

int accept_object(object who, object ob)
{
        object myenv;
        if( !query_temp("出海", who) )
        {
                message_vision("老船伕笑着對$N説：無功不受祿，您"
                               "還是自己留着吧！\n", who);
                return 0;
        }
        if( query("money_id", ob) && ob->value() >= 10000 )
        {
                message_vision("老船伕對$N説：好！既然這位" +
                               RANK_D->query_respect(who) +
                               "如此看得起我，\n那我也拼上這條破船，舍"
                               "命陪君子便了！\n" , who);
                delete_temp("出海", who);
                message_vision("老船伕一招手，叫來幾個年輕船伕。\n年輕船"
                               "夫和$N上了船，一聲「起錨」船就開走了，但"
                               "老船伕卻沒上船......\n", who);
                myenv = environment (who);
                who->move("/d/shenlong/dahai");
                tell_room(myenv, "老船伕看船走了，掂着手裏的金子笑了：去"
                          "神龍島？送死的事情我可不幹。\n只可惜我那幾個"
                          "聽話的船伕，要被那幫人給吃掉了。嘿嘿，哈哈！\n");
                tell_object(who, BLU "你在海上航行了很久很久.......\n" NOR);
                call_out("goto_shenlong", 10, who);
                destruct(ob);
                return -1;
        } else  
                message_vision("老船伕皺眉對$N説：您給的也太少了吧？\n", who);
        return 0;
}

void goto_shenlong(object ob)
{
        if (! objectp(ob) || find_object("/d/shenlong/dahai") != environment(ob))
                return;

        tell_object(ob, "大船終於停在了一個小島邊。你走下船來。\n");
        ob->move("/d/shenlong/haitan");
}

void unconcious()
{
        ::die();
}