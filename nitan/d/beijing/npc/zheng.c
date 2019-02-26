inherit NPC;
#include <ansi.h>
void create()
{
        set_name("鄭克爽", ({ "zheng keshuang", "zheng" }));
        set("title", HIC"一等海澄公"NOR);
        set("long", "這是一個弓腰曲背的老頭兒，頭髮花白，容色憔悴不堪，\n"
                   "仔細再看，這人年紀倒也不怎麼老，只是愁眉苦臉，眼角\n"
                   "邊都是皺紋，頦下留了短鬚，也已花白，再凝神一看，卻\n"
                   "不是鄭克爽是誰\n");
        set("gender", "男性");
        set("age", 32);
        set("attitude", "peaceful");
        set("shen_type", 1);
        set("str", 50);
        set("int", 40);
        set("con", 40);
        set("per", 40);
        
        set("neili", 300);
        set("max_neili", 300);

        set("combat_exp", 100000);

        set_skill("unarmed", 100);
        set_skill("force", 100);
        set_skill("dodge", 100);
        set_skill("parry", 100);

        setup();
        carry_object("/d/beijing/npc/obj/goldcloth1")->wear();
}
