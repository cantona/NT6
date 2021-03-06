// baizhen.c

#include <ansi.h>

inherit NPC;

void create()
{
        set_name("白振", ({ "bai zhen", "bai", "zhen"}) );
        set("title", "御前侍衞");
        set("nickname", HIY"金爪"HIB"鐵鈎"NOR);
        set("gender", "男性");
        set("age", 64);
        set("long",
                "白振是嵩陽派高手，三十年前就馳名武林了。\n");
        set("combat_exp", 450000);
        set("shen_type", -1);
        set("attitude", "heroism");

        set_skill("unarmed", 95);
        set_skill("blade", 95);
        set_skill("claw", 95);
        set_skill("parry", 90);
        set_skill("dodge", 90);
        set_skill("sougu-yingzhua", 90);
        set_skill("lingxu-bu", 90);
        map_skill("dodge", "lingxu-bu");
        map_skill("claw", "sougu-yingzhua");
        map_skill("parry", "sougu-yingzhua");
        prepare_skill("claw", "sougu-yingzhua");

        setup();
        carry_object("/d/city/obj/tiejia")->wear();

        add_money("silver", 30);
}
