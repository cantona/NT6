#include <ansi.h>
inherit NPC;

#include "fight.h"

void create()                                                                   
{
        NPC_D->generate_cn_name(this_object());
        set("gender", "男性");
        set("long", "這是位衣着破爛的丐幫弟子，眉目間透出股英氣。\n");
        set("title", "丐幫一袋弟子");
        set("age", 38);
        set("attitude", "peaceful");
        set("class", "beggar");

        set("str", 30);
        set("int", 30);
        set("con", 30);
        set("dex", 30);
        set("max_qi", 1800);
        set("max_jing", 1200);
        set("neili", 1600);
        set("max_neili", 1600);
        set("jiali", 150);
        set("combat_exp", 50000);

        set_skill("force", 50);
        set_skill("huntian-qigong", 50);
        set_skill("dodge", 50);
        set_skill("feiyan-zoubi", 50);
        set_skill("staff", 50);
        set_skill("fengmo-zhang", 50);
        set_skill("hand", 50);
        set_skill("shexing-diaoshou", 50);
        set_skill("strike", 50);
        set_skill("xiaoyaoyou", 50);
        set_skill("parry", 50);
        set_skill("begging", 50);
        set_skill("checking", 50);
        set_skill("literate", 50);
        set_skill("martial-cognize", 20);

        map_skill("force", "huntian-qigong");
        map_skill("dodge", "feiyan-zoubi");
        map_skill("staff", "fengmo-zhang");
        map_skill("strike", "xiaoyaoyou");
        map_skill("hand", "shexing-diaoshou");
        map_skill("parry", "fengmo-zhang");

        prepare_skill("hand", "shexing-diaoshou");

        create_family("丐幫", 20, "弟子");

        set("chat_chance_combat", 120);
        set("chat_msg_combat", ({
                (: perform_action, "staff.luan" :),
                (: exert_function, "recover" :),
                (: exert_function, "powerup" :),
        }));

        set_temp("apply/damage", 10);
        set_temp("apply/unarmed_damage", 10);
        set_temp("apply/armor", 50);

        setup();

        carry_object("/clone/weapon/zhubang")->wield();
        carry_object("/clone/cloth/cloth")->wear();
}