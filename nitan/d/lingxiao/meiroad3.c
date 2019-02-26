inherit ROOM;
#include <ansi.h> 

void create()
{
        set("short","梅道");
        set("long",@LONG
這裏種滿了綠梅。站在這裏，似乎看到了在凌霄城永遠不
可能看到的春天一樣。一陣微風吹來，在綠梅的海洋中蕩起陣
陣漣漪，同時將那股浸人心脾的素香，送到每個人的心中。東
邊就是凌霄城的觀景勝地戲梅亭了。
LONG);
        set("outdoors", "lingxiao");
        set("exits", ([
                    "west"  : __DIR__"meiroad1",
                    "east"  : __DIR__"ting",
        ]));
        set("objects", ([ 
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
                        return notify_fail("這裏的梅花已經被摘光了。\n");

                ob = new(__DIR__"obj/mei");
                ob->move(me, 1);
                addn("count", -1);

                message_vision("$N從路旁的樹上摘了一朵" +
                               query("name", ob)+"。\n",me);
                return 1;
        } else
                return notify_fail("你要摘什麼？\n");
}