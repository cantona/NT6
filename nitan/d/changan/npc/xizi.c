//xizi.c

inherit NPC;

void create()
{
        set_name("戲子", ({"xi zi", "zi"}) );
        set("gender", "男性" );
        set("age", 25);
        set("long","一位裝扮極為奇特的戲子。\n");
        set("combat_exp", 10000);
        set("str", 25);
        set("attitude","heroism");
        set_skill("dodge",80);
        setup();
        carry_object("/d/changan/npc/obj/changpao")->wear();
        add_money("silver", 2);
}

void init()
{
        remove_call_out("says");
        call_out("says", random(3), this_object());
}

void says (object me)
{
        string *msgs = ({
                "$N在台上走了幾步。\n",
                "$N高聲唱着什麼。\n",
                "$N在空中使了一個花步，一個跟頭翻了過來。\n",
                "$N口中唸唸有詞。\n",
                "$N一個回身走向台角。\n",
                "$N鞠了個躬。\n",
                "$N翻了個空翻。\n",
        });
        message_vision (msgs[random(sizeof(msgs))],me);
        remove_call_out("says");
        call_out("says", random(40), me);
}