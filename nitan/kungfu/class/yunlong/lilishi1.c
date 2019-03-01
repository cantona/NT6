// lilishi.c 李力世

#include <ansi.h>

inherit NPC;
inherit F_UNIQUE;
inherit F_MASTER;
int ask_weiwang();
int ask_zhu();
int do_skills(string arg);

void create()
{
        set_name("李力世", ({ "li lishi", "li" }));
        set("title", HIR "天地會"HIG"青木堂"NOR"會眾");
        set("gender", "男性");
        set("age", 45);
        set("str", 25);
        set("dex", 20);
        set("long", "這是一個身材矮小，滿連胡須的中年人，身上的\n"+
"衣服又臟又破，臉上滿是皺紋，看上去飽經風霜。\n");
        set("combat_exp", 35000);
        set("score", 5000);
        set("shen_type", 1);
        set("attitude", "peaceful");
        set_skill("unarmed", 50);
        set_skill("force", 60);
        set_skill("blade", 90);
        set_skill("dodge", 70);
        set_skill("parry", 50);
        set_skill("wuhu-duanmendao", 90);
        set_skill("yunlong-shenfa", 60);
        map_skill("blade", "wuhu-duanmendao");
        map_skill("dodge", "yunlong-shenfa");

        set("qi", 800);
        set("max_qi", 800);
        set("jing", 1000);
        set("max_jing", 1000);
        set("neili", 800); 
        set("max_neili", 800);
        set("jiali", 10);
        set("chat_chance", 2);
        set("chat_msg", ({
        "李力世說：呆會兒我還得把豬送到宮裡去。\n",
        "李力世突然吆喝道: 花雕芙苓豬啊，只賣黃金一兩，誰買誰買啊？\n",
        "李力世突然吆喝道: 燕窩人參豬啊，只賣黃金一兩，誰買誰買啊？\n",
        "李力世搔了搔頭，說道：這麼好的豬肉怎麼沒人要啊。\n",
        "李力世突然說：初進洪門結義兄，對天明誓表真心。\n",
        }));
        set("inquiry", ([
                "陳近南" :  "\n想見總舵主可不容易啊。\n",
                "天地會" :  "\n只要是英雄好漢，都可以入我天地會(join tiandihui)。\n",
                "入會" :  "\n只要入了我天地會，可以向會中各位好手學武藝。\n",
                "反清復明" : "去棺材店和回春堂仔細瞧瞧吧！\n",
                "暗號" : "敲三下！\n",
                "切口" : "敲三下！\n",
                "進宮" : (: ask_zhu :),
                "花雕芙苓豬" : (: ask_zhu :),
                "燕窩人參豬" : (: ask_zhu :),
                "威望" :  (: ask_weiwang :),
                "江湖威望" : (: ask_weiwang :),
        ]) );
        setup();
        carry_object(CLOTH_DIR"male-cloth")->wear();
        carry_object(CLOTH_DIR"male-shoe")->wear();
        carry_object(__DIR__"obj/tudao")->wield();
        add_money("silver", 20);
}

int accept_object(object who, object ob)
{
        if( query("money_id", ob) && ob->value() >= 10000 )
        {
                message_vision("\n李力世對$N一揖作禮，說道：這位客官，要什麼盡管說。\n",this_player());
                set_temp("money_paid", 1, who);
                return 1;
        }
        return 0;
}

int ask_weiwang()
{
command("tell"+query("id", this_player())+"你現在的江湖威望是"+(query("weiwang", this_player())));
say("\n李力世說道：如果你威望值很高，有些人見了你不但不會殺你，還會教你武功，送你寶貝。\n"
+"而且你還可以加入幫會，率領會眾去攻打目標，就連去錢莊取錢也會有利息 。。。。。\n");
say("李力世說：殺某些壞人或救某些好人可以提高江湖威望。\n");
return 1;
}


int ask_zhu()
{
if( query_temp("money_paid", this_player()) )
{
delete_temp("money_paid", this_player());
set("huanggong\\canenter", 1, this_player());
say("李力世說：您老現在可以走啦！\n");
return 1;
}
say("李力世說：幹什麼也得先交錢啊。\n");
return 1;
} 


void init()
{
::init();
add_action("do_skills","skills");
add_action("do_skills","cha");
add_action("do_join","join");
}

int recognize_apprentice(object ob)
{
    if( query("weiwang", ob)<50 )
    {
    message_vision("$N搖了搖頭。\n",this_object());
    command("tell"+query("id", ob)+"不是天地會弟子我不教。\n");
    return 0;
    }
        return 1;
}

int do_skills(string arg)
{
        object ob ;
        ob = this_player () ;
        if( !arg || arg!="li" )
                return 0;
        if(wizardp(ob))  return 0;
        if( query("party/party_name", ob) != "天地會" )
        {
                message_vision("$N搖了搖頭。\n",this_object());
                command("tell"+query("id", ob)+"不是天地會弟子不能察看。\n");
                return 1;
        }
    command("tell"+query("id", ob)+"我所有的武功如下：\n"+
"  基本刀法 (blade)                         - 一代宗師  90/    \n"+
"  基本輕功 (dodge)                         - 神乎其技  60/    \n"+
"  基本內功 (force)                         - 神乎其技  60/    \n"+
"  基本招架 (parry)                         - 出類拔萃  50/    \n"+
"  基本拳腳 (unarmed)                       - 出類拔萃  50/    \n"+
"□雲龍身法 (yunlong-shenfa)                - 神乎其技  60/    \n"+ 
"□五虎斷門刀 (wuhu-duanmendao)             - 一代宗師  90/    \n");
   return 1;
}
#include "/kungfu/class/yunlong/tiandihui.h";
