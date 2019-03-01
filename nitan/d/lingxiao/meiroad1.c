inherit ROOM;
#include <ansi.h> 

void create()
{
        set("short", "梅道");
        set("long", @LONG
這是一條充滿了梅花清香的大道。往北就是凌霄城的大殿
凌霄殿了。聞著滿天的梅香，本以為這裡種滿了梅樹，走近卻
才發現，這裡只有兩棵合圍粗的白梅，開著漫天的冰凌。其實
是梅還是雪，已分不清了。看到這種情況那句「梅須遜雪三分
白，雪卻輸梅一段香」的話，是誰也不會信了。這梅這雪，誰
白誰香，分得出來嗎？
LONG);
        set("outdoors", "lingxiao");
        set("exits", ([
                "south"  : __DIR__"iceroad3",
                "north"  : __DIR__"dadian",
                "west"  : __DIR__"meiroad2",
                "east"  : __DIR__"meiroad3",
        ]));
        set("objects", ([
                __DIR__"npc/dizi" : 2,
                __DIR__"obj/ban" : 1,
        ]));
        setup();
}

void init()
{
        add_action("do_pick","pick");
}

int do_pick(string arg)
{
        object me = this_player();
        object ob;

        if (arg == "mei hua" || arg == "meihua")
        {
                if (query("count") < -5)
                        return notify_fail("這裡的梅花已經被摘光了。\n");

                ob = new(__DIR__"obj/mei");
                ob->move(me, 1);
                addn("count", -1);

                message_vision("$N從路旁的樹上摘了一朵" +
                               query("name", ob)+"。\n",me);
                return 1;
        } else
                return notify_fail("你要摘什麼？\n");
}