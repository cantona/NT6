// Room: /d/baihuagu/shanpo2.c
// Last Modified by Winder on Mar. 5 2001

#include <ansi.h>;
#include "yangfeng.h";
inherit ROOM;
void create()
{
        set("short", GRN"山谷中"NOR);
        set("long", 
HIY"這是一面山谷。由於山坡向南，阻住了山風，加之地下礦藏
豐富，所以地氣極暖，百花先放。此處架着幾個木架，託着七八
個蜂巢。但見羣蜂爭舞，到處都是嗡嗡聲，給靜謐的山谷帶來了
無限生氣。山谷中高樹林立，還有很多灌木，想來谷中物產極多，
偶爾可見一兩個挖掘草藥的農人。\n"NOR); 
        set("outdoors", "baihuagu");
        set("count", 10);
        set("exits", ([
                "westup" : __DIR__"baihuagu2",
                "west"   : __DIR__"shanpo4",
                "north"  : __DIR__"shanpo5",
                "south"  : __DIR__"shanpo6",
        ]));
        set("objects", ([
                __DIR__"npc/yubee": 2
        ]));
        set("item_desc", ([
                "蜂巢" : "這是一個巨大的蜂巢，裏面很多密蜂正忙着釀蜜。\n",
        ]));
        set("coor/x", -390);
        set("coor/y", -360);
        set("coor/z", -10);
        setup();
}
void init()
{
        add_action("do_dig","dig");
        add_action("do_full","full");
        add_action("do_yang","yang");
        add_action("do_getmi","getmi");
        add_action("do_quit","quit");
        add_action("do_quit","exit");
        add_action("do_quit","exercise");
        add_action("do_quit","dazuo");
        add_action("do_quit","learn");
        add_action("do_quit","xue");
        add_action("do_quit","tuna");
        add_action("do_quit","persuade");
        add_action("do_quit","quanjia");
        add_action("do_quit","practice");
        add_action("do_quit","lian");
        add_action("do_quit","study");
        add_action("do_quit","du");
        add_action("do_quit","teach");
        add_action("do_quit","jiao");
}
int do_dig(string arg)
{
        object me;
        object food;
        me=this_player();
        if( query("food", me) >= me->max_food_capacity() )
        {
                message_vision( HIC"$N正要挖什麼，突然老頑童跑了過來，邪惡地笑了一下，猛然從身後取出一支茯苓，望$N嘴中灌過去，口中叫道：我叫你吃！！把$N灌得頭暈眼花，吃的都吐了出來。老頑童得意地笑了，又一溜煙地跑了。\n"NOR,me);
                return 1;
        }
        else
        {
                if (query("count") > 0)
                {
                        message_vision("$N挖了一會兒，挖到一顆首烏。當下坐下，吃將起來。\n",me);
                        addn("food", 30, me);
                        addn("count", -1);
                }
                else message_vision("$N挖了一會兒，啥都沒有。\n",me);
                return 1;
        }
}
int do_full(string arg)
{
        object me;
        me=this_player();
        if( query("water", me) >= me->max_water_capacity() )
        {
                message_vision( HIY"$N意猶未盡地拍了拍肚子，手伸向蜂巢——突然慘叫一聲，整個人都跳了起來，只見整隻手都膨脹起來。\n"NOR,me);
                return 1;
        }
        else
        {
                if (query("count") > 0)
                {
                        message_vision("$N從蜂巢中取了些蜂漿，喝了起來。\n",me);
                        addn("water", 30, me);
                        addn("count", -1);
                }
                else message_vision("$N掏了一會兒，啥都沒有。\n",me);
                return 1;
        }
}

int do_getmi(string arg)
{
        object me;
        me=this_player();
        if( query_temp("marks/getmi", me) )
        {
                message_vision( HIY"$N歡叫一聲，從蜂巢中取出一罐蜜。\n"NOR,me);
                new("/d/baihuagu/obj/mi")->move(me);
                set_temp("marks/getmi", 0, me);
                return 1;
        }
        else
        {
                message_vision( HIR"$N嘿嘿一笑，賊忒兮兮地向蜂巢湊去，正要有所行動，突聽嗡的幾聲，幾隻玉蜂從裏面衝將而出，把$N蜇得滿頭大包！\n"NOR,me);
                return 1;
        }
}
