// yu.c 余魚同

#include <ansi.h>

inherit NPC;
inherit F_MASTER;

void create()
{
        set_name("余魚同", ({ "yu yutong", "yu","yutong" }));
        set("title", HIR "紅花會"HIG"十四當家" NOR);
        set("nickname", YEL "金笛秀才" NOR);
        set("long",
"一個長身玉立，眉清目秀，風流英俊的書生。余魚同乃江南望族
子弟，中過秀才。他父親因和一家豪門爭一塊墳地，官司打得傾家
盪產，又被豪門借故陷害，瘐死獄中。余魚同一氣出走，得遇機緣，
拜馬真為師，棄文習武，回來把士豪刺死，從此亡命江湖，後來入
了紅花會。他為人機警靈巧，多識各地鄉談，在會中任聯絡四方、
刺探訊息之職。\n");
        set("gender", "男性");
        set("class", "scholar");
        set("age", 20);
        set("attitude", "friendly");
        set("shen_type", 1);
        set("per", 27);
        set("str", 30);
        set("int", 30);
        set("con", 30);
        set("dex", 30);

        set("max_qi", 3000);
        set("max_jing", 1000);
        set("neili", 2000);
        set("max_neili", 2000);
        set("jiali", 100);
        set("combat_exp", 1000000);
        set("score", 500000);

        set_skill("literate", 100);
        set_skill("force", 200);
        set_skill("dodge", 200);
        set_skill("unarmed", 200);
        set_skill("parry", 200);
        set_skill("whip", 200);
        set_skill("blade", 200);
        set_skill("sword", 200);
        set_skill("hand", 200);
        set_skill("claw", 200);
        set_skill("houquan", 150);
        set_skill("yunlong-xinfa", 200);
        set_skill("yunlong-shengong", 200);
        set_skill("wuhu-duanmendao", 150);
        set_skill("yunlong-jian", 200);

        set_skill("yunlong-shenfa", 150);
        set_skill("yunlong-bian", 150);
        set_skill("yunlong-shou", 150);
        set_skill("yunlong-zhua", 150);

        map_skill("dodge", "yunlong-shenfa");
        map_skill("force", "yunlong-shengong");
        map_skill("unarmed", "houquan");
        map_skill("blade", "wuhu-duanmendao");
        map_skill("hand", "yunlong-shou");
        map_skill("parry", "yunlong-shou");
        map_skill("claw", "yunlong-zhua");
        map_skill("sword", "yunlong-jian");
        map_skill("whip", "yunlong-bian");

        prepare_skill("hand","yunlong-shou");
        prepare_skill("claw","yunlong-zhua");
        set("env/wimpy", 20);
        create_family("武當派", 18, "弟子");

         setup();
        carry_object(CLOTH_DIR"jinduan")->wear();
        //carry_object("/d/beijing/obj/yaodai")->wear();
        carry_object(WEAPON_DIR"changjian")->wield();
}

