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

        set("qi", 500); 
        set("max_qi", 500);
        set("jing", 100);
        set("max_jing", 100);
        set("shen", 0);

        set("combat_exp", 50000);
        set("shen_type", 1);
        set("attitude", "friendly");
        set("env/wimpy", 50);

        set("inquiry", ([
                "利息" :  "\n想要利息先入會！\n",
                "陳近南" :  "\n想見總舵主可沒那麼容易。\n",
                "天地會" :  "\n只要是英雄好漢，都可以入我天地會(join tiandihui)。\n",
                "加入" :  "\n只要入了我天地會，大家就可以一起反青復明。\n",
                "入會" :  "\n只要入了我天地會，大家就可以一起反青復明。\n",
                "威望" :  (: ask_weiwang :),
                "江湖威望" : (: ask_weiwang :),
       ]) );

        set_skill("unarmed", 50);
        set_skill("dodge", 50);
        set_temp("apply/attack", 100);
        set_temp("apply/defense", 100);
        set_temp("apply/damage", 40);

        setup();
        carry_object("/clone/misc/cloth")->wear();
        add_money("silver", 50);
}

int ask_weiwang()
{
        command("tell"+query("id", this_player())+"你現在的江湖威望是"+
                (query("weiwang", this_player())));
        say("\n錢老本說：如果你威望值很高，有些人見了你不但不會殺你，還會教你武功，送你寶貝。\n"
            "而且你還可以加入幫會，率領會眾去攻打目標，就連去錢莊取錢也會有利息 。。。。。\n");
        say("錢老本又說：殺某些壞人或救某些好人可以提高江湖威望。\n");

        return 1;
}

#include "/kungfu/class/yunlong/tiandihui.h"
