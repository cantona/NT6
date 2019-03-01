// chengqi.c

#include <ansi.h>;
inherit NPC;

void create()
{
        set_name("陳七", ({ "chen qi","chen" }) );
        set("gender", "男性");
        set("title", HIR"福"HIC"威"YEL"鏢局"HIY"趟子手"NOR);
        set("age", 30);
        set("long",
                "這是個鏢局趟子手，長得虎背熊腰，一身橫練功夫。\n");
        set("combat_exp", 10000);
        set("shen_type", -1);
        set("attitude", "peaceful");

        set("apply/attack", 20);
        set("apply/defense", 20);

        set_skill("unarmed", 40);
        set_skill("sword", 20);
        set_skill("parry", 40);
        set_skill("dodge", 40);
        setup();

        carry_object("/clone/misc/cloth")->wear();
        add_money("silver", 1);
}