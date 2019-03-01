#include <ansi.h>

inherit NPC;
inherit F_MASTER;

void create()
{
        set_name("輝月使", ({ "huiyue shi", "huiyue", "shi" }));
        set("long", "一個三十多歲的中年男子，裝束奇異，不同\n"
                    "普通的中土人士。這便是波斯明教總教教主\n"
                    "座下的輝月使。\n");
        set("title", HIB "波斯總教教主座下" NOR);
        set("nickname", HIY "雲風月三使" NOR);
        set("gender", "男性");
        set("age", 38);
        set("attitude", "friendly");
        set("shen_type", 1);

        set("per", 30);
        set("str", 30);
        set("int", 30);
        set("con", 30);
        set("dex", 30);
        
        set("max_qi", 2500);
        set("max_jing", 800);
        set("neili", 2600);
        set("max_neili", 2600);
        set("jiali", 100);
        set("combat_exp", 800000);

        set("chat_chance_combat", 200);
        set("chat_msg_combat", ({
                (: perform_action, "finger.feng" :),
                (: exert_function, "powerup" :),
                (: exert_function, "recover" :),
        }) );

        set_skill("literate", 100);
        set_skill("sanscrit", 300);
        set_skill("force", 180);
        set_skill("dodge", 180);
        set_skill("unarmed", 180);
        set_skill("parry", 180);
        set_skill("finger", 220);
        set_skill("strike", 220);
        set_skill("sword", 180);
        set_skill("shenghuo-ling", 180);
        set_skill("tougu-zhen", 220);
        set_skill("yinfeng-dao", 220);
        set_skill("shenghuo-xinfa", 200);
        set_skill("qiankun-danuoyi", 180);

        map_skill("dodge", "qiankun-danuoyi");
        map_skill("force", "shenghuo-xinfa");
        map_skill("finger", "tougu-zhen");
        map_skill("strike", "yinfeng-dao");
        map_skill("parry", "qiankun-danuoyi");
        map_skill("sword", "shenghuo-ling");

        prepare_skill("strike", "yinfeng-dao");
        prepare_skill("finger", "tougu-zhen");

        create_family("波斯明教總舵", 32, "弟子");

        setup();
        carry_object("/d/tulong/yitian/npc/obj/jiaofu")->wear();
}
void init()
{
        object me;

        me = this_player();

        if (! interactive(me))
                return;

        if (living(this_object()) && present("yitian sword", me))
        {
                command("say 咦？倚天劍怎麼會在你手裡，看來這次中原之行沒白跑了！");
                kill_ob(me);
                return;
        }

        if (living(this_object()) && present("tulong blade", me))
        {
                command("say 哼，把屠龍刀交出來，我們已經守侯多時了！");
                kill_ob(me);
                return;
        }

        if (living(this_object()) && present("shenghuo ling", me))
        {
                command("say 咦？你怎麼會拿著我教的聖火令？死吧！");
                kill_ob(me);
                return;
        }
}
