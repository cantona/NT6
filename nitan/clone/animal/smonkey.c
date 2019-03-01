// /d/shenlong/npc/smonkey.c
// Last Modified by winder on Aug. 1 2002

inherit NPC;

void create()
{
        set_name("小猴子", ({ "monkey", "hou", "houzi" }) );
        set("race", "走獸");
        set("age", 2+random(3));
        set("long", "一只機靈的小猴子，眼巴巴的看著你，大概想討些吃的。\n");
        set("attitude", "peaceful");

        set("limbs", ({ "頭部", "身體",  "前腿", "後腿", "尾巴" }) );
        set("verbs", ({ "bite", "claw" }) );

        set_skill("dodge", 10+random(20));

        set("combat_exp", 350+random(200));
        set_temp("apply/attack", 6+random(8));
        set_temp("apply/defense", 6+random(4));
        set_temp("apply/armor", 2);

        setup();

        set("chat_chance", 8);
        set("chat_msg", ({
                "一只小猴子忽然跑過來，向你作了個揖。\n",
                "一只小猴子嘰嘰喳喳跑了過來。\n",
                "小猴子蹦蹦跳跳地跑開了。\n",
                "小猴子搖搖尾巴跑開了。\n",
        }) );
}

int accept_object(object me, object obj)
{
        object ob;

        if( query("food_supply", obj) && obj->value() >= 0){
                command("jump"+query("id", me));
                say("小猴子三兩下便把"+query("name", obj)+"吃得幹幹凈凈。\n");

                remove_call_out("destroy_it");
                call_out("destroy_it", 1, obj);

                if( query("id", obj) != "banana" )
                        return 1;

                message_vision("小猴子拉扯$N的衣服，示意$N跟著它。\n", me);
                message("vision", me->name() + "隨著小猴子走向深山，左拐右拐地一下子便看不見了。\n", environment(me), ({me}));
                message("vision", "另一只小猴子走了過來。\n", environment(me),({me}));
                write("你隨著小猴子在山裡走著，東轉西轉地搞得你迷失了方向。\n");
                write("走了良久，小猴子把你帶到一片密林前。\n");
                write("緊接著，小猴子便往野林裡跑了。\n");
                me->move("/d/quanzhou/milin");
                message("vision", me->name()+"跟著小猴子走了過來。\n", environment(me), ({me}) );
                return 1;
        } else {
                say("小猴子把"+query("name", obj)+"接了過來，玩弄了幾下，似乎不懂有什麼用。\n");
                command("angry");
                command("kick"+query("id", me));
                if( query("money_id", obj)){
                        ob = new(base_name(obj));
                        ob->set_amount((int)obj->query_amount());
                        ob->move(environment(me));
                        say("小猴子把"+query("name", obj)+"丟到地上。\n");}
                remove_call_out("drop_it");
                call_out("drop_it", 1);
        }

        return 1;
}

void drop_it()
{
        command("drop all");
}

void destroy_it(object obj)
{
        destruct(obj);
}

void init()
{
        object me = this_player();

        ::init();

        if( interactive(me) && living(me) )
        {
                command("look"+query("id", me));
                message_vision("小猴子神秘地對$N眨了眨眼睛，“吱，吱，吱”叫了幾聲！\n", me);
        }
}
