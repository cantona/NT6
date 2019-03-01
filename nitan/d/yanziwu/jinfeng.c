// Room: /d/yanziwu/jinfeng.c
// Date: Jan.28 2000 by Winder
#include <ansi.h>;
inherit ROOM;

void create()
{
        set("short", "金風莊");
        set("long", @LONG
這裡是金風莊。莊上莊主就是包三先生了。不過太莊主卻另有其人，
想知道是誰，就請進去看看。
    莊外湖面正系著一尾小舟(zhou)。
LONG );
        set("outdoors", "yanziwu");
        set("exits", ([
                "west"  : __DIR__"guifang",
        ]));
        //set("objects", ([
        //        __DIR__"npc/bao" : 1,
        //]));
        set("item_desc", ([
                "zhou" : "這是金風莊和外界聯系的小舟。舟上一個綠衫少女。島上的客人只要\n登舟(enter)就可以離開了。\n",
        ]));
        set("coor/x", 750);
        set("coor/y", -1550);
        set("coor/z", 0);
        setup();
}
void init()
{
        add_action("do_enter", "enter");
}
int do_enter(string arg)
{
        object ob ;
        string dir;
        if( !arg || arg !="zhou" )
        {
                tell_object(this_player() , "你要投水？\n");
                 return 1 ;
        }
        ob = this_player();
message_vision("船上一個秀美溫柔的江南少女看到$N登舟，竹篙輕點，舟已
離岸，金風莊漸漸在視野裡遠去。\n", ob);
        ob ->move(__DIR__"taihu") ;
        tell_object(ob, HIG "你在湖上飄流，四周看不盡的江南美景。\n" NOR ) ;
        call_out("home", 10 , ob );
        return 1 ;
}
void home( object ob )
{
        tell_object(ob , "小舟終于戀戀不舍地靠岸了。你走下小舟來。少女揮手依依道別。\n" ) ;
        ob->move (__DIR__"muti") ;
}