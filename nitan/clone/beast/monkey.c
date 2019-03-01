// Code of ShenZhou
// monkey.c 

inherit NPC;

void create()
{
        set_name("猴子", ({ "monkey" }) );
        set("gender", "男性");
        set("age", 25);
        set("long",
                "這只猴子在在桃樹間跳上跳下，還不時津津有味地啃幾口著蜜桃。\n");
        set("combat_exp", 5000);
        set("shen_type", -1);
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