#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", HIB "陰陽塔" NOR);
        set("long", HIB @LONG
這是地獄中最高的一座塔，高約三百餘尺，共有十八級。這裏就是
塔頂，塔頂有個供奉台(stone)，傳説有神獸朱雀路過。
LONG NOR
        );

        set("exits", ([
                "down" : __DIR__"yinyangta17",
        ]));

        set("item_desc", ([
                "stone" : HIW "\n上面好像可以放(put)物品。\n" NOR,
        ]));
                
        set("objects",([
                // __DIR__"npc/zhuque" : 1,
        ]));
        set("zhuque", 1);
        
        set("no_magic", 1);
        setup();
}

void init()
{
        object me;
        me = this_player();

        add_action("do_fang", "put");
        add_action("do_fang", "fang");
}

int do_fang(string arg)
{
        object me = this_player();
        object ob;
        object ob1;


        if (me->is_busy())
                return notify_fail("你現在正忙着呢。\n");
                
        if (objectp(present("zhu que", environment(me))))
                return notify_fail("朱雀已經現身了，還尋什麼呀，趕快戰鬥吧！\n");

        if (query("zhuque") < 1)
                return notify_fail("朱雀已經被宰了，你再怎麼尋也是尋不到的！\n");

        if (arg != "qise yinluo")
                return notify_fail("你必須放上至寶七色瓔珞，才能招引神獸朱雀！\n");
                                
        if (! objectp(ob = present("qise yinluo", me)))
                return notify_fail("你身上沒有至寶七色瓔珞！\n");               
        
        destruct(ob);
        message_vision(HIC "\n$N" HIC "你小心翼翼的將至寶七色瓔珞放到供奉台，開始目不轉睛的尋找朱雀。\n" NOR, me); 
        
        ob1 = new("/d/death/npc/zhuque");
        ob1->move(environment(me));
        message_vision(HIC "\n神獸朱雀受到至寶七色瓔珞的招引，突然出現在供奉台，你頓時大喜！\n" NOR, me);         
        
        return 1;
}
 