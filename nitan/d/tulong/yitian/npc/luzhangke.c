#include <ansi.h>
inherit NPC;

void create()
{
        set_name("鹿杖客", ({ "lu zhangke", "lu", "zhangke" }));
        set("long", "一個六十多歲的老者，頭髮花白，滿面紅光，\n"
                    "身材魁梧高大，這便是汝陽王用重金聘請的\n"
                    "高手，玄冥二老中的鹿杖客，一雙玄冥毒掌\n"
                    "使得出神入化，武藝超羣，很得汝陽王的賞\n"
                    "識。\n");
        set("title", MAG "玄冥二老" NOR);
        set("gender", "男性");
        set("age", 68);
        set("attitude", "peaceful");
        set("shen_type", -1);

        set("per", 30);
        set("str", 40);
        set("int", 40);
        set("con", 40);
        set("dex", 40);
        
        set("max_qi", 4000);
        set("max_jing", 2000);
        set("neili", 4800);
        set("max_neili", 4800);
        set("jiali", 150);
        set("combat_exp", 1800000);

        set("chat_chance_combat", 100);
        set("chat_msg_combat", ({
                (: perform_action, "strike.wuji" :),
                (: exert_function, "powerup" :),
                (: exert_function, "recover" :),
        }) );

        set_skill("literate", 100);
        set_skill("force", 270);
        set_skill("dodge", 250);
        set_skill("unarmed", 270);
        set_skill("parry", 270);
        set_skill("strike", 270);
        set_skill("lingxu-bu", 250);
        set_skill("xuanming-zhang", 270);
        set_skill("xuanming-shengong", 270);

        map_skill("dodge", "lingxu-bu");
        map_skill("force", "xuanming-shengong");
        map_skill("strike", "xuanming-zhang");
        map_skill("parry", "xuanming-zhang");

        prepare_skill("strike", "xuanming-zhang");

        setup();
        carry_object("/clone/cloth/cloth")->wear();
}
