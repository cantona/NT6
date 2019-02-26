// Npc: /kungfu/class/shaolin/xuan-tong.c
// Date: YZC 96/01/19

inherit NPC;
inherit F_MASTER;

#include "xuan.h"

void create()
{
        set_name("玄寂大師", ({
                "xuanji dashi",
                "xuanji",
                "dashi",
        }));
        set("long",
                "他是一位白鬚白眉的老僧，身穿一襲銀絲棕黃袈裟。他身材高大，\n"
                "兩手過膝。雙目半睜半閉，卻不時射出一縷精光。\n"
        );

        set("nickname", "龍樹院首座");
        set("gender", "男性");
        set("attitude", "friendly");
        set("class", "bonze");

        set("age", 70);
        set("shen_type", 1);
        set("str", 30);
        set("int", 30);
        set("con", 30);
        set("dex", 30);
        set("max_qi", 2500);
        set("max_jing", 1000);
        set("neili", 3500);
        set("max_neili", 3500);
        set("jiali", 50);
        set("combat_exp", 1100000);

        set_skill("force", 160);
        set_skill("hunyuan-yiqi", 160);
        set_skill("strike", 160);
        set_skill("yipai-liangsan", 160);
        set_skill("shaolin-xinfa", 150);
        set_skill("dodge", 150);
        set_skill("shaolin-shenfa", 150);
        set_skill("parry", 150);
        set_skill("claw", 150);

        set_skill("longzhua-gong", 160);
        set_skill("yipai-liangsan", 160);
        set_skill("buddhism", 150);
        set_skill("literate", 150);
        set_skill("medical", 180);
        set_skill("shaolin-yishu", 180);

        map_skill("force", "hunyuan-yiqi");
        map_skill("parry", "longzhua-gong");
        map_skill("dodge", "shaolin-shenfa");
        map_skill("claw", "longzhua-gong");
        map_skill("parry", "yingzhua-gong");
        map_skill("strike", "yipai-liangsan");

        prepare_skill("strike", "yipai-liangsan");

        create_family("少林派", 36, "弟子");

        set("chat_chance_combat", 120);
        set("chat_msg_combat", ({
                (: exert_function, "recover" :),
                (: exert_function, "powerup" :),
                (: perform_action, "claw.zhua" :),
        }));

        set("master_ob",4);
        setup();

        carry_object("/d/shaolin/obj/xuan-cloth")->wear();
}
