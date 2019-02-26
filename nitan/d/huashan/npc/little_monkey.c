// little_monkey.c

inherit NPC;

void create()
{
        set_name("小猴",({ "little monkey", "monkey"}) );
        set("gender", "雄性");
        set("race", "野獸");
        set("age", 2);
        set("long", "這是一隻調皮的小猴子，雖是畜牲，卻喜歡模仿人樣。\n"
            "陸大有整天調教得它無比伶俐，現在正騎在陸大有的脖子上。\n");
        set("limbs", ({ "頭部", "身體", "前腳", "後腳", "尾巴" }) );
        set("verbs", ({ "bite", "claw" }) );
        set("shen_type", 0);
        set("str", 20);
        set("dex", 20);
        set("con", 20);
        set("int", 20);
        set("attitude", "peaceful");

        set("no_get", 1);
        set("max_qi", 300);
        set("qi", 300);
        set("max_jing", 100);
        set("jing", 100);
        set("combat_exp", 50000);

        set("fight_times", 0);        

        set("chat_chance", 15);
        set("chat_msg", ({
                "小猴伸出小抓撓撓頭，衝你扮個鬼臉。\n",
                "小猴懶洋洋地打了個哈欠，爬到陸大有頭頂，又翻身下到主人肩頭。\n",
                "小猴伸抓捉住了身上的蝨子，看了兩眼，使勁就是一捏! \n",
        }));
        setup();
        
}
