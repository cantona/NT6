// xiaoxian.c 星宿小仙

#include <ansi.h>

inherit "/inherit/char/punisher";

void create()
{
        set_name("星宿小仙", ({ "xingxiu xiaoxian", "xiaoxian" }));
        set("long",  "她是一個小女孩，看上去年紀不大。\n");
        set("gender", "女性");
        set("age", 24);
        set("attitude", "peaceful");
        set("shen_type", 1);
        set("str", 30);
        set("int", 36);
        set("con", 38);
        set("dex", 33);
        
        set("max_qi", 60000);
        set("max_jing", 30000);
        set("neili", 75000);
        set("max_neili", 75000);
        set("jiali", 150);
        set("combat_exp", 55000000);
        set("score", 10000000);

        set_skill("force", 2200);
        set_skill("huagong-dafa", 2200);
        set_skill("guixi-gong", 2000);
        set_skill("throwing", 2100);
        set_skill("feixing-shu", 2100);
        set_skill("dodge", 1800);
        set_skill("zhaixing-gong", 1800);
        set_skill("strike", 1850);
        set_skill("chousui-zhang", 1850);
        set_skill("claw", 1800);
        set_skill("sanyin-wugongzhao", 1800);
        set_skill("whip", 1800);
        set_skill("chanhun-suo", 1800);
        set_skill("parry", 1850);
        set_skill("staff", 1900);
        set_skill("poison", 2550);
        set_skill("tianshan-zhang", 1900);
        set_skill("literate", 1200);

        map_skill("force", "huagong-dafa");
        map_skill("dodge", "zhaixing-gong");
        map_skill("strike", "chousui-zhang");
        map_skill("claw", "sanyin-wugongzhao");
        map_skill("whip", "chanhun-suo");
        map_skill("parry", "tianshan-zhang");
        map_skill("staff", "tianshan-zhang");

        prepare_skill("strike", "chousui-zhang");
        prepare_skill("claw", "sanyin-wugongzhao");

        create_family("星宿派", 0, "奇人");

        set("chat_chance_combat", 120);
        set("chat_msg_combat", ({
                (: perform_action, "staff.fugu" :),
                (: perform_action, "staff.xue" :),
                (: perform_action, "claw.zhua" :),
                (: exert_function, "recover" :),
        }));

        setup();
        carry_object("/clone/weapon/gangzhang")->wield();
        carry_object("/clone/misc/cloth")->wear();
}
