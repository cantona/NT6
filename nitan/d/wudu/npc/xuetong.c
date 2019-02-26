#include <ansi.h> 
inherit NPC;

void create()
{
        set_name("小學童", ({ "xue tong","tong" }) );
        set("gender", "男性" );
        set("age", 14);
        set("per", 30);
        set("long", "這是一個十三四歲的小童，正心不在焉的跟着先生胡亂念着。\n");
        set("combat_exp", 300);
        set("attitude", "friendly");
        set_skill("dodge", 5);
        set_skill("unarmed", 5);
        set_skill("parry", 5);
        set("max_qi", 200);

        set("chat_chance", 10);
        set("chat_msg", ({
                CYN "小學童斷斷續續的念道：人之初，性本……呼…呼……\n" NOR,
                CYN "小學童搖頭晃腦的念道：蟈蟈鳩鳩，在河洲洲，窈窕是你，君子高逑。\n" NOR,
                CYN "小學童自言自語道：生生死死，死死生生，先生先死，先死先生。\n" NOR,
                CYN "小學童隨聲附和道：春眠不覺曉，所以睡懶覺。\n" NOR,
        }));

        setup();
        add_money("coin", 50);

        carry_object("/d/city/obj/cloth")->wear();
}