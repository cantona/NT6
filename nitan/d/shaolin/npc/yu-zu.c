// yu-zu.c

inherit NPC;

void close_door(object room);

void create()
{
        set_name("獄卒", ({ "yu zu", "zu" }) );
        set("long",
                "這是一個長相十分兇惡的獄卒，滿臉橫肉，眼神裡帶著股殺氣。\n");
        set("attitude", "peaceful");
        set("chat_chance", 1);
        set("chat_msg", ({
                "獄卒嘿嘿嘿地冷笑起來，當他發現你正注視著他的時候，扭頭惡狠狠瞪了你一眼。\n",
                "獄卒掏出一把雪亮的匕首，緩緩地削著自己又黑又長的手指甲，嘴裡哼著什麼。\n"
        }) );
        set("age", 50);
        set("combat_exp", 20000);
        set("max_jing", 500);
        set("max_qi", 500);
        set_skill("dodge", 40);
        set_skill("unarmed", 40);
        set_temp("apply/armor", 30);
        set_temp("apply/damage", 20);
        setup();
}

int accept_object(object who, object ob)
{
        object room;

        if( query("money_id", ob) && ob->value() >= 1000 )
        {
                tell_object(who, "獄卒說道：下水道裡老鼠真多，替我去打幾只，可別乘機溜了呵！\n\n");
                message_vision("獄卒左右張望了一下，偷偷替$N打開通往南邊的小門。\n", who);

                if(!( room = find_object("d/shaolin/jianyu1")) )
                        room = load_object("d/shaolin/jianyu1");

                set("exits/south", "d/shaolin/andao1", room);

                remove_call_out("close_door");
                call_out("close_door", 10, room);
                
                return 1;
        }

        return 0;
}

void close_door(object room)
{
        message("vision","獄卒飛快地站起身，上前一下把小門關了起來。\n", room);
        delete("exits/south", room);
}        
