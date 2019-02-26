// monkey.c 
// Last Modified by winder on Aug. 1 2002

inherit NPC;

void create()
{
        set_name("猴子", ({ "monkey" }) );
        set("gender", "雄性");
        set("race", "走獸");
        set("age", 25);
        set("long", "這隻猴子在在桃樹間跳上跳下，還不時津津有味地啃幾口着蜜桃。\n");
        set("combat_exp", 5000);
        set("attitude", "peaceful");
        
        set("water", 200);
        set("food", 200);

        set("apply/attack", 10);
        set("apply/defense", 10);

//        set("chat_chance", 30);
//        set("chat_msg", ({
//                "土匪一聲大喊: 此山是我開，此樹是我栽，若要從此過，留下買路財 !\n",
//        }) );

        set_skill("unarmed", 25);
        set_skill("parry", 20);
        set_skill("dodge", 20);

        setup();
}