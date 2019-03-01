#include <ansi.h>

inherit NPC;
inherit F_DEALER;

void create()
{
          set_name("巫攀冰", ({ "wu panbing", "wu", "panbing"}));
          set("gender","男性");
        set("age", 56);
        set("title", "藥舖老板");
        set("combat_exp", 6000);
        set_skill("unarmed", 40);
        set_skill("parry", 40);
        set_skill("dodge", 40);
        set_skill("literate", 20);
        set("chat_chance", 5);
        set("chat_msg", ({
                CYN "巫攀冰拿筆桿敲了敲腦袋，一副恍然大悟的模樣。\n" NOR,
                CYN "巫攀冰使勁翻動著三尺厚的帳本。\n" NOR,
                CYN "巫攀冰道：中醫之中，要數本草綱目為一絕了。\n" NOR,
        }));
        setup();
        carry_object("/clone/misc/cloth")->wear();
        carry_object("/clone/book/mbook1");
        carry_object("/clone/book/mbook2");
}

void init()
{
        add_action("do_buy", "buy");
        add_action("do_list", "list");
}