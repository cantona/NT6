#include <ansi.h>

inherit NPC;

void create()
{
        set_name("血刀老祖--幻", ({ "xuedao laozu-shadow","shadow" }));
        set("long",@LONG
這喇嘛身著黃袍，年紀極老，尖頭削耳，臉上都是皺紋。他就是血刀門第四代掌門。
不過仔細一看，似乎不象是真人。
LONG
        );
        set("title",HIR"血刀門第四代掌門"NOR);
        set("gender", "男性");
        set("age", 85);
        set("attitude", "peaceful");
        set("shen_type", -1);
        set("str", 130);
        set("int", 130);
        set("con", 130);
        set("dex", 130);
        set("max_qi", 311000);
        set("max_jing", 101100);
        set("neili", 20100);
        set("max_neili", 20100);
        set("jiali", 50);
        set("combat_exp", 180011000);
        set("score", 18110000);

        set_skill("lamaism", 1150);
        set_skill("literate", 1180);
        set_skill("force", 1180);
        set_skill("parry", 1180);
        set_skill("blade", 1180);
        set_skill("sword", 1120);
        set_skill("dodge", 1180);
        set_skill("longxiang-gong", 1180);
        set_skill("shenkong-xing", 1180);
        set_skill("hand", 1180);
        set_skill("dashou-yin", 1180);
        set_skill("mingwang-jian", 1120);
        set_skill("xuedao-daofa", 2100);

        map_skill("force", "longxiang-gong");
        map_skill("dodge", "shenkong-xing");
        map_skill("hand", "dashou-yin");
        map_skill("parry", "xuedao-daofa");
        map_skill("blade", "xuedao-daofa");
        map_skill("sword", "mingwang-jian");
        prepare_skill("hand","dashou-yin");        
        set("chat_chance_combat", 50);  
        set("chat_msg_combat", ({
                (: perform_action, "blade.shendao" :), 
                (: perform_action, "blade.shendao" :),
                (: perform_action, "blade.shendao" :),
                (: perform_action, "blade.shendao" :),
                (: perform_action, "blade.shendao" :),
        }) );

        create_family("雪山寺", 4, "弟子");
        set("class", "bonze");

        setup();
        carry_object("/clone/weapon/blade.c")->wield();

} 

int accept_fight(object ob)
{
        ob=this_player();   
        if( !query("fighter", ob)){command("grin");command("say 好，送死的來了！\n");
        set("fighter", 1, ob);
        set_temp("m_success/幻影", 1, ob);
        remove_call_out("kill_ob");
        call_out("kill_ob", 1, ob);
        return 1;
        }
        else
        write(query("name", ob)+"，你已經上過場了！\n");}
void die()
{
        object ob;        message_vision("\n$N一晃，變為一縷輕煙消失了。\n", this_object());
        ob = new("/quest/tulong/npc/shadow2");
        ob->move(environment(this_object()));
        destruct(this_object());
} 
