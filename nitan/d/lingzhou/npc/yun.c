// yun.c

inherit NPC;

#include <ansi.h>;
void create()
{

        set_name("雲中鶴", ({ "yun zhonghe", "yun" }));
        set("gender", "男性");
        set("nickname", HIY"窮兇極惡"NOR);
        set("age", 34);
        set("str", 25);
        set("dex", 16);
        set("per", 21);
        set("long", "此人長得又高又瘦象一杆大竹竿，説話聲音忽尖忽粗，十分難
聽，穿着一身青衫，一副色迷迷模樣。\n");
        set("combat_exp", 150000);
        set("shen_type", 1);
        set("attitude", "peaceful");
        set("neili", 1000);
        set("max_neili", 1000);
        set("jiali", 50);

        set_skill("strike", 80);
        set_skill("claw", 80);
        set_skill("force", 80);
        set_skill("dodge", 80);
        set_skill("parry", 80);
        set_skill("huhe-quan", 80);
        set_skill("huagong-dafa", 80);
        set_skill("shaolin-shenfa", 80);
        map_skill("dodge", "shaolin-shenfa");
        map_skill("force", "huagong-dafa");
        map_skill("parry", "huhe-quan");
        map_skill("cuff", "huhe-quan");
        prepare_skill("cuff", "huhe-quan");

        setup();
        carry_object("/kungfu/class/taohua/obj/bupao")->wear();
}
