// daobaifeng.c 刀白鳳

#include <ansi.h>
inherit NPC;
inherit F_MASTER;

void create()
{
        set_name("刀白鳳", ({ "dao baifeng", "dao" }));
        set("title",  "大理國王妃" );
        set("nickname",  CYN"玉虛散人"NOR );
        set("gender", "女性");
        set("long", "這是個容貌秀麗的中年道姑，是個擺夷族女子，頗有雍容氣質。
她本是大理國皇帝段正淳的正房原配夫人。
因惱丈夫風流不羈，沾花惹草，一怒之下跑到這裏出了家。她看起來約三十多歲。\n");
        set("age", 35);
        set("class", "officer");
        set("attitude", "friendly");
        set("shen_type", 1);
        set("per", 28);
        set("str", 25);
        set("int", 25);
        set("con", 25);
        set("dex", 25);
        set("env/wimpy", 60);        
        
        set("max_qi", 1800);
        set("max_jing", 500);
        set("neili", 1500);
        set("max_neili", 1500);
        set("jiali", 100);
        set("combat_exp", 500000);
        set("score", 200000);

        set_skill("force", 100);
        set_skill("dodge", 100);
        set_skill("parry", 100);
        set_skill("sword", 100);
        set_skill("cuff", 100);
        set_skill("strike", 100);
        set_skill("whip", 100);
        set_skill("kurong-changong", 100);
        set_skill("duanjia-jian", 150);
        set_skill("tiannan-bu", 150);
        set_skill("jinyu-quan", 150);
        set_skill("wuluo-zhang", 150);
        set_skill("feifeng-bian", 150);
        set_skill("literate", 60);

        map_skill("force", "kurong-changong");
        map_skill("dodge", "tiannan-bu");
        map_skill("whip", "feifeng-bian");
        map_skill("cuff", "jinyu-quan");
        map_skill("strike", "wuluo-zhang");
        map_skill("parry", "feifeng-bian");
        map_skill("sword", "duanjia-jian");
        prepare_skill("cuff", "jinyu-quan");
        prepare_skill("strike", "wuluo-zhang");
        set("chat_chance_combat", 60);
        set("chat_msg_combat", ({                                        
                (: exert_function, "powerup" :),                
                (: exert_function, "recover" :),
                (: exert_function, "regenerate" :),
        }) );

        setup();
        carry_object("/d/dali/npc/obj/cynrobe")->wear();
        carry_object("/d/dali/obj/fuchen")->wield();
        add_money("silver", 10);

        create_family("大理段家",18,"王妃");
}

void attempt_apprentice(object ob)
{
        if ((int)ob->query_skill("kurong-changong",1) < 30 )
        {
                command("say 你的本門內功心法太低了，還是努努力先提高一下吧。");
                return;
        }
        if( query("gender", ob) != "女性" )
        {
                command("say 我只收女弟子。");
                return;
        }
        if( query("shen", ob)<10000 )
        {
                command("say 我大理段氏向來行俠仗義，您請回吧！");
                return;
        }
        if( strsrch(query("guard", ob),"鎮南王府") >= 0 )
        {
                command("say 很好，既然入我門來就得終身為奴供我驅使。");
                command("recruit "+query("id", ob));
        }
        else
        {
                command("say 你是何人，如此大膽，假冒我府中廝僕！");
                return;
        }
}
 
