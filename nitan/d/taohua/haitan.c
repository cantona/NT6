// Copyright (C) 2003, by Lonely. All rights reserved.
// This software can not be used, copied, or modified 
// in any form without the written permission from authors.

#include <ansi.h>
#include <room.h>

// inherit HARBOR;
inherit ROOM;

void create()
{
        set("short", "海灘");
        set("long", @LONG
這裏就是名震江湖的桃花島了。你放眼望去，除了海天交際處幾點海
鷗的影子若隱若現，四周見不到一個人影，不由得心裏一陣發慌。北面是
一片燦若雲霞的桃林，繁花似錦，五色繽紛，但靜悄悄的，似乎透着古怪。
桃林前立了一塊石碑(shibei)，上面似乎有些字跡，旁邊有一塊大石(sto
ne)，海邊泊着一艘大船(chuan)。
LONG );

        set("exits", ([
                "north" : __DIR__"thzhen1",
        ]));

        set("item_desc",([
                "shibei" : "
先天......伏羲......佔其地利......
......後天......文王......得其天時......\n",

                "stone" : "大石上方有一塊凹痕，象是一個扭曲的八卦形狀。\n",
                "chuan" : "這是桃花島對外聯繫的大船。島上的客人或弟子只要\n"
                          "上船(enter)就可以回中原。\n",
        ]));

        set("outdoors", "taohua");

        set("island", "桃花島");
        set("shape", "有一股夾着撲鼻花香的海風吹來。");
        set("navigate/locx", 30);
        set("navigate/locy", -180);

        set("coor/x", 9000);
        set("coor/y", -2000);
        set("coor/z", 0);
        setup();

}

void init()
{

        add_action("do_put", "put");
        add_action("do_pozhen", "pozhen");
        add_action("do_enter", "enter");
        add_action("do_pozhen","破陣");
}

int do_put(string arg)
{
        object me;
        string item, target;

        me = this_player();

        if (! arg || sscanf(arg, "%s in %s", item, target) != 2)
                return notify_fail("什麼？\n");

        if (! present("tie bagua", me))
                return notify_fail("什麼？\n");

        if (item != "tie bagua")
                return notify_fail("什麼？\n");

        if (target != "stone")
                return notify_fail("什麼？\n");

        message_vision("$N把鐵八卦放入大石凹痕裏\n", me);
        message_vision(HIW "只聽得軋軋數聲響，桃林向左右兩邊分開，一條小路出現在$N面前\n"
                       "$N連忙收起鐵八卦，走入桃林。桃林在$N身後又恢復了原狀。\n\n" NOR, me);

        me->move("/d/taohua/xiaojing");

        return 1;

}

int do_pozhen()
{
        object me;

        me = this_player();

        if (me->query_skill("qimen-wuxing", 1) < 120) 
        {
                me->receive_damage("jing", 50);
                me->receive_damage("qi", 50);
                message_vision("$N冥思苦想半晌不得其解，神困力疲，如同着了魔一樣，居然一步步走向桃林\n", me);
                me->move("/d/taohua/thzhen1");
    
        } else 
        {

                message_vision(HIW "$N凝思片刻，桃林的種種生克變化已全盤瞭然於胸，\n"
                               "仰天一聲長笑，袍袖一拂，掠入桃林，左一彎，右一轉，已影蹤不見\n" NOR, me);

        me->move("/d/taohua/xiaojing");
        }
        return 1;

}
int do_enter ( string arg )
{
        object ob ;
        string dir;
        if( !arg || arg !="chuan" ) 
        {
                tell_object(this_player() , "你要 enter 哪兒？\n" ) ;
                return 1 ;
        }
        ob = this_player () ;
        message_vision("船伕一見有人上船，忙叫了一聲：開船嘍！\n", ob);
        message_vision("船伕升起帆，船就向西方航行。\n", ob);
        ob ->move("/d/taohua/dahai") ;
        tell_object(ob, BLU "你在海上航行了很久很久.......\n" NOR ) ;
        call_out("rtaohua", 10 , ob );
        return 1 ;
}
void rtaohua( object ob )
{
        if (base_name(environment(ob)) != "/d/taohua/dahai")
                return;

        tell_object(ob , "大船終於抵達了中原的一個繁華城市。你走下船來。\n" ) ;
        ob->move ("/d/jiaxing/jiaxinggang") ;
}