// Last Modified by winder on Sep. 12 2001
// xutianhong.c 徐天宏

#include <ansi.h>;
inherit NPC;
inherit F_MASTER;

void create()
{
        set_name("徐天宏", ({ "xu tianhong", "xu", "tianhong" }));
        set("nickname", HIM"武諸葛"NOR);
        set("title", HIR"紅花會"HIG"七當家"NOR);
        set("long","他是紅花會的七當家，\n他年紀好像在四十上下，身材矮小，足智多謀，是紅花會的智囊軍師。武功也頗不弱，冷靜持重。\n");
        set("gender", "男性");
        set("class", "swordman");
        set("age", 40);
        set("attitude", "peaceful");
        set("shen_type", 1);
        set("str", 28);
        set("int", 28);
        set("con", 28);
        set("dex", 28);
        
        set("max_qi", 2000);
        set("max_jing", 1500);
        set("neili", 2400);
        set("max_neili", 2400);
        set("jiali", 100);
        set("combat_exp", 1000000);
        set("score", 100000);

        set_skill("force", 120);
        set_skill("honghua-shengong", 120);
        set_skill("dodge", 120);
        set_skill("youlong-shenfa", 180);
        set_skill("hand", 120);
        set_skill("parry", 120);
        set_skill("sword", 120);
        set_skill("zhuihun-jian", 180);
        set_skill("benlei-shou", 180);
        set_skill("literate", 100);

        map_skill("force", "honghua-shengong");
        map_skill("dodge", "youlong-shenfa");
        map_skill("hand", "benlei-shou");
        map_skill("parry", "zhuihun-jian");
        map_skill("sword", "zhuihun-jian");
        prepare_skill("hand", "benlei-shou");

        create_family("紅花會", 4, "弟子");
        
        set("env/wimpy", 60);
        set("chat_chance_combat", 60);
        set("chat_msg_combat", ({        
                (: perform_action, "sword.zhuihun" :),
                (: perform_action, "hand.yunkai" :),                        
                (: exert_function, "powerup" :),
                (: exert_function, "regenerate" :),
                (: exert_function, "recover" :),
        }) );

        setup();
        carry_object("/d/wudang/obj/bluecloth")->wear();
        carry_object(WEAPON_DIR"changjian")->wield();
}

void init()
{
        object ob = this_player();

        ::init();

        if( query("shen", ob)<1000 && 
                query("family/master_id", ob) == "xutianhong" )
        {
                command("chat"+query("name", ob)+"！你這等邪惡姦詐之徒，我豈能仍是你的師父。\n");
                command("expell"+query("id", ob));
                set("title", "紅花會"+RED+"棄徒"NOR, this_player());
        }
}

void attempt_apprentice(object ob)
{
        if( query("shen", ob)<2000 )
        {
                command("say 我紅花會收徒極嚴。");
                command("say 這位" + RANK_D->query_respect(ob) + "平時還要多做一些行俠仗義之事！");
                return;
        }
        command("say 好，你這個年青人還不錯，我收下你了！");
        command("recruit "+query("id", ob));
}
