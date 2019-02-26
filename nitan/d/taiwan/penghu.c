// Room: /d/taiwan/penghu.c
// Last Modifyed by Ahda on Jan. 4 2002

#include <ansi.h>;
inherit ROOM;

void create()
{
        set("short", "澎湖島");
        set("long", @LONG
澎湖為台灣屬島，海峽中砥，台島屏障。馬公港內多為本地漁民，
早晚勞作，與世無爭。
    港內有舟(zhou)船(chuan) 往返大陸台島，衝波激浪中，自有漁家
滋味。
LONG );
        set("item_desc", ([
                "chuan" : "一條大海船。出遠海沒這樣的船可不行。\n",
                "zhou"  : "一條水軍戰舟，前往台灣，還得靠它。\n",
        ]));
        set("objects", ([
                __DIR__"npc/lanli": 1,
                __DIR__"npc/liu": 1,
                __DIR__"npc/bing": 4,
        ]));
        set("outdoors", "taiwan");
        set("coor/x", 2300);
        set("coor/y", -6800);
        set("coor/z", 0);
        setup();
}

void init()
{
        add_action("do_enter", "enter");
}
int do_enter ( string arg )
{
        object ob = this_player () ;
        string dir;
        if( !arg || (arg !="chuan" && arg !="zhou"))
        {
                tell_object(this_player() , "你要 enter 哪兒？\n" ) ;
                return 1 ;
        }
        if (arg == "chuan")
        {
                message_vision("船伕一見有人上船，忙叫了一聲：開船嘍！\n", ob);
                message_vision("船伕升起帆，船就向西方順風航行。\n", ob);
                call_out("tdalu", 10 , ob );
        }
        else
        {
                message_vision("水兵一見有人上船，忙叫了一聲：開船嘍！\n", ob);
                message_vision("水兵升起帆，船就向東方逆風航行。\n", ob);
                call_out("ttaiwan", 10 , ob );
        }
        ob->move(__DIR__"dahai") ;
        tell_object(ob, BLU "你在海上航行了很久很久.......\n" NOR ) ;
        return 1 ;
}
void tdalu( object ob )
{
        tell_object(ob , "大船終於抵達了福建的一個繁華海港。你走下船來。\n" ) ;
        ob->move("/d/quanzhou/houzhu") ;
}
void ttaiwan( object ob )
{
        tell_object(ob , "戰舟終於抵達了台灣的一個港口城市。你走下船來。\n" ) ;
        ob->move(__DIR__"lugang") ;
}
