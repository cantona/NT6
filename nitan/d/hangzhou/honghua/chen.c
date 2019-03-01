// chen.c 陳家洛

#include <ansi.h>

inherit NPC;
inherit F_MASTER;

void create()
{
        set_name("陳家洛", ({ "chen jialuo", "chen","jialuo" }));
        set("title", HIR "紅花會"HIG"總舵主" NOR);
        set("long",
"他一副模樣直是個富貴人家的紈褲子弟，豐姿如玉，目朗似星，輕
袍緩帶，手中搖著一柄折扇，神採飛揚，氣度閒雅，吐屬斯文。服
飾儼然是個貴介公子。\n");
        set("nickname", HIY"玉面神龍"NOR);
        set("gender", "男性");
        set("class", "scholar");
        set("age", 22);
        set("attitude", "friendly");
        set("shen_type", 1);
        set("per", 30);
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

        set_skill("literate", 600);
        set_skill("force", 600);
        set_skill("dodge", 600);
        set_skill("unarmed", 600);
        set_skill("parry", 600);
        set_skill("whip", 600);
        set_skill("blade", 600);
        set_skill("sword", 600);
        set_skill("hand", 600);
        set_skill("claw", 600);
        set_skill("yunlong-xinfa", 600);
        set_skill("yunlong-shengong", 600);
        set_skill("wuhu-duanmendao", 600);
        set_skill("yunlong-jian", 600);
        set_skill("yunlong-shenfa", 600);
        set_skill("yunlong-bian", 600);
        set_skill("yunlong-shou", 600);
        set_skill("yunlong-zhua", 600);
/*
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
        set_skill("yunlong-xinfa", 200);
        set_skill("yunlong-shengong", 200);
        set_skill("wuhu-duanmendao", 150);
        set_skill("yunlong-jian", 200);
        set_skill("yunlong-shenfa", 150);
        set_skill("yunlong-bian", 150);
        set_skill("yunlong-shou", 150);
        set_skill("yunlong-zhua", 150);
*/

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
        set("env/wimpy", 60);

         setup();
        carry_object(CLOTH_DIR"jinduan")->wear();
        //carry_object("/d/beijing/obj/yaodai")->wear();
        carry_object("/clone/weapon/changjian")->wield();
}
