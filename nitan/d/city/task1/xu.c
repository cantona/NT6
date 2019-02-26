// xu.c 徐長老

#include <ansi.h>
inherit NPC;

void create()
{
        set_name("徐長老", ({ "xu  zhanglao"}));
        set("nickname", "丐幫叛徒");
        set("long", "丐幫的叛徒，據説丐幫弟子正在四處打探他的蹤跡。\n");
        set("gender", "男性");
        set("age", 66);
        set("attitude", "peaceful");
        set("str", 28);
        set("int", 20);
        set("con", 25);
        set("dex", 27);

        set("max_qi", 1500);
        set("max_jing", 1500);
        set("neili", 1800);
        set("max_neili", 1800);
        set("jiali", 100);
        set("combat_exp", 1800000 + random(500000));
         set("chat_chance_combat", 60);
        set("chat_msg_combat", ({
               (: exert_function, "powerup" :),
               (: exert_function, "regenerate" :),
               (: exert_function, "recover" :),
        }));
        set_skill("force", 160+ random(50));
        set_skill("huntian-qigong", 150+ random(50));
        set_skill("dodge", 150+ random(50));
        set_skill("xiaoyaoyou", 220+ random(50));
        set_skill("unarmed", 160+ random(50));
        set_skill("changquan", 220+ random(50));
        set_skill("parry", 150+ random(50));
        set_skill("liuhe-dao", 220+ random(50));
        set_skill("blade", 150+ random(50));
        map_skill("force", "huntian-qigong");
        map_skill("dodge", "xiaoyaoyou");
        map_skill("blade", "liuhe-dao");
        map_skill("unarmed", "changquan");
          map_skill("parry", "liuhe-dao");

        setup();
        carry_object("/clone/misc/cloth")->wear();
        carry_object("/clone/weapon/gangdao")->wield();
        add_money("gold", 3);
}
#include "npc.h"
