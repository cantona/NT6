#include <ansi.h>
#include <combat.h>
inherit NPC;
void create()
{
        string *names = ({"白額猛虎","吊睛猛虎"});
        set_name( names[random(sizeof(names))], ({ "big tiger","tiger"}));
        set("vendetta_mark","tiger");
        set("race", "野獸");
        set("gender", "雄性");
        set("age", 20);
        set("long", "這是一隻兇猛的老虎。\n");

        set("str", 50);
        set("cor", 120);
        set("cps", 22);
        set("fle",50);
        set("resistance/qi",25);
        set("max_qi", 4000);
        set("max_jing", 2000);
        set("max_neili", 4000);
        set("attitude", "peaceful");

        set("limbs", ({ "頭部", "身體", "前腳", "後腳", "尾巴" }) );
        set("verbs", ({ "bite", "claw" }) );
        set("combat_exp", 300000);
        set("bellicosity", 5 );

        set_temp("apply/attack", 50);
        set_temp("apply/parry", 50);
        set_temp("apply/unarmed_damage", 50);

        setup();
        carry_object(__DIR__"obj/tiger_bone");
}

varargs void start_busy(mixed new_busy, mixed new_interrupt)
{
        message_vision(HIY"\n$N突然發出一聲響徹山林的怒吼，$n頓時大驚失色！\n"NOR,this_object());
        ::start_busy(1);
}