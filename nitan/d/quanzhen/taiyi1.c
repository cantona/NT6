// taiyi1.c
// Java Oct.10 1998
#include <ansi.h>;
inherit ROOM;

void create()
{
        set("short", "太乙池");
        set("long", @LONG
你眼前出現一個山間湖泊，這就是著名的太乙池 (chi)，傳為唐
天寶年間地震造成，四周高峯環列，池面碧波盪漾，山光水影，風景
十分優美。
LONG
        );
        set("outdoors", "zhongnan");
        set("item_desc", ([
                "chi" : 
HIG"\n\n這是一個很大的山間湖，碧波盪漾，湖水清澈見底，讓人忍不住想跳(jump)下去
暢遊一番。\n\n"NOR
        ]));
        set("exits", ([
                "southup"   : __DIR__"shandao3",
        ]));
          set("objects", ([
                  "/clone/npc/walker" : 1,
          ]));

        set("coor/x", -3190);
        set("coor/y", 180);
        set("coor/z", 80);
        setup();
}
void init()
{
        add_action("do_jump","jump");
}
int do_jump(string arg)
{
        object me = this_player();
        object *inv; 
        int c_exp,i;
        c_exp=query("combat_exp", me);
        if( !arg || arg != "chi")
        {
                write("你往哪裏跳呀? \n");
                return 1;
        }
        inv = all_inventory(me);
        for (i = 0; i < sizeof(inv); i++)
        {
          if (inv[i]->is_character())
             {
              return notify_fail("你要跳？自己一個人跳吧，帶着別人幹嗎？\n");
             }
        }  
        message_vision("$N往太乙池中跳去。\n", me);
        me->move("/d/quanzhen/taiyi2");
        message_vision("$N跳進了太乙池中來。\n", me);
        return 1;
}