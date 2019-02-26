// xiaoyao.c 逍遙子

#include <ansi.h>
inherit NPC;

void create()
{
        set_name("逍遙子", ({ "xiaoyao  zi"}));
        set("nickname", "煙霞神龍");
        set("long","病夫模樣的中年人，衣衫襤褸，咬著一根旱煙管，雙目似睜似閉，嘴裏慢慢噴出煙霧。\n");
        set("gender", "男性");
        set("age", random(10) + 45);
        set("attitude", "peaceful");
        set("str", 25);
        set("int", 20);
        set("con", 25);
        set("dex", 27);

        set("max_qi", 1500);
        set("max_jing", 800);
        set("neili", 700);
        set("max_neili", 700);
        set("jiali", 100);
        set("combat_exp", 500000 + random(40000));
        set("chat_msg_combat", ({
               (: exert_function, "powerup" :),
               (: exert_function, "regenerate" :),
               (: exert_function, "recover" :),
        }));

        set_skill("force", 60);
        set_skill("beiming-shengong", 100);
        set_skill("dodge", 100 + random(50));
        set_skill("yunlong-shenfa", 150 + random(50));
        set_skill("hand", 100 + random(50));
        set_skill("shexing-diaoshou", 150 + random(50));
        set_skill("parry", 100 + random(50));
        set_skill("literate", 20);
        map_skill("force" , "beiming-shengong");
        map_skill("hand","shexing-diaoshou");
        map_skill("parry","shexing-diaoshou");
        map_skill("dodge","yunlong-shenfa");

        setup();
        carry_object("/clone/misc/cloth")->wear();
          add_money("silver", 50);
}
#include "npc.h"
