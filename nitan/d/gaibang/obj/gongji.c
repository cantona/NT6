// Copyright (C) 2003, by Lonely. All rights reserved.
// This software can not be used, copied, or modified 
// in any form without the written permission from authors.
// gongji.c 公雞

inherit ITEM;
inherit F_FOOD;

int do_cut(string);
int do_wash(string);
int do_wrap(string);
int do_bake(string);
int do_clean(string);

void create()
{
        set_name("公雞", ({"gong ji", "ji", "chicken"}));
        set_weight(3000);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", "一隻肥大的公雞。\n");
                set("unit", "只");
                set("value", 50);
                set("food_remaining", 2);
                set("food_supply", 40);
        }

        setup();
}

void init()
{
        add_action("do_cut", "cut");
        add_action("do_cut", "po");
        add_action("do_wash", "wash");
        add_action("do_wash", "xi");
        add_action("do_wrap", "wrap");
        add_action("do_wrap", "guo");
        add_action("do_bake", "bake");
        add_action("do_bake", "kao");
        add_action("do_clean", "clean");
        add_action("do_clean", "bo");
}

// step1 剖公雞
int do_cut(string arg)
{
        object ji = this_object(), me = this_player();
        object weapon=query_temp("weapon", me);

        if ( !arg || arg == "") return 0;
        
        if (me->query_skill("cooking", 1) < 100)
                return notify_fail("你的基本廚藝太低了。\n");

        if ( arg == "公雞" || arg == "chicken" ) {

                if ( objectp(weapon) 
                 && (query("skill_type", weapon) != "sword"
                 || query("skill_type", weapon) != "blade")){
                        message_vision("$N用"+query("name", weapon)+"剖開"+query("name", ji)+"肚子。\n",me);
                        set("step", 1, ji);
                        set("long", "一隻剖開肚子的大公雞。\n", ji);
                        return 1;
                }

                else {
                        message_vision( "$N用手扯開一隻大公雞。\n", me);
                        set("fake", 1, ji);
                        return 1;
                } 
        }
        tell_object( me, "你要切什麼？\n");
        return 1;
}

// step2 洗內臟

int do_wash(string arg)
{
        object ji = this_object(), me = this_player();

        if ( !arg || arg == "") return 0;

        if ( arg == "公雞" || arg == "chicken" || arg == "內臟" || arg == "intestine" ) {
                message_vision("$N將"+query("name", ji)+"內臟洗剝乾淨。\n",me);
                set("long", "一隻肚子剖開，內臟洗乾淨的大公雞。\n", ji);

                if( query("step", ji) != 1 )
                        set("fake", 1, ji);
                else set("step", 2, ji);
                return 1;
        }
        tell_object( me, "你要洗什麼？\n");
        return 1;
}

// step3 裹水泥
int do_wrap(string arg)
{
        object ji = this_object(), me = this_player(), ni = present("shi ni", me);

        if ( !arg || arg == "") return 0;

        if ( arg == "公雞" || arg == "chicken" || arg == "泥" || arg == "mud" ) {
                set("mud", 1, ji);

                if (!objectp(ni)) {
                        message_vision("$N用水和了一團泥裹在"+query("name", ji)+"外。\n",me);
                        set("fake", 1, ji);
                }
                else {
                        message_vision("$N取出身上的濕泥，裹在"+query("name", ji)+"外。\n",me);
                        destruct(ni);
                }
                        
                set("long", "一隻裹在濕泥裏的公雞。\n", ji);

                if( query("step", ji) != 2 )
                        set("fake", 1, ji);
                else 
                        set("step", 3, ji);
                return 1;
        }

        tell_object( me, "你要裹什麼？\n");
        return 1;
}

// step4 烤雞
int do_bake(string arg)
{
        object ji = this_object(), fire, me = this_player();
        fire = present("fire", me);

        if ( !arg || arg == "") return 0;

        if ( arg == "公雞" || arg == "chicken" ) {
                if ( !objectp(present("fire", me)) ) {
                        tell_object( me, "你身上沒有火折，生不了火。\n");
                        return 1;
                } 
 
                else {
                        fire = present("fire", me);
                        message_vision("$N生火烤起"+query("name", ji)+"來。\n",me);
                        if( query("step", ji) != 3 )
                                set("fake", 1, ji);
                        else set("step", 4, ji);
                        set("cook_time", 0, ji);
                        remove_call_out("cooking");
                        call_out("cooking", 1, me, ji, 0);
                        return 1;
                }
        }
        tell_object( me, "你要烤什麼？\n");
        return 1;
}

// step5 等
int cooking(object me, object ji, int cook_time)
{
        set("cook_time", cook_time, ji);
//      message_vision( cook_time + "\n", me);
        if ( cook_time == 25 ) {
                if( !query("mud", ji)){
                        message_vision( "烤得一會兒，雞中透出香甜。\n", me);
                        set("long", "一隻烤得香甜的公雞。\n", ji);
                }
                else {
                        message_vision( "烤得一會兒，泥中透出香甜，濕泥漸漸乾透。\n", me);
                        set("long", "一隻裹着幹泥，烤得香甜的公雞。\n", ji);
                }
        }

        if ( cook_time == 50 ) {
                message_vision( "再烤得一會兒，你似乎嗅到什麼東西烤糊了。\n", me);
                if( !query("mud", ji) )
                        set("long", "一隻烤糊了的公雞。\n", ji);
                else
                        set("long", "一隻裹着幹泥，烤糊了的公雞。\n", ji);
        }

        if ( cook_time < 50) {
                cook_time = cook_time + 1;
                remove_call_out("cooking");
                call_out("cooking", 1, me, ji, cook_time);
        }

        return 1;
}

// step6 剝幹泥 
int do_clean(string arg)
{
        object ji = this_object(), me = this_player();
        object ob = new(__DIR__"jiaohua-ji");

        if ( !arg || arg == "") return 0;

        if( !query("mud", ji)) {
                if ( arg == "雞毛" || arg == "hair" ) {
                        message_vision( "$N剝去雞毛。\n", me);
                        ob->move(me);
                        set("fake", 1, ob);
                        return 1;
                }
                tell_object(me, "你要剝什麼？\n");
                return 1;
        }
                        
        if ( arg == "幹泥" || arg == "mud" ) {
                message_vision( "$N剝去幹泥，雞毛隨泥而落。\n", me);
                ob->move(me);

                if( query("step", ji) != 4 )
                        set("fake", 1, ob);
                else if( query("cook_time", ji)<36){
                        set("undercook", 1, ob);
                        set("fake", 1, ob);
                }
                else if( query("cook_time", ji)>40){
                        set("overcook", 1, ob);
                        set("fake", 1, ob);
                }
                destruct(ji);
                return 1;
        }
        tell_object( me, "你要剝什麼？\n");
        return 1;
}

