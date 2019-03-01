// chuyuan.c

#include <ansi.h>

inherit NPC;

void create()
{
        set_name("褚圓", ({ "chu yuan", "chu", "yuan"}) );
        set("title", "御前侍衛");
        set("gender", "男性");
        set("age", 34);
        set("long",
                "褚圓原是和尚，法名智圓，後來犯了清規，被追繳度牒，逐
出廟門，他索性還了俗，做了大內侍衛。\n");
        set("combat_exp", 350000);
        set("shen_type", -1);
        set("attitude", "heroism");

        set_skill("unarmed", 55);
        set_skill("sword", 55);
        set_skill("parry", 50);
        set_skill("dodge", 50);
        set_skill("damo-jian", 50);
        set_skill("shaolin-shenfa", 50);
        map_skill("sword", "damo-jian");
        map_skill("parry", "damo-jian");
        map_skill("dodge", "shaolin-shenfa");

        setup();
        carry_object("/d/city/obj/tiejia")->wear();
        carry_object("/clone/weapon/changjian")->wield();

        add_money("silver", 10);
}
