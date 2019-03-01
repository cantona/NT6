// gaoyanchao.c 高彥超

#include <ansi.h>;

inherit NPC;
inherit F_UNIQUE;
inherit F_MASTER;
int ask_weiwang();

void create()
{
        set_name("高彥超", ({ "gao yanchao", "gao", "yanchao" }));
        set("gender", "男性");
        set("age", 32);
        set("str", 25);
        set("dex", 20);
        set("long", "他不過三十出頭，卻顯得異常老練。\n");
        set("combat_exp", 40000);
        set("score", 5000);
        set("shen_type", 1);
        set("attitude", "peaceful");

        set_skill("force", 70);
        set_skill("dodge", 70);
        set_skill("parry", 70);
        set_skill("claw", 70);
        set_skill("hand", 70);
        set_skill("literate", 50);
        set_skill("yunlong-shengong", 60);
        set_skill("yunlong-shenfa", 60);
        set_skill("yunlong-shou", 80);
        set_skill("yunlong-zhua", 80);
        map_skill("hand", "yunlong-shou");
        map_skill("claw", "yunlong-zhua");
        map_skill("force", "yunlong-shengong");
        map_skill("dodge", "yunlong-shenfa");
        map_skill("parry", "yunlong-shou");
        prepare_skill("hand","yunlong-shou");
        prepare_skill("claw","yunlong-zhua");

        set_temp("apply/attack", 25);
        set_temp("apply/defense", 25);
        set_temp("apply/armor", 5);
        set_temp("apply/damage", 25);
        set("qi", 400);
        set("max_qi", 400);
        set("jing", 300);
        set("max_jing", 300);
        set("neili", 250); 
        set("max_neili", 250);
        set("jiali", 35);
        set("inquiry", ([
                "陳近南" : "想見總舵主可不容易啊。\n",
                "天地會" : "只要是英雄好漢，都可以入我天地會(join tiandihui)。\n",
                "入會" : "只要入了我天地會，可以向會中各位好手學武藝。\n",
                "反清復明" : "去棺材店內室仔細瞧瞧吧！\n",
                "暗號" : "敲三下！\n",
                "切口" : "敲三下！\n",
                "威望" : (: ask_weiwang :),
                "江湖威望" : (: ask_weiwang :),
        ]) );
        set("party/party_name", "天地會");
        set("party/rank", HIG"青木堂"NOR"會眾");
        create_family("雲龍門", 2, "弟子");
        setup();
        carry_object("/clone/misc/cloth")->wear();
        add_money("gold", 1);
}

int ask_weiwang()
{
        command("tell"+query("id", this_player())+"你現在的江湖威望是"+(query("weiwang", this_player())));
        say("\n高彥超説道：如果你威望值很高，有些人見了你不但不會殺你，還會教你武功，送你寶貝。\n而且你還可以加入幫會，率領會眾去攻打目標，就連去錢莊取錢也會有利息 。。。。。\n");
        say("高彥超又説：殺某些壞人或救某些好人可以提高江湖威望。\n");
        return 1;
}

void init()
{
        ::init();
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
/*
int do_skills(string arg)
{
        object ob ;
        ob = this_player () ;
        if( !arg || arg!="gao" ) return 0;
        if(wizardp(ob)) return 0;
        if( query("party/party_name", ob) != "天地會" )
        {
                message_vision("$N搖了搖頭。\n",this_object());
                command("tell"+query("id", ob)+"不是天地會弟子不能察看。\n");
                return 1;
        }
        command("tell"+query("id", ob)+"我所有的武功如下：\n"+
"  基本棍法 (club)                          - 登峯造極  80/    \n"+
"  基本輕功 (dodge)                         - 出神入化  70/    \n"+
"  基本內功 (force)                         - 出神入化  70/    \n"+
"□混元一氣功 (hunyuan-yiqi)                - 神乎其技  60/    \n"+
"  讀書寫字 (literate)                      - 心領神會  50/    \n"+
"  基本招架 (parry)                         - 出神入化  70/    \n"+
"□少林身法 (shaolin-shenfa)                - 神乎其技  60/    \n"+
"  基本拳腳 (unarmed)                       - 出神入化  70/    \n"+
"□少林醉棍 (zui-gun)                       - 出神入化  70/    \n");
        return 1;
}
*/
#include "/kungfu/class/yunlong/tiandihui.h";
