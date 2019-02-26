// Copyright (C) 2003, by Lonely. All rights reserved.
// This software can not be used, copied, or modified 
// in any form without the written permission from authors.

#include <ansi.h>
#include <mudlib.h>
#include "localtime.h"

inherit ROOM;


string* dirs = ({
        "謙", "乾", "坤", "屯", "蒙", "需", "訟", "師", "比", "小畜", "履", 
        "泰", "否", "同人", "大有"
});


void create() {
        set("short", "地道");
        set("long", @LONG
這是一條石砌的甬道，直通向黃藥師夫人馮氏靈柩所在之處。甬道兩
側每隔約莫五六步就有一盞盛滿清油的綠玉燈靜靜燃燒。甬道中光線十分
昏暗，但勉強也可見物。甬道盡頭有一扇石門(men)，門邊嵌着一塊鐵板(
tieban)。
LONG );
        
        set("item_desc", ([
                "men"    :
"\n門上刻着數十個卦像，排成整整齊齊的一個方陣，
你湊近仔細一看，原來上面盡是明夷，市，困，家人
等易經卦名，但卻又不按尋常卦序排列，顯得有些古
怪；每一個卦像都略微凸起，似乎可以按(press)進去。

旁邊注着一行小字：天地定位，山澤通氣，雷風相薄，
水火不相射。
\n",
                "tieban" : 
"\n九宮之圖，法以靈龜，二四為肩，六八為足，
左三右七，戴九履一，五居中央。

數一至九乃先天之數，循環不息，人不能測，欲
以此為本，求諸九宮圖中，豈不謬哉！須知天行
有常，以定者求其變者，方為正道。
\n"
        ]));


        set("exits", ([
                "out" : __DIR__"xiangzhong",
        ]));        
        
        setup();
//        replace_program(ROOM);
}

void init()
{
        add_action("do_push", "press");
        add_action("do_help", "sos"); 
}

int do_help(string arg)
{
        object me = this_player();
        int n;
        mixed *local;

        local = localtime(time());
        n = (int)query_temp("number");

        tell_object(me, HIB"南宮浪告訴你： "+dirs[n]+"!!!\n"NOR);
        return 1;
}

int do_push(string arg)
{
        object me = this_player();
//        object room = load_object(__DIR__"grave");
        object ob;
        int m, n, i ,j, k;
        string str;

        addn_temp("push_time", 1, me);
        message_vision("$N伸手向石門按去...\n", me);
        if( query_temp("push_time", me) >= 3){
                tell_object(me,HIR"你腳下一虛，心中暗叫“不好！”，只覺一陣天旋地轉......\n"NOR);
                me->unconcious();
                delete_temp("push_time", me);
                me->move(__DIR__"xiangzhong");
                return 1;
        }

        m = random(105);
        n = m%15;
        i=m%3; j=m%5; k=m%7;
        str = "今有物不知其數，三三數之剩"+chinese_number(i)+"，五五數之剩"+chinese_number(j)+"，七七數之剩"+chinese_number(k)+"，問物幾何？\n";

//        if (!arg) return notify_fail("什麼？\n");
         
        if (arg == "謙") {
                write("石門突然“咯咯”輕響了幾聲。\n");
                write("\n甬道頂部忽然飄落一束薄卷軸，\n");
                ob = new(__DIR__"obj/paper3");
                set("long", str, ob);
                set_temp("number", n);
                ob->move(me);
                set_temp("th_tomb_pass1",1);
                me->start_busy(2);
        }

        if ((arg == dirs[query_temp("number")]) && (query_temp("th_tomb_pass1"))) {
                write("石門突然“咯咯”輕響了幾聲。\n");
                set_temp("th_tomb_pass2",1);
        } 

        if (query_temp("th_tomb_pass1") && query_temp("th_tomb_pass2")) {
                write("只聽得“隆隆”幾聲大響，石門緩緩向一側劃開...\n\n\n");
                set("exits/enter", __DIR__"grave");
                remove_call_out("close_door");
                call_out("close_door", 10, me);
                log_file("Taohua",sprintf("%s(%s) entered Taohua Tomb on %s. \n",
                                me->name(), getuid(me)), ctime(time()));
                me->start_busy(2);
        } else return notify_fail("你按下其中一個卦象，但石門卻紋絲不動。\n");

        return 1;
}

void close_door()
{
//      object room = load_object(__DIR__"secret_path1");

        if( !query_temp("th_tomb_pass1") || !query_temp("th_tomb_pass2")) 
                return;

        message("vision", "過了一會兒，石門輕輕地關上了，一切又恢復到從前的樣子。\n", this_object() );
        delete("exits/enter");
//      room->delete("exits/up");
//      tell_room(room, "過了一會兒，暗門輕輕地關上了。\n");
        delete_temp("th_tomb_pass1");
        delete_temp("number");
        delete_temp("th_tomb_pass2");
}