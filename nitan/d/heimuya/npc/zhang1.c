// zhang1.c
#include <ansi.h>
inherit NPC;

int shang_ya();
void create()
{
    set_name("張乘風", ({"zhang chengfeng", "zhang", "chengfeng"}));
    set("nickname", HIY "金猴神魔" NOR );
    set("title", "日月神教長老");
    set("gender", "男性");
    set("age", 42);
    set("shen_type", -1);
    set("long",
        "他是日月神教長老。\n");
    set("attitude", "peaceful");

    set("per", 21);
    set("str", 30);
    set("int", 30);
    set("con", 30);
    set("dex", 30);

    set("qi", 3000);
    set("max_qi", 3000);
    set("jing", 1000);
    set("max_jing", 1000);
    set("neili", 3000);
    set("max_neili", 3000);
    set("jiali", 300);

    set("combat_exp", 1500000);
    set("score", 0);
    set("inquiry", ([
        "黑木崖" : "本教弟子或持教主令牌方能上崖！\n",
        "日月神教" : "本教弟子或持教主令牌方能上崖！\n",
        "日月教" : "本教弟子或持教主令牌方能上崖！\n",
        "黑木令" : "那是本教教主令牌，見牌如見教主親臨！\n",
        "上崖" :   (: shang_ya :),
    ]) );

    set_skill("force", 150);
    set_skill("kuihua-xinfa", 150);
    set_skill("unarmed", 150);
    set_skill("changquan", 150);
    set_skill("dodge", 150);
    set_skill("lingxu-bu", 150);
    set_skill("parry", 150);
    set_skill("club", 150);
    set_skill("weituo-gun", 150);

    map_skill("force", "kuihua-xinfa");
    map_skill("club", "weituo-gun");
    map_skill("parry", "weituo-gun");
    map_skill("unarmed", "changquan");
    map_skill("dodge", "lingxu-bu");

    create_family("日月神教", 2, "長老");

    setup();
    carry_object("/d/heimuya/npc/obj/shutonggun")->wield();
    carry_object("/clone/misc/cloth")->wear();
}

int shang_ya()
{
    object ob, myenv ;
    ob = this_player ( ) ;
    if( query("family/family_name", ob) == "日月神教" )
    {
        message_vision("張乘風一招手，崖上落下一個大吊籃。\n",ob);
        message_vision("$N一彎腰進了吊籃，吊籃緩緩地鉸上崖去......\n", ob);
        myenv = environment (ob) ;
        ob->move ("/d/heimuya/basket");
        call_out("goto_heimuya", 3, ob) ;
               return 1;
    }
    else  
    message_vision("張乘風上上下下打量了$N一下：什麼！上崖？你的黑木令呢？！\n",ob);
    return 1;
}

int accept_object(object who, object ob)
{
    object myenv ;
    if( query("id", ob) == "heimuling" )
    {
        message_vision("張乘風對$N說：好！這位" + RANK_D->query_respect(who) + "不錯，那就請吧！\n" , who);
        message_vision("張乘風一招手，崖上落下一個大吊籃。\n", who);
        message_vision("$N一彎腰進了吊籃，吊籃緩緩地鉸上崖去......\n", who);
        myenv = environment (who) ;
        who->move ("/d/heimuya/basket");
        call_out("goto_heimuya",10,who) ;
        destruct(ob);
               return 1;
    }
    else  
    {
        message_vision("張乘風對$N說：你敢耍我？！\n", who);
        this_object()->kill_ob(who);
    }
    return 0;
}

void goto_heimuya (object ob)
{
    if (! ob) return;
    tell_object(ob , "你眼前一亮，一幢幢白色建築屹立眼前，霎是輝煌。\n");
    ob->move ("/d/heimuya/chengdedian") ;
}
