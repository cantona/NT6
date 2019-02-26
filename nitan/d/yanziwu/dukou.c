// Room: /d/yanziwu/dukou.c
// Date: Jan.28 2000 by Winder
#include <ansi.h>;
inherit ROOM;

void create()
{
        set("short", "茶花渡");
        set("long", @LONG
這裏是蔓陀山莊的茶花渡。山莊主王夫人平生摯愛茶花，可是卻不
識貨，雖然莊裏茶花遍野，甚至不惜渡名茶花。不承望滿莊茶花仍是株
株懷才不遇模樣，沒一枝長得精神點。
    由此可乘船離開蔓陀山莊。湖面正繫着一尾小舟(zhou)。
LONG );
        set("outdoors", "mantuo");
        set("exits", ([
                "north"  : __DIR__"chalin6",
                "south"  : __DIR__"chalin7",
                "east"   : __DIR__"path1",
        ]));
        set("objects", ([
                __DIR__"npc/xiaocui" : 1,
        ]));
        set("item_desc", ([
                "zhou" : "這是蔓陀山莊和湖外聯繫的小舟。舟上一個綠衫少女。島上的客人只要\n登舟(enter)就可以出湖了。\n",
        ]));
        set("coor/x", 1200);
        set("coor/y", -1300);
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
message_vision("船上一個秀美温柔的江南少女看到$N登舟，竹篙輕點，舟已
離岸，蔓陀山莊漸漸在視野裏遠去。\n", ob);
        ob ->move(__DIR__"taihu") ;
        tell_object(ob, HIG "你在湖上飄流，四周看不盡的江南美景。\n" NOR ) ;
        call_out("home", 10 , ob );
        return 1 ;
}
void home( object ob )
{
        tell_object(ob , "小舟終於戀戀不捨地靠岸了。你走下小舟來。少女揮手依依道別。\n" ) ;
        ob->move (__DIR__"hupan") ;
}