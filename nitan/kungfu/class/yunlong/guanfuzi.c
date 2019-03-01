// guanfuzi.c 關安基 

#include <ansi.h>;

inherit NPC;
inherit F_UNIQUE;
inherit F_MASTER;
int ask_weiwang();

void create()
{
        set_name("關安基", ({ "guan anji", "guan" }));
        set("nickname", "關夫子");
        set("shen_type", 1);

        set("gender", "男性");
        set("age", 35);
        set("long", "只見他長長的胡子飄在胸前，模樣甚是威嚴。因此人稱關夫子。\n");

        set("qi", 1000);
        set("max_qi", 1000);
        set("jing", 1200);
        set("max_jing", 1200);
        set("neili", 1000); 
        set("max_neili", 1000);
        set("jiali", 35);
        set_skill("force", 70);
        set_skill("dodge", 70);
        set_skill("parry", 70);
        set_skill("claw", 70);
        set_skill("hand", 70);
        set_skill("literate", 50);
        set_skill("yunlong-shengong", 80);
        set_skill("yunlong-shenfa", 80);
        set_skill("yunlong-shou", 80);
        set_skill("yunlong-zhua", 80);
        map_skill("hand", "yunlong-shou");
        map_skill("claw", "yunlong-zhua");
        map_skill("force", "yunlong-shengong");
        map_skill("dodge", "yunlong-shenfa");
        map_skill("parry", "yunlong-shou");
        prepare_skill("hand","yunlong-shou");
        prepare_skill("claw","yunlong-zhua");

        set_temp("apply/attack", 35);
        set_temp("apply/damage", 25);

        set("combat_exp", 50000);
        set("attitude", "friendly");
        set("chat_chance", 1);
        set("chat_msg", ({
                "關安基忽然說：本堂的香主誰來當，還輪不到我說話。\n",
                "關安基忽然說：唉，我的脾氣不大好，大家可要小心了。\n",
        }));
        set("inquiry", ([
                "陳近南" : "想見總舵主可不容易啊。\n",
                "天地會" : "只要是英雄好漢，都可以入我天地會(join tiandihui)。\n",
                "入會" : "只要入了我天地會，可以向會中各位好手學武藝。\n",
                "反清復明" : "去屠宰場和棺材店仔細瞧瞧吧！\n",
                "威望" : (: ask_weiwang :),
                "江湖威望" : (: ask_weiwang :),
        ]) );
        set("party/party_name", "天地會");
        set("party/rank", HIG"青木堂"NOR"會眾");
        create_family("雲龍門", 2, "弟子");

        setup();
        carry_object("/clone/misc/cloth")->wear();
        carry_object("/clone/weapon/changjian")->wield();
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

void init()
{
        add_action("do_join","join");
}

void die()
{
        message_vision("\n$N大怒道：“你敢砍老子！兄弟們會替我報仇的！”說完倒地死了。\n", this_object());
        ::die();
}

int ask_weiwang()
{
        command("tell"+query("id", this_player())+"你現在的江湖威望是"+(query("weiwang", this_player())));
        say( "\n關安基說：如果你威望值很高，有些人見了你不但不會殺你，還會教你武功，送你寶貝。\n而且你還可以加入幫會，率領會眾去攻打目標，就連去錢莊取錢也會有利息。。。。。\n");
        say("關安基又說：殺某些壞人或救某些好人可以提高江湖威望。\n");
        return 1;
}
#include "tiandihui.h";
