// Room: /d/lingxiao/yudong.c
// Last Modified by Winder on Jul. 15 2001

#include <ansi.h>
inherit ROOM;
void create()
{
        set("short","玉洞");
        set("long",@LONG 
如果説外面的冰洞象夢幻的世界一樣，那麼，這裏就是真正的天堂。
整個洞內，無論洞壁洞頂，全是墨綠的玉石。玉質温潤細滑，竟是和田
之玉。就算在權貴之家，和田玉也是了不起的財富。一塊手掌般大的和
田玉，就夠一户中等人家過上一輩子。但是，這裏最吸引人的，還是中
間的玉台(table)上天然所生的一塊珠子，它散發出幽幽光澤，照的滿
室皆綠。
LONG);
        set("had_yujing", 1);
        set("exits",([ /* sizeof() == 1 */
                "out" : __DIR__"wave", 
        ])); 
        set("item_desc", ([
                "table" : "這是一整塊玉天然行成的玉台，玉中呈現出奇怪的圖形。
上面天然生出的一塊珠子(zhuzi)。\n",
                "zhuzi": "這是一塊玉珠，它散發出幽幽光澤，照的滿室皆綠。\n",
        ]));
        
        set("coor/x", -31040);
        set("coor/y", -8950);
        set("coor/z", 100);
        set("no_clean_up", 0);
        setup();
}

void init()
{       
        add_action("do_take", "take");
        add_action("do_take", "qu");
        add_action("do_take", "jian");
        add_action("do_take", "pick");
}

int do_take(string arg)
{
        object baoyu, me=this_player();

        if( !arg || arg=="" ) return 0;
        if( arg=="zhuzi" )
        {
                if (query("had_yujing"))
                {
                        
                        message_vision("$N輕輕的從石台上撿起塊玉來。\n", me);
                        baoyu = new(__DIR__"obj/yujing");
                        //baoyu = new("/clone/fam/etc/lv5f");
                        baoyu->move(me);
                        //message("channel:rumor", MAG"【謠言】某人："+me->query("name")+"得了冰魄玉精啦。\n"NOR, users());
                        set("had_yujing", 0);
                        return 1;
                }               
                message_vision("$N伸手去取，才發現冰雕的玉石立刻化成一灘水，冰魄玉精早就被別人取走了...。\n", me);
                return 1;
        }
        return 0;
}
