#include <ansi.h>
inherit NPC;
inherit F_UNIQUE;
int ask_weiwang();

void create()
{
        set_name("徐天川", ({ "xu tianchuan", "xu", "tianchuan" }));
        set("title", HIR "天地會"HIG"青木堂"NOR"護法");
        set("nickname", "八臂猿猴");
        set("gender", "男性");
        set("long", "\n他是青木堂數一數二的好手，手上功夫十分了得，尤其擅使一套猴拳。\n");
        set("age", 55);

        set("int", 30);
        
        set("qi", 500);
        set("max_qi", 500);
        set("jing", 500);
        set("max_jing", 500);
        set("shen_type", 1);

        set("combat_exp", 75000);
        set("attitude", "friendly");

        set_skill("force", 70);
        set_skill("dodge", 70);
        set_skill("parry", 90);
        set_skill("unarmed", 90);
        set_skill("hand", 100);
        set_skill("hunyuan-yiqi", 70);
        set_skill("shaolin-shenfa", 70);
        set_skill("houquan", 100);

        set_temp("apply/attack", 50);
        set_temp("apply/defense", 50);
        set_temp("apply/damage", 35);
        set("env/wimpy", 50);

        map_skill("force", "hunyuan-yiqi");
        map_skill("dodge", "shaolin-shenfa");
        map_skill("hand", "houquan");
        map_skill("unarmed", "houquan");
        map_skill("parry", "houquan");

        set("chat_chance", 3);
        set("chat_msg", ({
        "徐天川想了想，說：有人想要進出皇宮，我得想個法子才好啊。\n",
        "徐天川說道: 江湖威望很重要，威望值高大有好處啊。\n",
        "徐天川突然說：自此傳得眾兄弟，後來相認團圓時。\n",
        "徐天川突然說：初進洪門結義兄，對天明誓表真心。\n",
        }));

        set("inquiry", ([
                "陳近南" :  "\n想見總舵主可不容易啊。\n",
                "天地會" :  "\n只要是英雄好漢，都可以入我天地會(join tiandihui)。\n",
                "加入" :  "\n只要入了我天地會，大家就可以一起反青復明。\n",
                "入會" :  "\n只要入了我天地會，大家就可以一起反青復明。\n",
                "威望" :  (: ask_weiwang :),
                "江湖威望" : (: ask_weiwang :),
        ]) );

        setup();
        carry_object("/clone/misc/cloth")->wear();
        add_money("silver", 50);
}

void init()
{
        ::init();
        add_action("do_join","join");
}

int ask_weiwang()
{
command("tell"+query("id", this_player())+"你現在的江湖威望是"+(query("weiwang", this_player())));
say("\n徐天川說：如果你威望值很高，有些人見了你不但不會殺你，還會教你武功，送你寶貝。\n"
+"而且你還可以加入幫會，率領會眾去攻打目標，就連去錢莊取錢也會有利息。\n");
say("徐天川又說：殺某些壞人或救某些好人可以提高江湖威望。\n");
return 1;
}

int recognize_apprentice(object ob)
{
            return 1;
}

int prevent_learn(object me,string skill)
{
if (skill!="houquan") {return 1;} 
  else {return 0;} 
}

#include "/kungfu/class/yunlong/tiandihui.h";
