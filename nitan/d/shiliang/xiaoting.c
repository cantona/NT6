// Room: xiaoting.c
// Feb. 6, 1999 by Winder
inherit ROOM;
void create()
{
        set("short", "小廳");
        set("long",@LONG
這是一個小小的客廳，牆上掛著一些字畫，其中最顯眼的是王
羲之的一幅《蘭亭集序》，有個女僕人正在打掃著衛生。
LONG
        );
        set("exits", ([
                "south" : __DIR__"xiaoyuan",
                "up" : __DIR__"xiaolou",
        ]));
        set("objects", ([
                 __DIR__"npc/afeng" : 1,
        ]));
        set("item_desc", ([
                "《蘭亭集序》" : "這大概是王老先生的真跡，筆法遒勁，渾然一派大家風范。\n" ,
        ]));
        set("coor/x", 1620);
        set("coor/y", -1770);
        set("coor/z", 0);
        setup();
}
void init()
{
        add_action("do_enter", "enter");
//        add_action("do_move", "open");
        add_action("do_kneel", "kneel");
}
int do_kneel(string arg)
{
        object me,hole;
        string dir;
        me = this_player();
        if (!arg||arg=="") return 0;
        if( arg=="《蘭亭集序》" ) {
                message_vision("$N虔誠地跪在《蘭亭集序》下，磕起頭來，“咚咚”地板好象是空的。\n", this_player());
        }
        if( sscanf(arg, "《蘭亭集序》 %s", dir)==1 ) 
        {
                if( dir=="9" || dir=="nine")
                {
                        if(!objectp(present("hole", environment(me))))
                        {
message_vision("$N一口氣磕了九個響頭，突然間，地板鬆動了，露出一個大洞。\n",me);
                                hole = new("/d/shiliang/obj/hole");
                                hole->move("/d/shiliang/xiaoting");
                        }
                }   
                else return notify_fail("你胡亂磕了幾個頭，結果啥也沒發生。\n");
        }                
        return 1;
}
int do_enter(string arg)
{
        if( !arg || arg!="floor" ) return 0;
                return notify_fail(" 想穿地板啊？你不會奇門遁甲。\n");
        return 1;
}