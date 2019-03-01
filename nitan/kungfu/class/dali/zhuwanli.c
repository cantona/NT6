// zhuwanli.c 褚萬裡

#include <ansi.h>
inherit NPC;
inherit F_MASTER;

void upgrade_title(object me,string arg);
string clear_title(string arg);
int ask_me();
int ask_for_toushen();
void create()
{
        set_name("褚萬裡", ({ "zhu wanli", "zhu" }));
        set("title",  "大理國護衛" );
        set("long", "他是大理國四大護衛之一。身穿黃衣，臉上英氣逼人。手持一根鐵桿。\n");
        set("gender", "男性");
        set("age", 33);
        set("class", "officer");
        set("attitude", "friendly");
        set("shen_type", 1);
        set("per", 25);
        set("str", 20);
        set("int", 20);
        set("con", 25);
        set("dex", 25);
        set("no_get",1);
        
        set("max_qi", 1000);
        set("max_jing", 500);
        set("neili", 1000);
        set("max_neili", 1000);
        set("jiali", 50);
        set("combat_exp", 300000);
        set("score", 100000);

        set("inquiry",([
                "投身"    : (: ask_for_toushen :),
                "toushen" : (: ask_for_toushen :),
                "指點武功" : (: ask_me :),
        ]));

        set_skill("force", 50);
        set_skill("dodge", 50);
        set_skill("parry", 50);
        set_skill("cuff", 50);
        set_skill("sword", 50);
        set_skill("staff", 50);
        set_skill("kurong-changong", 50);
        set_skill("tiannan-bu", 70);
        set_skill("jinyu-quan", 70);
        set_skill("duanjia-jian", 75);
        set_skill("literate", 30);

        map_skill("force", "kurong-changong");
        map_skill("dodge", "tiannan-bu");
        map_skill("cuff", "jinyu-quan");
        map_skill("sword", "duanjia-jian");
        map_skill("staff", "duanjia-jian");
        map_skill("parry", "duanjia-jian");
        prepare_skill("cuff", "jinyu-quan");
        set("chat_chance_combat", 60);
        set("chat_msg_combat", ({
                (: perform_action, "sword.jingtian" :),                                
                (: exert_function, "powerup" :),                
                (: exert_function, "recover" :),
                (: exert_function, "regenerate" :),
        }) );

        setup();
        carry_object("/d/dali/npc/obj/junfu")->wear();
        carry_object(__DIR__"obj/diaogan")->wield();
        add_money("silver", 10);

        create_family("大理段家",19,"護衛");
}
int ask_for_toushen()
{
        object me;

        me = this_player();

        if( query("class", me) == "eunach" )
        {
                command("say 公公？我們府裡不收公公。\n");
                return 1;
        }
        if( query("class", me) == "bonze" )
        {
                say( "褚萬裡說道：這位" + RANK_D->query_respect(me)
                        + "，出家人哪還能再有家？\n");
                return 1;
        }
        if( (int)me->query_str() < 20)
        {
                say( "褚萬裡說道：這位" + RANK_D->query_respect(me)
                        + "這麼文弱，怎麼能在府裡承值？\n");
                return 1;
        }
        say( "褚萬裡說道：這位" + RANK_D->query_respect(me)
                + "就委屈你先在府裡聽用吧。\n");
        set("guard", "鎮南王府家奴", me);
        return 1;
}
#include "/kungfu/class/dali/weishi.h"; 
