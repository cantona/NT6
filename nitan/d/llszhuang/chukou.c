// chukou.c

#include <ansi.h>

inherit ROOM;
void create()
{
        set("short", "墓林");
  set("long",
"這裡是喪生在山莊裡的江湖俠客的墓林,一塊塊墓碑(mubei)立在路邊\n"
".\n似乎是在告訴來這裡的人RED~~~千萬要小心啊!~~~NOR\n"
);
        set("item_desc", ([
            "mubei": HIG "\n上面寫著--趕快走吧,這裡不是久留之地啊!(leave here)\n" NOR,
    ]));
        set("no_fight",1);
        set("no_die",1);
        setup();
}

int init()
{
        add_action("do_leave","leave");
}
int do_leave(string arg)
{
        object me;
        object *inv;
        int i;
        me = this_player();
        inv = all_inventory(me);
    if ( !arg || arg !="here" )
        return notify_fail("你真的要走?是leave here \n");

        for( i=0;i<sizeof(inv);i++)
{
                if( inv[i]->is_character() )
                   return notify_fail("你不能背著人進去!\n");
}
       write(YEL"你終于離開了這鬼地方!\n"NOR);
        me->move("/d/city/wumiao");
        return 1;
}
