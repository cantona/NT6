// /d/shenlong/chaser/hu.c
// Last Modified by winder on Jul. 12 2002

#include <ansi.h>
#include <room.h>

inherit NPC;

int random_steal();
int random_walk();
int is_valuable(object);
void dest_me()
{
        message_vision("$N急急忙忙離開了。\n",this_object());
        destruct(this_object());
}
void create()
{
        set_name("胡桂南", ({ "hu guinan", "hu" }) );
        set("nickname", "聖手神偷");
        set("long","這是一個身材瘦小的漢子。\n他上唇留了兩撇鼠須，眸子一翻，精光逼人。\n");
        set("gender", "男性" );
        set("age", 35);
        set("attitude", "peaceful");
        set("shen_type", 1);
        set("str", 25);
        set("int", 25);
        set("con", 25);
        set("dex", 30);

        set("max_qi", 800);
        set("max_jing", 400);      
        set("neili", 800);
        set("max_neili", 800);
        set("jiali", 30);
        set("combat_exp", 100000);
        set("score", 1000);

        set_temp("apply/attack",  20);
        set_temp("apply/defense", 40);
        set_temp("apply/damage",  20);

        set_skill("force", 80);
        set_skill("dodge", 100);
        set_skill("parry", 80);
        set_skill("cuff", 100);
        set_skill("hand", 100);
        set_skill("stealing", 200);

        set_skill("taixuan-gong", 80);
        set_skill("changquan", 80);
        set_skill("lingxu-bu", 80);
        set("env/wimpy",70);

        map_skill("dodge", "lingxu-bu");
        map_skill("parry", "changquan");
        map_skill("cuff", "changquan");
        map_skill("hand", "sanshou");
        map_skill("force", "taixuan-gong");
        prepare_skill("cuff", "changquan");
        prepare_skill("hand", "sanshou");


        set("chat_chance", 10);
        set("chat_msg", ({
                (: random_steal :),
                (: random_walk :)
        }) );

        set("stay_chance", 1);
        set("no_clean_up", 1);
        setup();
        if (clonep(this_object()))
                call_out("dest_me",600);
        carry_object(CLOTH_DIR"cloth")->wear();
}

void init()
{
        object ob;
        object *inv;

        ::init();

        if( !living(this_object()) || this_object()->is_fighting() ||
                this_object()->is_busy() ) return;

        if( interactive(ob = this_player()))
        {
                inv = filter_array(all_inventory(ob), "is_valuable", this_object());
                if( sizeof(inv) )
                {
                        remove_call_out("stealing");
                        if( query("unique_hold", ob) )
                        call_out("stealing", 1, ob, inv);
                }
        }
}

int stealing(object ob, object* inv)
{
        object obj,tester;
        int dp, ap;

//        tester = find_player("winder");
//        if (!tester) tester = find_player("qingyun");
        if( !living(this_object()) || this_object()->is_fighting() ||
                this_object()->is_busy() ) return 1;

        if( !ob || environment(ob) != environment() ) return 1;
        if( !query("no_fight", environment(ob)) )
        {
//                if(tester) tell_object(tester,"胡桂南告訴你：這裡可以戰鬥，我好怕怕，不偷了。\n");
                return 1;
        }
        obj = inv[random(sizeof(inv))];

        dp=query("combat_exp", ob);
        ap = (int)query_skill("stealing", 1);

        if (obj == ob) return 1;
//        if(tester) tell_object(tester, "胡桂南告訴你：我要偷"+ob->query("id")+"的"+obj->query("name")+"。\n");
// make 神照經 harder to steal, so player can dazuo more -:)  -winder
        if( query("name", obj) == "神照經" )
        {
                ap = ap * ap * ap / 1000;
        }
        else ap = ap * ap * ap;
        if( query("equipped", obj))dp*=10;
        if (userp(obj)) return random_walk();

        if( dp*2 + random(ap+dp)/2 >= dp*3 )
        {
                if( obj->move(this_object()) )
                        call_out("do_destroy", 1, obj);
        command("pat"+query("id", ob));
//                if(tester) tell_object(tester, "胡桂南告訴你：我偷到了"+ob->query("id")+"的"+obj->query("name")+"。\n");
                delete("unique_hold", ob);
                return random_walk();
        }

//        if(tester) tell_object(tester, "胡桂南告訴你：真倒霉，沒偷到。\n");
        remove_call_out("stealing");
        call_out("stealing", 60, ob, inv);
        // if fail, will try to steal again  -winder
        return 1;
}

void do_destroy(object obj)
{
        obj->move("/d/shenlong/cangku");
}

private int is_valuable(object ob)
{
        object *inv;

        if (ob->is_character()) return 0;
        if( query("value", ob)>100000 || ob->is_unique())return 1;
        if( ob->is_container() )
        {
                inv = all_inventory(ob);
                for(int i=0; i<sizeof(inv); i++)
                {
                        if(is_valuable(inv[i]))
                                return 1;
                }
        }

        return 0;
}

int random_walk()
{
        mapping exits, doors;
        string *dirs, dir, last_room;
        object here = environment();
        int temp;
        object tester = find_player("winder");
        if (!tester) tester = find_player("qingyun");

        if( !objectp(here) || is_fighting() || is_busy() ||
                !mapp(exits=query("exits", here)) || 
                query("jingli") < query("max_jingli") / 2 ) return 1;
        dirs = keys(exits);
        if( mapp(doors = here->query_doors()) )
        {
                dirs += keys(doors);
        }
        if( (temp = sizeof(dirs)) < 1 ) return 1;

        dir = dirs[random(temp)];
        if( temp >= 2 && stringp(last_room = query_temp("last_room")) )
        {
                if( exits[dir] == last_room )
                {
                        dirs -= ({dir});
                        dir = dirs[random(sizeof(dirs))];
                }
        }

        if( mapp(doors) && !undefinedp(doors[dir]) &&
                (doors[dir]["status"] & DOOR_CLOSED) )
                command("open " + dir);
        command("go " + dir);
        set_temp("last_room", base_name(here));

//        if(tester) tell_object(tester, "胡桂南告訴你：我從"+base_name(here) +"走到"+ base_name(environment()) +"。\n");
        return 1;
}

int random_steal()
{
        object ob;
        mixed inv;
        int i;
        object tester = find_player("winder");
        if (!tester) tester = find_player("qingyun");

        if( !living(this_object()) ) return 1;

        if( is_fighting() ) return 1;

        inv = all_inventory(environment());
        inv = filter_array(inv, (: userp :));
        if( !sizeof(inv) ) return random_walk();

        for(i=0;i<sizeof(inv);i++)
        {
                ob = inv[i];
                if( !query("unique_hold", inv[i]))continue;
                inv = filter_array(all_inventory(ob), "is_valuable", this_object());
                if( sizeof(inv) )break;
        }

        if( !sizeof(inv) ) return random_walk();
        remove_call_out("stealing");
        call_out("stealing", 1, ob, inv);

        return 1;
}
