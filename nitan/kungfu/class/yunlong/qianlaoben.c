// qianlaob.c
#include <ansi.h>

inherit NPC;
inherit F_BANKER;
int ask_weiwang();

void create()
{
        set_name("錢老本", ({"qian laoben", "qian", "laoben"}));
        set("title", HIR "天地會"HIG"青木堂"NOR"會眾");
        set("gender", "男性");
        set("age", 34);

        set("str", 22);
        set("int", 24);
        set("dex", 18);
        set("con", 18);

        set("qi", 800); 
        set("max_qi", 800);
        set("jing", 500);
        set("max_jing", 500);
        set("neili", 800); 
        set("max_neili", 800);
        set("jiali", 20);
        set("shen", 0);

        set("no_get", 1);
        set("combat_exp", 50000);
        set("shen_type", 1);
        set("attitude", "friendly");
        set("env/wimpy", 50);
        set("chat_chance", 5);
        set("chat_msg", ({
                "錢老本說道：我叫錢老本，就是因為做生意連老本也賠了。\n",
                "錢老本笑著說道：在本店存錢利息至少百分之一，客官您只管存吧。\n",
                "錢老本說：只有對本派弟子我才這麼客氣，對別的人啊，哼哼......\n",
                "錢老本突然說道: 江湖威望很重要，威望值高大有好處啊。\n",
                "錢老本突然說：五人分開一首詩，身上洪英無人知。\n",
        }));
        set("inquiry", ([
                "利息" : "想要利息先入會！\n",
                "陳近南" : "想見總舵主可沒那麼容易。\n",
                "天地會" : "只要是英雄好漢，都可以入我天地會(join tiandihui)。\n",
                "加入" : "只要入了我天地會，可以向會中各位好手學武藝。\n",
                "入會" : "只要入了我天地會，可以向會中各位好手學武藝。\n",
                "威望" : (: ask_weiwang :),
                "江湖威望" : (: ask_weiwang :),
        ]) );

        set_skill("unarmed", 50);
        set_skill("dodge", 50);
        set_temp("apply/attack", 100);
        set_temp("apply/defense", 100);
        set_temp("apply/damage", 40);

        setup();
        carry_object("/clone/misc/cloth")->wear();
        add_money("gold", 5);
}

void init()
{
        add_action("do_check", "check");
        add_action("do_check", "chazhang");
        add_action("do_convert", "convert");
        add_action("do_convert", "duihuan");
        add_action("do_deposit", "deposit");
        add_action("do_deposit", "cun");
        add_action("do_withdraw", "withdraw");
        add_action("do_withdraw", "qu");
        delete_temp("busy");
}

int ask_weiwang()
{
        command("tell"+query("id", this_player())+"你現在的江湖威望是"+(query("weiwang", this_player())));
        say( "錢老本說：如果你威望值很高，有些人見了你不但不會殺你，還會教你武功，送你寶貝。\n而且你還可以加入幫會，率領會眾去攻打目標，就連去錢莊取錢也會有利息 。。。。。\n");
        say("錢老本又說：殺某些壞人或救某些好人可以提高江湖威望。\n");
        return 1;
}
