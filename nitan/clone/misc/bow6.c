// Updated by Lonely

#include <ansi.h>
#include <weapon.h>
inherit HAMMER;

mapping exits_name=([
        "east":            "東方",
        "south":           "南方",
        "west":            "西方",
        "north":           "北方",
        "eastup":          "東上方",
        "southup":         "南上方",
        "westup":          "西上方",
        "northup":         "北上方",
        "eastdown":        "東下方",
        "southdown":       "南下方",
        "westdown":        "西下方",
        "northdown":       "北下方",
        "northeast":       "東北方",
        "northwest":       "西北方",
        "southeast":       "東南方",
        "southwest":       "西南方",
        "up":              "上方",
        "down":            "下方",
        "enter":           "裡邊",
        "out":             "外邊",
]);

int do_shoot(string id, object me, object bow, object room, string what, int m);
string exits_reverse(string dir);

string exits_reverse(string dir)
{
         if (dir == "east") return "west";
         if (dir == "west") return "east";
         if (dir == "south") return "north";
         if (dir == "north") return "south";
         if (dir == "eastup") return "westdown";
         if (dir == "westup") return "eastdown";
         if (dir == "southup") return "northdown";
         if (dir== "northup") return "southdown";
         if (dir == "eastdown") return "westup";
         if (dir == "westdown") return "eastup";
         if (dir == "southdown") return "northup";
         if (dir == "northdown") return "southup";
         if (dir == "northeast") return "southwest";
         if (dir == "northwest") return "southeast";
         if (dir == "southwest") return "northeast";
         if (dir == "southeast") return "northwest";
         if (dir == "up") return "down";
         if (dir == "down") return "up";
         if (dir == "enter") return "out";
         if (dir == "out") return "enter";

         return "";
}

void create()
{
        set_name(HIG"水晶連弩"NOR,({ "crystal bow","bow","gong" }) );
        set_weight(16000);
        if(clonep())
                set_default_object(__FILE__);
        else {
                set("long", "一把寒鐵制的組合弓弩，威力巨大無比。\n");
                set("unit", "把");
                set("value", 80000);
                set("consistence", 75);
                set("dam", 1400);         
                set("no_put", 1);
                set("is_bow", 1);
                set("wield_msg", HIY"$N將$n"HIY"從肩上取下，握在手中。\n"NOR);
                set("unwield_msg", HIY"$N將$n"HIY"橫跨，背在肩上。\n"NOR);
                set("material", "iron");
        }
        init_hammer(10);
}

void init()
{
        add_action("do_she", "she");
}

int do_she(string arg)
{
    object me = this_player(), bow, ob, room;
           int i, n, m;
           string what;
           mapping exits;
   
    room = environment(me);
           bow=query_temp("weapon", me);

    if( query("no_fight", room) )
                   return notify_fail("這裡不許戰鬥！\n");

           if( !bow || !query("is_bow", bow) )
                   return notify_fail("弓還在背上呢，怎麼射呀！\n");

           if( me->query_str()<query("dam", bow)/20 )
                   return notify_fail("你使盡吃奶的力氣也拉不開弓來，看來力氣不夠！\n");  

           if( query("consistence", bow)<0 )
           {
                    message_vision(HIW"$N手中的"+query("name", bow)+HIW"“□”地一聲斷了！\n",me);
                    bow->unequip();
                    destruct(bow);
                    return 1;
           }

           if (me->is_busy())
                   return notify_fail("你現在正忙著呢！\n");

           if( query("qi", me)<200 || query("jing", me)<100 )
                   return notify_fail("你現在精氣不夠充盈，硬拉功怕有危險啊！\n"); 

           if (! arg || sscanf(arg, "%s %d", what, n) != 2)
                   return notify_fail("不會射箭？找人家教教你吧！\n");
                   
            if( n>query("dam", bow)/200)n=query("dam", bow)/200;
            
            for (i = 0; i < n; i++)
             {
            if( objectp(room) && mapp(exits=query("exits", room)) && stringp(exits[what]) )
                      {
                               m = i + 1;
                room = find_object(exits[what]);
                      }

        }

        if (room == environment(me))
                      return notify_fail("看清楚點，朝哪裡射呀你？\n");
                      
        if (objectp(room))
             {
            if( query("have_quest", room) || query("no_fight", room) )
                              return notify_fail("那裡有神明佐佑，不容你胡來也！\n"); 
                              
            "/cmds/std/look.c"->look_room(me, room);  
                      
                      message_vision(HIY"$N從箭囊內抽出一支"HIW"羽箭"HIY"，搭在"
                                       +query("name", bow)+HIY"上，隨後立了一個霸王上弓式，\n朝"HIR
                                       + exits_name[what] + HIY"把弓拉滿.......\n"NOR, me);
                                       
            tell_object(all_inventory(room), HIB"你覺得一股猛烈的殺機從"HIR
                                       + exits_name[exits_reverse(what)] + HIB"傳來！！\n"NOR);

                      tell_object(me, HIR + exits_name[what] + HIW"的情景你一目了然，"
                                + "你把利箭漸漸瞄準了──>\n"NOR);   
                      me->start_busy(2 + random(3));  
            input_to("do_shoot", me, bow, room, what, m);
             } else return notify_fail("看清楚點，朝哪裡射呀你？\n");  

            return 1;
}

int do_shoot(string id, object me, object bow, object room, string what, int m)
{
            object ob, obj, *env;
            int damage, ratio;

            if (! id || id == "") 
            {
                     message_vision("$N嘆了口氣，將箭從"+query("name", bow)+"上又取了下來。\n",me);
                     return 1;
            }

            if (objectp(ob = present(id, room)) && ob->is_character())
            {
                     if( query("is_quest", ob) && query("killer", ob) != query("id", me) )
                     {
                              tell_object(me,"“砰”地一聲，你被"+query("name", bow )
                                          + "震了一下，看來目標不好惹呀！\n");
                              return 1;
                     }

                     if( playerp(ob) && query("age", ob)<18 )
                     {
                              tell_object(me,"“砰”地一聲，你被"+query("name", bow )
                                          + "震了一下，原來你的目標是小朋友呀！\n");
                              return 1;
                     }

                      message_vision(HIY"$N“嗖”地一箭朝"HIR + exits_name[what] + HIY"射了出去！\n", me);

                      damage=query("dam", bow)*(5+me->query_str())/(m*5+ob->query_dex());
                      if (damage < 100) damage = 100;
                      if (damage > 1500) damage = 1500;
                      damage = damage + random(damage);
                      
                me->want_kill(ob);

                     if (random(me->query_skill("arrow", 1)) > ob->query_skill("dodge", 1) / 4
                  || random(query("combat_exp", me))>query("combat_exp", ob)*2 )
                     {
                              if (damage > 2000)
                                message_vision(HIY"“嗖”地一聲，一枚"HIW"羽箭從"HIR
                                                   + exits_name[exits_reverse(what)]
                                                   + HIY"飛來，"HIR"“噗嗤”"HIY"一聲紮在$N"HIR"額頭"HIY"上！\n"NOR,
                                                   ob);
                              else if (damage > 1500)
                                message_vision(HIY"“嗖”地一聲，一枚"HIW"羽箭從"HIR
                                                   + exits_name[exits_reverse(what)]
                                                   + HIY"飛來，"HIR"“噗嗤”"HIY"一聲紮在$N"HIR"胸口"HIY"上！\n"NOR,
                                                   ob);
                              else if (damage > 1000)
                                message_vision(HIY"“嗖”地一聲，一枚"HIW"羽箭從"HIR
                                                   + exits_name[exits_reverse(what)]
                                                   + HIY"飛來，"HIR"“噗嗤”"HIY"一聲紮在$N"HIR"肩膀"HIY"上！\n"NOR,
                                                   ob);
                              else if (damage > 500)
                                message_vision(HIY"“嗖”地一聲，一枚"HIW"羽箭從"HIR
                                                   + exits_name[exits_reverse(what)]
                                                   + HIY"飛來，"HIR"“噗嗤”"HIY"一聲紮在$N"HIR"小腿"HIY"上！\n"NOR,
                                                   ob);
                              else
                                message_vision(HIY"“嗖”地一聲，一枚"HIW"羽箭從"HIR
                                                   + exits_name[exits_reverse(what)]
                                                   + HIY"飛來，"HIR"“噗嗤”"HIY"一聲紮在$N"HIR"手臂"HIY"上！\n"NOR,
                                                   ob);
                              damage = damage / 4 + random(damage / 2);                                  
                              ob->receive_damage("qi", damage, me);
                              
                              if( damage>query_temp("apply/armor", ob) )
                                      ob->receive_wound("qi",damage-query_temp("apply/armor", ob),me);
                              
                              COMBAT_D->report_status(ob, random(2));  
                                      tell_object(me, HIR"嘿嘿，目標應聲而倒，真是好箭法！\n"NOR);

                              ratio=query("combat_exp", me)/100;
                              ratio=query("combat_exp", ob)/ratio;
                              if (ratio > 1000) ratio = 1000;
                              if (ratio < 10) ratio = 10;
                              if (! playerp(ob))
                                      me->improve_skill("arrow", 
                                              random((damage / 2 + me->query_int() / 10) * ratio / 100), 0);

                      } else
                      if (random(3) > 0)
                      {
                               env = all_inventory(room);
                               obj = env[random(sizeof(env))];
                               if (obj != ob && obj->is_character())
                               {
                                       damage=query("dam", bow)*(5+me->query_str())/(m*5+obj->query_dex());
                                       if (damage < 100) damage = 100;
                                       if (damage > 1500) damage = 1500;
                                       damage = damage / 2 + random(damage / 2); 

                                       if (damage > 2000)
                                        message_vision(HIY"“嗖”地一聲，一枚"HIW"羽箭從"HIR
                                                           + exits_name[exits_reverse(what)]
                                                           + HIY"飛來，"HIR"“噗嗤”"HIY"一聲紮在$N"HIR"額頭"HIY"上！\n"NOR,
                                                           obj);
                                       else if (damage > 1500)
                                        message_vision(HIY"“嗖”地一聲，一枚"HIW"羽箭從"HIR
                                                           + exits_name[exits_reverse(what)]
                                                           + HIY"飛來，"HIR"“噗嗤”"HIY"一聲紮在$N"HIR"胸口"HIY"上！\n"NOR,
                                                           obj);
                                       else if (damage > 1000)
                                        message_vision(HIY"“嗖”地一聲，一枚"HIW"羽箭從"HIR
                                                           + exits_name[exits_reverse(what)]
                                                           + HIY"飛來，"HIR"“噗嗤”"HIY"一聲紮在$N"HIR"肩膀"HIY"上！\n"NOR,
                                                           obj);
                                       else if (damage > 500)
                                        message_vision(HIY"“嗖”地一聲，一枚"HIW"羽箭從"HIR
                                                           + exits_name[exits_reverse(what)]
                                                           + HIY"飛來，"HIR"“噗嗤”"HIY"一聲紮在$N"HIR"小腿"HIY"上！\n"NOR,
                                                           obj);
                                       else
                                        message_vision(HIY"“嗖”地一聲，一枚"HIW"羽箭從"HIR
                                                           + exits_name[exits_reverse(what)]
                                                           + HIY"飛來，"HIR"“噗嗤”"HIY"一聲紮在$N"HIR"手臂"HIY"上！\n"NOR,
                                                           obj);
                                damage = damage / 4 + random(damage / 2);
                                obj->receive_damage("qi", damage, me);
                                if( damage>query_temp("apply/armor", obj) )
                                        obj->receive_wound("qi",damage-query_temp("apply/armor", obj),me);
                                COMBAT_D->report_status(obj, random(2));  

                                tell_object(me,HIB"糟糕，箭好象射到別人了，好好練箭法吧！\n"NOR);
                               } else
                               {
                                message_vision(HIY"一枚"HIW"羽箭從"HIR + exits_name[exits_reverse(what)]
                                                   + HIY"飛來，"HIR"“嗖”"HIY"地一聲從$N"HIR"耳邊"NOR"飛過！\n"NOR,
                                                   ob);
                                tell_object(me, HIW"哎呀，箭射飛了，好好練箭法吧！\n"NOR);
                               }
                      } else
                      {
                        message_vision(HIY"一枚"HIW"羽箭從"HIR + exits_name[exits_reverse(what)]
                                           + HIY"飛來，"HIR"“嗖”"HIY"地一聲從$N"HIR"耳邊"NOR"飛過！\n"NOR,
                                           ob);
                        tell_object(me,HIW"哎呀，箭射飛了，好好練箭法吧！\n"NOR);
                      }
            } else
                     tell_object(me, "可惜，目標現在不在那裡了，你的箭飛了耶！\n");

             addn("consistence", -1, bow);
             me->receive_damage("jing", 50, me);
             me->receive_damage("qi", 100, me);

             return 1;
}    
