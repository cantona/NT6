// neitang.c
#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", "偏房"); 
        set("long", @LONG
這是一間沒有任何東西的房子，四壁空盪盪的，好象是一間剛修
好的，還沒有來得及進行裝飾的房間，正中的牆上畫著一幅壁畫，相
當的醒目，畫著九天十萬神魔歃血為盟，十萬滴魔血化做了一只鮮紅
的鸚鵡，鸚鵡的眼睛竟然是用非常罕見的朱雀石做成的。
LONG );
        set("exits", ([ /* sizeof() == 1 */
            "east" : __DIR__"senlin1",
        ]));

        set("no_clean_up", 0);
        set("item_desc", ([
            "eye": "一塊邪惡的朱雀石，發出耀眼的紅光。\n"
        ]) ); 
        setup();
}
void init()
{
        add_action("do_push", "push");
}
int do_push(string arg)
{
        string dir;
        object me=this_player();

        if( !arg || arg=="" ) {write("你想推什麼？\n");return 1;}

        if( arg=="eye" ) {
                write("你使勁推了一下鸚鵡的眼睛，牆壁悄然旋開。\n");
                if((int)me->query_skill("force",1)>=100)
                {write("順著牆壁旋開的夾縫，你進到裡面的密室。\n");
                me->move(__DIR__"mishi");

                 return 1;}
                write("你試著推了一下鸚鵡的眼睛，但什麼都沒有發生。\n");

                addn("jing", -10, me);
                addn("qi", -10, me);


                return 1;

                 }
}
