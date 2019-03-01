// wuliuqi.c

#include <ansi.h>;

inherit NPC;
inherit F_MASTER;
inherit F_UNIQUE;
int ask_weiwang();

void create()
{
        set_name("吳六奇", ({"wu liuqi", "wu","liuqi"}));
        set("nickname", HIB"鐵丐"NOR);
        set("gender", "男性");
        set("age", 50);
        set("long", 
                "這個老叫化，便是天下聞名的“鐵丐”吳六奇，向來嫉惡如仇。\n"
                "他在官居廣東提督之時，手握一省重兵，受了查伊璜的勸導，\n"
                "心存反清復明之志，暗入天地會，任職洪順堂香主。\n"
        );

        set("attitude", "peaceful");
        
        set("str", 24);
        set("int", 20);
        set("con", 24);
        set("dex", 20);

        set("qi", 1500);
        set("max_qi", 1500);
        set("jing", 1000);
        set("max_jing", 1000);
        set("neili", 1500);
        set("max_neili", 1500);
        set("jiali", 100);
        
        set("combat_exp", 150000);
        set("score", 30000);

        set_skill("force", 120);
        set_skill("dodge", 120);
        set_skill("parry", 120);
        set_skill("claw", 120);
        set_skill("hand", 120);
        set_skill("literate", 50);
        set_skill("yunlong-shengong", 120);
        set_skill("yunlong-shenfa", 120);
        set_skill("yunlong-shou", 120);
        set_skill("yunlong-zhua", 120);
        map_skill("hand", "yunlong-shou");
        map_skill("claw", "yunlong-zhua");
        map_skill("force", "yunlong-shengong");
        map_skill("dodge", "yunlong-shenfa");
        map_skill("parry", "yunlong-shou");
        prepare_skill("hand","yunlong-shou");
        prepare_skill("claw","yunlong-zhua");

        set("chat_chance", 3);
        set("chat_msg", ({
                "吳六奇忽然放開喉嚨唱起曲來：“走江邊，滿腔憤恨向誰言？。。\n"
                "。。。。。。寒濤東卷，萬事付空煙。精魂顯大招，聲逐海天遠。\n",
                "吳六奇說: 江湖威望很重要，威望高大有好處啊。\n",
                "吳六奇突然說道: 鬆柏二枝分左右，中節洪華結義亭。\n",
                "吳六奇突然說道: 福德祠前來誓願，反清復明我洪英。\n",
        }));
        set("inquiry", ([
                "陳近南" : "想見總舵主可不容易啊。\n",
                "天地會" : "只要是英雄好漢，都可以入我天地會(join tiandihui)。\n",
                "入會" : "只要入了我天地會，可以向會中各位好手學武功。\n",
                "反清復明" : "去藥舖和棺材店仔細瞧瞧吧！\n",
                "威望" : (: ask_weiwang :),
                "江湖威望" : (: ask_weiwang :),
        ]) );
        set("party/party_name", "天地會");
        set("party/rank", HIG"洪順堂"HIC"香主"NOR);
        create_family("雲龍門", 2, "弟子");

        setup();
        carry_object("/clone/misc/cloth")->wear();
}

int ask_weiwang()
{
        command("tell"+query("id", this_player())+"你現在的江湖威望是"+(query("weiwang", this_player())));
        say( "吳六奇說：如果你威望值很高，有些人見了你不但不會殺你，還會教你武功，送你寶貝。\n而且你還可以加入幫會，率領會眾去攻打目標，就連去錢莊取錢也會有利息 。。。。。\n");
        say("\n吳六奇又說：殺某些壞人或救某些好人可以提高江湖威望。\n");
        return 1;
}

int recognize_apprentice(object ob)
{
        if( query("party/party_name", ob) != "天地會" )
        {
                message_vision("$N搖了搖頭。\n",this_object());
                command("tell"+query("id", ob)+"不是天地會弟子我不教。\n");
                return 0;
        }
        return 1;
}

void init()
{
        ::init();
        add_action("do_join","join");
}
/*
int do_skills(string arg)
{
        object ob ;
        ob = this_player () ;
        if( !arg || arg!="wu" )
                return 0;
        if(wizardp(ob))
                return 0;
        if(wizardp(ob)) return 0;
        if( query("party/party_name", ob) != "天地會" )
        {
                message_vision("$N搖了搖頭。\n",this_object());
                command("tell"+query("id", ob)+"不是天地會弟子不能察看。\n");
                return 1;
        }
        command("tell"+query("id", ob)+"我所有的武功如下：\n"+
"  叫化絕活 (begging)                       - 出類拔萃  50/   \n"+ 
"  道聽途說 (checking)                      - 出類拔萃  50/   \n"+ 
"  基本輕功 (dodge)                         - 一代宗師  90/   \n"+ 
"  基本內功 (force)                         - 一代宗師  95/   \n"+ 
"□混天氣功 (huntian-qigong)                - 一代宗師  90/   \n"+
"  基本招架 (parry)                         - 登峰造極  85/   \n"+
"  基本拳腳 (unarmed)                       - 一代宗師  90/   \n"+
"□降龍十八掌 (xianglong-zhang)             - 登峰造極  85/   \n"+
"□逍遙遊 (xiaoyaoyou)                      - 一代宗師  95/   \n");
        return 1;
}
*/
#include "tiandihui.h";
