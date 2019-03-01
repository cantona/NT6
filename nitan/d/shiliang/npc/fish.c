// Feb. 6, 1999 by Winder

inherit NPC;
void create()
{
        set_name("噬人魚", ({ "fish", "yu" }) );
        set("race", "遊魚");
        set("age", 3);
        set("long", "這是一只身形並不很大的魚，渾身覆滿絢麗的鱗片，\n"
            "一口鋒利的牙齒，正虎視耽耽的看著你\n");
        set("attitude", "aggressive");
        set("max_qi",1000);
        set("str", 26);
        set("cor", 30);
        set("combat_exp", 1000000);
        set("max_kee", 6000);
        
         set_temp("apply/attack", 45);
        set_temp("apply/damage", 60);
        set_temp("armor", 53);
        setup();
}
void die()
{
        object ob;
        message_vision("$N口中吐出一顆夜明珠，肚皮往上一翻，$N死了。\n", this_object());
        ob = new("/d/npc/m_weapon/tan/item/zhenzhu");
        ob->move(environment(this_object()));
        destruct(this_object());
}