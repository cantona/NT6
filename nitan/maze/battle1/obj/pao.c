// This program is a part of NT MudLIB
//
// sdong, 3/18/2000

#include <ansi.h>
#include <armor.h>
#include <room.h>
inherit F_SSERVER;
inherit ITEM;
#define ORIGINAL "/maze/battle1/room_28.c"
int explode(object me, object ob);
int do_fire(string arg);
int do_aim(string arg);
string look_room(object me, object env);
int do_load(string arg);

mapping default_dirs = ([
        "north":        "北",
        "south":        "南",
        "east":                "東",
        "west":                "西",
        "northup":        "北邊",
        "southup":        "南邊",
        "eastup":        "東邊",
        "westup":        "西邊",
        "northdown":        "北邊",
        "southdown":        "南邊",
        "eastdown":        "東邊",
        "westdown":        "西邊",
        "northeast":        "東北",
        "northwest":        "西北",
        "southeast":        "東南",
        "southwest":        "西南",
        "up":                "上",
        "down":                "下",
        "out":                "外",
        "enter":        "裏",
        "in":                "裏",
        "left":                "左",
        "right":        "右",
]);

string day_event(){return NATURE_D->outdoor_room_event();}

void create()
{
        set_name(HIY"青銅炮"NOR, ({"pao","qingtong pao","bombgun"}));
        set_weight(1500000);
        set("value",150000);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("long",
"一座青銅鑄造的大炮，巨大的炮管昂然挺空，端的是威風八面。
久聞試劍山莊主人收集天下奇門兵器，沒想到連大炮都有，只是
不知好用不好用。\n\n");

                set("unit", "座");
                set("material", "bronze");
        }
        setup();
}

void init()
{
        add_action( "do_load", "load" );
        add_action( "do_aim", "aim" );
        add_action( "do_fire", "shoot" );
}

int do_load(string arg)
{
        object ob = this_object(), huoyao, dantou;
        object me = this_player();
        int exp_time;

        if ( !arg || (arg!="powder" && arg!="huo yao" && arg!="dan tou" ) )
           return notify_fail( "你想要加載什麼？\n");

        if( me->is_busy() ) return notify_fail("你還在忙着呢！\n") ;

        if( arg=="powder" || arg =="huo yao" )
        {
                huoyao = present("huo yao");
                if( !huoyao || !objectp(huoyao) )return notify_fail( "你想要加載什麼？\n");

                if( query_temp("yao_loaded") > 2 )return notify_fail("大炮已經裝滿火藥了。\n");

                if( huoyao && objectp(huoyao) && query("load", huoyao)>0 )
                {
                        message_vision("$N往炮筒里加入一些火藥。\n",me);
                        set("load",query("load",  huoyao)-1, huoyao);
                        if( query("load", huoyao) <= 0)destruct(huoyao);
                        addn_temp("yao_loaded",1);
                        me->start_busy(1);
                }
        }
        else if( arg =="dan tou" )
        {
                dantou = present("dan tou");
                if( !dantou || !objectp(dantou) )return notify_fail( "你想要加載什麼？\n");

                if( query_temp("dan_loaded") > 0 )return notify_fail("大炮已經裝有彈頭了。\n");

                message_vision("$N往炮筒里加入一枚彈頭。\n",me);
                destruct(dantou);
                addn_temp("dan_loaded",1);
                me->start_busy(1);
        }

        return 1;
}



string look_room(object me, object env)
{
                  int i;
                  object *inv;
                  mapping exits;
                  string str, *dirs;

                  if( !env ) {
                                         return "你的四周灰濛濛地一片，什麼也沒有。\n";
                  }
                  str = sprintf( "%s - %s\n    %s%s",
                                         query("short", env),
                                         wizardp(me)? file_name(env): "",
                                         query("long", env),
                                         query("outdoors", env)?NATURE_D->outdoor_room_description():"");

                  if( mapp(exits=query("exits", env))){
                                         dirs = keys(exits);
                                         for(i=0; i<sizeof(dirs); i++)
                        if( (int)env->query_door(dirs[i], "status") & DOOR_CLOSED )
                                                                                  dirs[i] = 0;
                                         dirs -= ({ 0 });
                                         if( sizeof(dirs)==0 )
                                                                str += "    這裏沒有任何明顯的出路。\n";
                                         else if( sizeof(dirs)==1 )
                                                                str += "    這裏唯一的出口是 " + BOLD + dirs[0] + NOR + "。\n";
                else
                        str += sprintf("    這裏明顯的出口是 " + BOLD + "%s" + NOR + " 和 " + BOLD + "%s" + NOR + "。\n",
                                implode(dirs[0..sizeof(dirs)-2], "、"), dirs[sizeof(dirs)-1]);
                  }
//      str += env->door_description();

        inv = all_inventory(env);
        for(i=0; i<sizeof(inv); i++) {
                                         if( inv[i]==me ) continue;
                                         if( !me->visible(inv[i]) ) continue;
                                         if( objectp(query("rider", inv[i])))continue;
                                         else delete("rider", inv[i]);
                                         if( objectp(query("rided", inv[i]))){
                                                                str += "  " + inv[i]->short() + "騎在" +
                                                                (query("rided", inv[i]))->name()+"上";
                                         if( stringp(query_temp("exit_blocked", inv[i])) )
                                                                str+="擋着往"+query_temp("exit_blocked", inv[i])+
                                                                "去的路";
                                                                str += "\n";
                                         }
                                         else {
                                                                if( stringp(query_temp("exit_blocked", inv[i])) )
                                                                str+=""+inv[i]->short()+"擋着往"+query_temp("exit_blocked", inv[i] )
                                                                                  +"去的路\n";
                                                                else
                                                                str += "  " + inv[i]->short() + "\n";
                                                                delete("rided", inv[i]);
                                         }
                  }

                  return(str);
}


int do_aim(string arg)
{
        object me = this_player();
        object cur_target, target;
        string str, dest;
        mapping exit;

        if( me->is_busy() ) return notify_fail("你還在忙着呢！\n") ;

        cur_target = query_temp("target");

        if( !cur_target ){
                cur_target = find_object(ORIGINAL);
                if( !cur_target )cur_target=load_object(ORIGINAL);
                if (!objectp(cur_target))return notify_fail("找不到目標。\n");
        }

        if( arg=="down" || arg=="up" || arg=="out" || arg=="enter" )return notify_fail("這個方向沒法打到。\n");

        if( arg )
        {
                if( !mapp(exit=query("exits", cur_target)) || undefinedp(exit[arg])){
                        return notify_fail("這個方向沒有出路。\n");
                }

                if( !cur_target->valid_leave(me, arg) ) notify_fail("這個方向太遠了。\n");

                dest = exit[arg];

                if( !(target = load_object(dest)) )
                        return notify_fail("無法移動。\n");
        }
        else target = cur_target;

        set_temp("target",target);

        str = look_room(me, target);
        tell_object(me, str+"\n");
        if(arg)
                message_vision(HIW"$N將炮口緩緩向"+default_dirs[arg]+"轉，瞄準了"+query("short", target)+"。\n"NOR,me);

        me->start_busy(1);

        return 1;
}

int do_fire(string arg)
{
        object ob = this_object();
        object me = this_player();
        int exp_time;

    if( query_temp("fired", ob))return notify_fail("你一拉才發現此炮已被引燃了，就快發射了！\n");
        if( query_temp("dan_loaded", ob) <= 0)return notify_fail("炮還沒有上彈頭呢！\n");
        if( query_temp("yao_loaded", ob)<3)return notify_fail("炮還沒裝滿\彈藥呢！\n");

        message_vision("$N伸手用力一拉，拉開了$n導火索。\n", me,ob);
        set_temp("fired", 1, ob);
        set_temp("owner", me, ob);
        call_out("explode", 1 + random(5), me, ob);

        return 1;
}

int explode(object me, object ob)
{
        object *victims, env, owner;
        int i,damage;
        string str;

                delete_temp("fired", ob);
                delete_temp("owner", ob);
                delete_temp("dan_loaded", ob);
                delete_temp("yao_loaded", ob);

        env = query_temp("target");
        if( !env ){
                env = find_object(ORIGINAL);
                if( !env )env=load_object(ORIGINAL);
                if (!objectp(env))return notify_fail("找不到目標。\n");
        }

        message_vision(HIY"只聽的一聲驚天動地的爆響，$N"+HIY"發射了，彈頭帶着一道火線飛向"+query("short", env)+HIY"，四周一片硝煙禰漫。\n"NOR,ob);

        owner = query_temp("owner");

        if( !owner || !objectp(owner) )
        {
                if(me && objectp(me) )
                        owner=me;
                else owner=ob;
        }

        tell_room(env,HIR"只聽的一聲驚天動地的爆響，一發炮彈落地，四周一切立刻被炸得灰飛煙滅！\n"NOR, me);

        if( query("no_fight", env)){
                return 0;
        }

        victims = all_inventory(env);

        for (i=0; i<sizeof(victims); i++) {
                   if (!living(victims[i]) || victims[i]==me ) continue;
                damage= 4000+random(8000);
        victims[i]->receive_damage("qi", damage,  owner);
        victims[i]->receive_wound("qi", random(damage), owner);
        str=COMBAT_D->status_msg(query("qi", victims[i])*100/query("max_qi", victims[i]));

                message_vision(HIR"$N被炸得人仰馬翻！\n"NOR,victims[i]);
                message_vision(HIR"你遠遠看到"+query("name", victims[i])+"被炸得人仰馬翻！\n"NOR,ob);
        message_vision("($N"+str+")\n", victims[i]);
                message_vision(HIR"你遠遠看到("+query("name", victims[i])+str+")\n",ob);
        }

        if( !query("th_buzhen", env))return 1;

        set("long",query("org_desc",  env), env);
        set("exits",query("org_exits",  env), env);
        set("cost",query("org_cost",  env), env);
        delete("org_desc", env);
        delete("org_cost", env);
        delete("org_exits", env);
        delete("th_buzhen", env);
        delete("th_pozhen", env);
        delete("th_zhen_owner", env);

        return 1;
}
