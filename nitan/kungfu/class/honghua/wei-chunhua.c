// Last Modified by winder on Sep. 12 2001
// wei-chunhua.c 衛春華

#include <ansi.h>;
inherit NPC;

void create()
{
        set_name("衛春華", ({ "wei chunhua", "wei","chunhua" }));
        set("title", HIR "紅花會"HIG"九當家" NOR);
        set("nickname", HIY "九命錦豹子" NOR);
        set("long", 
"他長得面目英俊，穿一件青布長衫，三十歲左右年紀，雙目炯炯，
英氣逼人。凡逢江湖上兇毆爭鬥、對抗官兵之時，衛春華總是不顧
性命的勇往直前，一生所遇兇險不計其數，但連重傷也未受過一次，
是以說他有九條性命。\n");
        set("gender", "男性");
        set("class", "swordsman");
        set("age", 31);
        set("attitude", "friendly");
        set("shen_type", 1);
        set("per", 26);
        set("str", 30);
        set("int", 30);
        set("con", 30);
        set("dex", 30);
        
        set("max_qi", 1800);
        set("max_jing", 800);
        set("neili", 1000);
        set("max_neili", 1000);
        set("jiali", 100);
        set("combat_exp", 250000);

        set_skill("force", 100);
        set_skill("dodge", 100);
        set_skill("cuff", 100);
        set_skill("parry", 100);
        set_skill("sword", 100);
        set_skill("baihua-cuoquan", 150);
        set_skill("honghua-shengong", 100);
        set_skill("zhuihun-jian", 150);
        set_skill("youlong-shenfa", 150);

        map_skill("dodge", "youlong-shenfa");
        map_skill("force", "honghua-shengong");
        map_skill("cuff", "baihua-cuoquan");
        map_skill("parry", "zhuihun-jian");
        map_skill("sword", "zhuihun-jian");
        prepare_skill("cuff", "baihua-cuoquan");

        set("env/wimpy", 60);
        set("chat_chance_combat", 60);
        set("chat_msg_combat", ({
                (: perform_action, "sword.zhuihun" :),        
                (: perform_action, "cuff.cuo" :),                        
                (: exert_function, "powerup" :),
                (: exert_function, "regenerate" :),
                (: exert_function, "recover" :),
        }) );
        create_family("紅花會", 2, "弟子");

         setup();
        carry_object("/d/wudang/obj/bluecloth")->wear();
        carry_object(WEAPON_DIR"changjian")->wield();
}
