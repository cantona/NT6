// xutianch.c 徐天川

#include <ansi.h>
inherit NPC;

int ask_weiwang();

void create()
{
        set_name("徐天川", ({ "xu tianchuan", "xu", "tianchuan" }));
        set("nickname", "八臂猿猴");
        set("gender", "男性");
        set("long","他是青木堂數一數二的好手，手上功夫十分了得，尤其擅使一套猴拳。\n");
        set("age", 55);
        set("int", 30);
        set("qi", 1000);
        set("max_qi", 1000);
        set("jing", 500);
        set("max_jing", 500);
        set("neili", 1500);
        set("max_neili", 1500);
        set("jiali", 100);
        set("shen_type", 1);

        set("combat_exp", 75000);
        set("attitude", "friendly");

        set_skill("force", 70);
        set_skill("dodge", 70);
        set_skill("parry", 90);
        set_skill("unarmed", 90);
        set_skill("yunlong-shengong", 70);
        set_skill("yunlong-shenfa", 70);
        set_skill("houquan", 100);

        set_temp("apply/attack", 50);
        set_temp("apply/defense", 50);
        set_temp("apply/damage", 35);
        set("env/wimpy", 50);

        map_skill("force", "yunlong-shengong");
        map_skill("dodge", "yunlong-shenfa");
        map_skill("hand", "houquan");
        map_skill("unarmed", "houquan");
        map_skill("parry", "houquan");

        set("chat_chance", 3);
        set("chat_msg", ({
                "徐天川想了想，説：有人想要進出皇宮，我得想個法子才好啊。\n",
                "徐天川説道: 江湖威望很重要，威望值高大有好處啊。\n",
                "徐天川突然説：自此傳得眾兄弟，後來相認團圓時。\n",
                "徐天川突然説：初進洪門結義兄，對天明誓表真心。\n",
        }));

        set("inquiry", ([
                "陳近南" : "想見總舵主可不容易啊。\n",
                "天地會" : "只要是英雄好漢，都可以入我天地會(join tiandihui)。\n",
                "入會" : "只要入了我天地會，可以向會中各位好手學武功。\n",
                "威望" : (: ask_weiwang :),
                "江湖威望" : (: ask_weiwang :),
                "去清復明膏" : "去藥鋪內室裏仔細瞧瞧吧！\n",
                "去清復明" : "去藥鋪內室裏仔細瞧瞧吧！\n",
                "反清復明" : "去藥鋪內室裏仔細瞧瞧吧！\n",
                "暗號" : "敲三下！\n",
                "切口" : "敲三下！\n",
        ]) );
        set("party/party_name", "天地會");
        set("party/rank", HIG"青木堂"NOR"護法");
        create_family("雲龍門", 2, "弟子");

        setup();
        carry_object("/clone/misc/cloth")->wear();
        add_money("gold", 5);
}

void init()
{
        ::init();
        add_action("do_skills","skills");
        add_action("do_skills","cha");
        add_action("do_join","join");
}

int ask_weiwang()
{
command("tell"+query("id", this_player())+"你現在的江湖威望是"+(query("weiwang", this_player())));
say("\n徐天川説：如果你威望值很高，有些人見了你不但不會殺你，還會教你武功，送你寶貝。\n"
+"而且你還可以加入幫會，率領會眾去攻打目標，就連去錢莊取錢也會有利息 。。。。。\n");
say("徐天川又説：殺某些壞人或救某些好人可以提高江湖威望。\n");
return 1;
}

int recognize_apprentice(object ob)
{
        if( query("weiwang", ob)<50 )
        {
                message_vision("$N搖了搖頭。\n",this_object());
                command("tell"+query("id", ob)+"不是天地會弟子我不教。\n");
        }
        return 1;
}
#include "tiandihui.h";
