#include <ansi.h>
inherit NPC;

void create()
{
        set_name(GRN "大青蛙" NOR, ({ "frog" }));
        set("age", 7);
        set("long", GRN "這是一只黑絲大青蛙，長在深不見日的水潭\n"
                    "裡，全身惡臭，肥肥壯壯，一對血紅的眼睛\n十分"
                    "惡心，你真想殺了它。\n");
        set("limbs", ({ "蛙前爪", "蛙後抓", "蛙嘴" }) );
        set("verbs", ({ "bite", "claw" }) );
        set("combat_exp", 50);
        set("shen_type", -1);
        set("str", 11);
        set("dex", 11);
        set("con", 11);
        set("int", 11);
        set("attitude", "peaceful");
        setup();
}