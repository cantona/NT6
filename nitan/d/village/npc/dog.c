// dog.c

inherit NPC;

void create()
{
        set_name("野狗", ({ "dog" }) );
        set("race", "走獸");
        set("age", 3);
        set("long", "一隻渾身髒兮兮的野狗。\n");
        set("str", 32);
        set("dex", 36);
        set("chat_chance", 6);
        set("chat_msg", ({
                (: this_object(), "random_move" :),
                "野狗用鼻子聞了聞你的腳。\n",
                "野狗在你的腳邊挨挨擦擦的，想討東西吃。\n",
                "野狗對著你搖了搖尾巴。\n",
                "野狗用後腿抓了抓自己的耳朵。\n" }) );
                
        set_temp("apply/attack", 10);
        set_temp("apply/armor", 3);

        setup();
}

int accept_object(object who, object ob)
{
        if( ob->id("bone") ) {
                set_leader(who);
                message("vision", name() + "高興地汪汪叫了起來。\n", environment());
                return 1;
        }
}