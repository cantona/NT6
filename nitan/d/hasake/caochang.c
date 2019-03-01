// caochang.c 草場
#include <ansi.h>
inherit ROOM;
void create()
{
        set("short", "草場");
        set("long", @LONG
這一族哈薩克人大概已經習慣了定居生活，于是做了個大草場。春夏
把遠處肥嫩的水草割下來堆在這裡，以備秋冬季節畜生的食料。這裡堆滿
了一堆堆帳篷大小的草堆和幹草(gancao)，看起來不下千堆。
LONG);
        set("exits", ([
            "northdown" : __DIR__"pmchang",
            "westdown" : __DIR__"shuijing",            
            "east" : __DIR__"caoyuan1",
        ]));
        set("objects", ([
                    __DIR__"npc/hasake" : 1
        ]));
        set("item_desc", ([
                "gancao" : "  這是堆積在草場理的草堆，地上還零零散散地放了
好多已經曬幹的水草。你可以幫助牧民們把幹草堆(dui)成堆。\n",
        ])); 
        set("outdoors", "hasake");
        setup();
}

void init()
{
        add_action("do_dui", "dui");
}

int do_dui(string arg)
{      
        object me, weapon;
        int costj, costq;
        string skill;
        me = this_player();
        weapon=query_temp("weapon", me);
        if(!living(me)) return notify_fail("你發瘋了? \n");
        if(!weapon) return notify_fail("你用手來堆？有性格！\n");
        if(!arg || arg != "gancao"){    
              message_vision("$N拿起$n在地上磨了磨。\n",me, weapon);
              return 1;
              }        
        costj=1500/query("con", me);
        costj = random(costj);
        costq=2000/query("str", me);
        costq = random(costq);

        if( query("jing", me)<costj || query("qi", me)<costq){
               message_vision(HIR "\n 啊！。。。\n由于$N用力過猛，一大堆幹草倒下來壓在了$N身上！\n"NOR,me);
               me->unconcious();
               return 1;
               }        
        addn("jing", -costj, me);
        addn("qi", -costq, me);
        message_vision("$N用$n拉起一把幹草堆在草堆上。\n", me, weapon);
        skill=query("skill_type", weapon);
        if(me->query_skill(skill, 1) < 120){
                write(HIY "你使勁地叉著幹草，只覺得手中這"+weapon->name()+HIY"是越來越好用。\n"NOR);
                me->improve_skill(skill, (int)(me->query_int()/3));
                }
        else write("你使勁地叉著幹草，但卻發現沒有什麼好玩的。\n");
        return 1;
}