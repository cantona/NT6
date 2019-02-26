#include <ansi.h>

inherit NPC;
inherit F_UNIQUE;

void create()
{
        set_name("趙敏", ({ "zhao min", "min", "zhao"}));
        set("title", HIY "大元紹敏郡主" NOR);
        set("long",
"她臉泛紅霞，容色麗都。十分美麗之中，更帶着三分英氣，三分豪態，同
時雍容華貴，自有一副端嚴之姿，令人肅然起敬，不敢逼視。\n");
        set("gender", "女性");
        set("age", 15);
        set("attitude", "peaceful");
        set("shen_type", 1);
        set("per", 30);
        set("str", 15);
        set("int", 25);
        set("con", 25);
        set("dex", 30);

        set("max_qi", 500);
        set("max_jing", 200);
        set("max_neili", 500);
        set("neili", 500);
        set("jiali", 50);
        set("combat_exp", 50000+random(10000));
        set("score", 20000);
        set("chat_chance_combat", 60);
        set("chat_msg_combat", ({
                (: perform_action, "sword.ren" :),
        }) );

        set_skill("force", 80);
        set_skill("dodge", 80);
        set_skill("unarmed", 80);
        set_skill("sword", 80);
        set_skill("liangyi-jian", 80);
        set_skill("huifeng-jian", 80);
        set_skill("taiji-shengong", 90);
        set_skill("changquan", 80);
        set_skill("lingxu-bu", 80);
        map_skill("dodge", "lingxu-bu");
        map_skill("parry", "liangyi-jian");
        map_skill("sword", "liangyi-jian");
        map_skill("unarmed", "changquan");

        set("inquiry", ([
            "張無忌" :  "張公子遠在崑崙，不知他近來可好？秋冷春寒，可有寒衣？\n",
            "倚天劍" :  "倚天為天下神兵，怎麼，你想要？\n",
        ]));

        setup();
        carry_object("/clone/weapon/changjian")->wield();
        carry_object("/clone/cloth/female2-cloth")->wear();
}
void init()
{       
        object ob;
        ob = this_player();
        ::init();

        add_action("do_get","get");
        add_action("do_yun","yun");
        add_action("do_yun","exert");

        remove_call_out("greeting");
        call_out("greeting", 1, ob);
}

int do_yun(string arg)
{
        object obj;

        obj=this_object();
        if (arg == "roar" )
        {
                message_vision(CYN "\n趙敏喝道：無恥賊子，在我這兒由不得你猖狂！\n" NOR,
                                   obj);
                return 1;
        }
        return 0;

}

int do_get(string arg)
{
        object obj, env, shelf;
        string what, where;

        if(!arg) 
        return 0;

        if(sscanf(arg,"%s from %s",what, where) !=2)
        return 0;

        obj=this_object();
        if(where == "shelf")
        {
                message_vision(CYN "\n趙敏喝道：無恥賊子，休得無理！\n" NOR,
                                   obj);

                message_vision(CYN "\n趙敏輕聲哼了聲，道：要想得到倚天劍也可以，但是首先"
                                   "得比贏(bi)我的手下！\n" NOR,
                                   obj);
                return 1;
        }
        return 0;
}

int accept_fight(object who)
{
        command("say 欺負一個弱小女子算什麼，要比和我的手下比(bi)。");
        return 0;
}

int accept_hit(object who)
{
        command("say 欺負一個弱小女子算什麼，要比和我的手下比(bi)。");
        return 0;
}

int accept_kill(object who)
{
        command("say 欺負一個弱小女子算什麼，要比和我的手下比(bi)。");
        return notify_fail("剎那間你覺得無從下手。\n");
}

int accept_ansuan(object who)
{
        return notify_fail("你剛想暗算，可是隻見樓上人影晃動，根本看不清楚。\n");
}

void receive_damage(string type, int n)
{
        return;
}

void receive_wound(string type, int n)
{
        return;
}

void greeting(object ob)
{
        if( !ob || environment(ob) != environment() )
        return;

        if( !userp(ob))
        return;

        message_vision( HIW "$N一上樓來，只見一位明豔少女正座中堂，臉泛紅霞，容色麗都。十分美麗\n"+
                            "之中，更帶着三分英氣，三分豪態，同時雍容華貴，自有一副端嚴之致，令\n"+
                            "人肅然起敬，不敢逼視。少女身旁地站着幾人，衣着各異，但從幾人的神態\n"+
                            "和氣度看來，無一不是武林高手。中堂擺着一個名貴的紅木製劍架，劍架上\n"+
                            "橫放着一柄長劍，長劍的劍鞘上赫然寫着“" NOR+HIY "倚天" NOR+HIW "”二字。\n" NOR,
                            ob,this_object());

        command("yi");
        command("say 哼，今天來我這裏添亂的人還真不少！");
}
