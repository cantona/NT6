// Copyright (C) 2003-2004, by Lonely. All rights reserved.
// This software can not be used, copied, or modified 
// in any form without the written permission from authors.

#include <ansi.h>
inherit ROOM;

void recreate();

string *enter_msg = ({
        HIB+"\n你只覺得眼前一花，突然什麼也聽不見，什麼也看不見......\n\n"+NOR,
        HIB+"只覺得身體不斷的下墜......\n\n"+NOR,
        HIB+"墜向無盡的黑暗......\n\n"+NOR,
        HIB+"忽然仿佛一只大手托了你一下......\n\n"+NOR,
        HIB+"冥冥中隱約傳來陣陣叮叮當當碰撞聲......\n\n"+NOR,
        HIB+"你睜眼一看，發現自己已置身于一個喧囂而似乎並不陌生的世界......\n\n"+NOR,
});

void entering_world(object me, int n);

void create()
{
        set("short", HIW "\n\n                無        間        道" NOR);
        set("long", HIW "\n"
"這裡是天地人三界不管的終極無間，這裡沒有任何出路，只有黑暗。\n\n" NOR);

        set("no_magic", 1);
        setup();
}

void init()
{
        set("poem_said", 0);
        add_action("do_say", "say");
        add_action("do_enter", "enter");
        add_action("do_smash", "smash");
}

int do_say(string arg)
{
        string dir;
        object ob;

        if( ! arg || arg == "" ) return 0;

        if( arg == "潛能無限，精意神通，身居禍福，自我主宰！" 
        &&  (int)query("poem_said") != 1 )
        {
                message_vision(HIW "\n只聽$N" HIW "猛然高聲喝道：“潛能無"
                               "限，精意神通，身居禍福，自我主宰！”\n" NOR + 
                               HIR "\n$N" HIR "話音剛"
                               "落，地面突然「轟隆隆」晃動了幾下。眼前出"
                               "現了一個鏡子。\n\n"
                               NOR, this_player());
                ob = new("/d/death/obj/wujian");
                ob->move(this_player(), 1); 
                message_vision(HIW "突然間電閃雷鳴，宇宙無敵之劍無間閃電伴隨著道道閃電穿進$N的懷中！\n", this_player());     
                this_object()->recreate();
                set("poem_said", 1);
                return 1;
        }

        if( arg == "潛能無限，精意神通，身居禍福，自我主宰！" && (int)query("poem_said") == 1 )
        {
                write(HIC "\n你對著黑暗一聲猛喝，聲音在司內回盪了好一陣才消逝。\n" NOR);
                return 1;
        }
}

void recreate()
{
        set("short", HIW "\n\n                無        間        道" NOR);
        set("long", HIW "\n"
"這裡是天地人三界不管的終極無間，這裡沒有任何出路，只有黑暗。\n"
"前方是一面足有一人高的大銅鏡(mirror)。\n\n" NOR);

        set("item_desc", ([
                "大銅鏡": "一面足有一人高的大銅鏡，奇怪的是鏡子裡一片混沌，照不出任何人影。\n",
                "銅鏡"  : "一面足有一人高的大銅鏡，奇怪的是鏡子裡一片混沌，照不出任何人影。\n",
                "mirror": "一面足有一人高的大銅鏡，奇怪的是鏡子裡一片混沌，照不出任何人影。\n",
        ]));
        set("objects", ([
                "/d/death/npc/ghost" : 21,
        ]));
        set("poem_said", 1);
        set("no_magic", 1);
        setup();
}


int do_enter(string arg)
{
        object me = this_player();
        
        if (! query("poem_said")) return 0;

        if (objectp(present("ghost", environment(me)))) 
                return notify_fail("你還是先解決掉這些亡魂吧！\n");
                
        set_temp("entering_world", 1, me);
        message_vision("$N向著銅鏡的方向走去。\n",me);
        call_out("entering_world", 1, me, 0);
        return 1;
}

void entering_world(object me, int n)
{
        object item; 

        remove_call_out("entering_world");

        tell_object(me, enter_msg[n]);

        if (n == sizeof(enter_msg) - 1)
        {
                delete_temp("entering_world", me);
                tell_room(environment(me), sprintf(HIY"銅鏡中放出一道金光罩向%s，隨後%s不見了。\n"NOR,
                          me->name(), me->name()), ({ me }));
                          
                me->clear_condition();
 
                foreach (item in all_inventory(me))
                {
                        message_vision("$N丟下了$n。\n", me, item);
                        if (item->is_character())
                                item->move(environment(me));
                        else
                                destruct(item);
                }

                // 選擇特殊技能
                UPDATE_D->zhuan_player(me);

                me->move("/d/city/wumiao");
                set("startroom", "/d/city/wumiao", me);
                tell_room(environment(me),me->name()+"突然出現在眼前。\n",({me}));                                
                me->save();
                return;                
        }
        else
        {
                call_out("entering_world", 3, me, n + 1);
                return;
        }
}

int do_smash(string arg)
{
        object ob, weapon;
        object me = this_player();

        if( !objectp(weapon=query_temp("weapon", me)) || 
            query("id", weapon) != "wujianshandian" )
                return notify_fail("你沒有裝備無間閃電，無法使用其 smash 神力！\n");

        if (! arg)
                return notify_fail("指令格式: smash <living>\n");
        
        ob = present(arg, environment(me));
        if (! ob )        
                return notify_fail("找不到這個生物。\n");

        message_vision(HIM"無間閃電化作無數閃電擊向"+query("name", ob)+"...\n\n"
                       NOR, me);        
        if (! ob->is_character())
        {
                message_vision(HIM + ob->name() + HIM "從這個世界上消失了...\n\n"
                               NOR, me);
                destruct(ob);
                return 1;
        }
        
        ob->die();
        
        return 1;
}

