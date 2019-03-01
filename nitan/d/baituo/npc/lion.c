// lion.c
// Date: Sep.22 1997

inherit NPC;

void create()
{
        set_name("雄獅", ({ "lion", "xiongshi", "shi" }) );
        set("race", "野獸");
        set("age", 15);
        set("long", "一隻矯健的雄獅，十分威風。\n");
//        set("attitude", "aggressive");
        set("attitude", "peace");
        set("shen_type", -1);

        set("limbs", ({ "獅頭", "獅身", "前爪", "後抓", "尾巴" }) );
        set("verbs", ({ "bite", "claw" }) );

        set("combat_exp", 40000);
        set_temp("apply/attack", 20000);
        set_temp("apply/defense", 30000);
        set_temp("apply/armor", 800);

        setup();

        set("chat_chance", 10);
        set("chat_msg", ({
                "雄獅一聲長吼，四下傳來陣陣會響。\n",
                "雄獅後足一蹬，猛地一躍到你的面前。\n",
        }) );
}
