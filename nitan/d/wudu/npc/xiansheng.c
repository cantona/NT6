#include <ansi.h> 
inherit NPC;

void create()
{
        set_name("教書先生", ({ "xian sheng","xian" }) );
        set("gender", "男性" );
        set("age", 40);
        set("per", 30);
        set("long", "一位白面無須的中年文士，正搖頭晃腦的在教學生念書。\n");
        set("combat_exp", 1000);
        set("attitude", "friendly");
        set_skill("dodge", 15);
        set_skill("unarmed", 10);
        set_skill("parry", 15);
        set("max_qi", 400);

        set("chat_chance", 10);
        set("chat_msg", ({
                CYN "教書先生念道：人之初，性本善。\n" NOR,
                CYN "教書先生搖頭晃腦的吟道：關關雎鳩，在河之洲，窈窕淑女，君子好逑。\n" NOR,
                CYN "教書先生自言自語道：撓撓癢癢，癢癢撓撓，不撓不癢，不癢不撓。\n" NOR,
                CYN "教書先生朗聲念道：春眠不覺曉，處處聞啼鳥。\n" NOR,
        }));

        setup();
        add_money("silver", 5);

        carry_object("/d/city/obj/cloth")->wear();
}