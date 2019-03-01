// /d/yixing/npc/shijian.c 侍劍
// Last Modified by winder on Jul. 12 2002

#include <ansi.h>;
inherit NPC;

void create()
{
        set_name("侍劍", ({ "shijian" }));
        set("long","她是長樂幫主的小丫鬟，臉龐略作圓形，倒也嫵媚可喜。\n她頭發略見蓬鬆，雪白的赤足踏在一雙繡花拖鞋中。\n");
        set("gender", "女性");
        set("age", 16);
        set("attitude", "friendly");
        set("shen_type", 1);
        set("str", 18);
        set("int", 28);
        set("con", 20);
        set("dex", 20);
   
        set("max_qi", 500);
        set("max_jing", 200);
        set("neili", 200);
        set("max_neili", 200);
        set("jiali", 10);
        set("combat_exp", 5000);
        set("score", 100);

        set_skill("force", 40);
        set_skill("dodge", 30);
        set_skill("unarmed", 30);
        set_skill("parry", 20);

        setup();
        carry_object("/d/city/obj/pink_cloth")->wear();
}
