inherit ROOM;
#include <ansi.h> 

void create()
{
        set("short", "前院");
        set("long", @LONG 
這裏是凌霄城的前院，凌霄弟子大都居住於此後。這裏種
了一棵三人合圍粗的墨梅，花瓣漆黑，氣味芬芳。深邃的大院
裏，高山陽光透過墨梅的花瓣射下，在雪地上映出一塊塊亮斑。
一隻雪鶴在樹下翩翩起舞，黑白相映，互有情趣。 
LONG);
        set("outdoors", "lingxiao");
        set("exits", ([
                    "south"  : __DIR__"dadian",
                    "west"  : __DIR__"huajing", 
                    "north"  : __DIR__"zhongting",
        ]));
        set("objects", ([
                "/clone/quarry/he2" : 1,
                __DIR__"obj/ban" : 1,
        ]));
        set("no_clean_up", 0);
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