//shendiao.c

inherit NPC;

void create()
{
        set_name("神鵰", ({ "shen diao", "diao" }) );
        set("race", "飛禽");
        set("subrace", "走禽");
        set("age", 20);
        set("long", @LONG
    這雕身形甚巨，比人還高，形貌醜陋之極，全身羽毛疏疏落
落，似是被人拔去了一大半似的，毛色黃黑，顯得甚是骯髒，雕
釣嘴彎曲，頭頂生著個血紅的大肉瘤，雙腿奇粗，羽翼甚短。
LONG
);
        set("attitude", "peaceful");
        set("chat_chance", 10);
        set("chat_msg", ({
                "這雕邁著大步來去，只是高視闊步，自有一番威武氣概。\n",
                "這雕不時伸出羽翼，卻又甚短，不知如何飛翔，但拍打呼呼成風。\n",
                "這雕突然高聲鳴叫，聲音微帶嘶啞，但激越蒼涼，氣勢甚豪。\n",
        }));
       set("qi", 4000);
        set("max_qi", 4000);
        set("jing", 2000);
        set("max_jing", 2000);
        set("str", 86);
        set("cor", 80);
        set("limbs", ({ "頭部", "身體", "左翅", "右翅", "左爪", "右爪" }) );
        set("verbs", ({ "poke", "claw", "wind" }) );

        set("combat_exp", 2000000);

        set_skill("dodge",100);
        set_skill("parry",100);

        set_temp("apply/attack", 120);
        set_temp("apply/damage", 120);
        set_temp("apply/armor", 120);
        set_temp("apply/defence",120);
        setup();
}

