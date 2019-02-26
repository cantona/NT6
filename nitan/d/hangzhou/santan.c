// santan.c
// Date: Nov.1997 by Venus
#include <room.h>;
#include <ansi.h>;
inherit ROOM;
void create()
{
        set("short", "三潭印月");
        set("long", @LONG
這裏是西湖小瀛洲的“我心相應”亭，小瀛洲人稱“湖中有島，島
中有湖”。亭前有聯曰：“客中客入畫中畫  樓外樓看山外山”。島後
三塔為東坡狩杭時所建。“塔影亭亭引碧流”、“玲瓏塔底月輪懸”，
遂使“三潭印月”位列西湖十景。
    元代三塔被毀，大明萬曆重建時已不在原處，致成今時“天上月一
輪，湖中影成三”之景。亭邊泊着小舟(zhou)是送遊客去蘇堤。
LONG);
        set("outdoors", "xihu");
        set("no_clean_up", 0);
        set("coor/x", 4130);
        set("coor/y", -1440);
        set("coor/z", 0);
        setup();
}

void init()
{
        add_action("do_enter", "enter");
}
int do_enter ( string arg )
{
        object ob ;
        string dir;
        if( !arg || arg !="zhou" ) 
        {
                tell_object(this_player() , "你要 enter 哪兒？\n" ) ;
                return 1 ;
        }
        ob = this_player () ;
        message_vision("梢公一見有人上船，輕搖木槳，小舟西行。\n", ob);
        ob ->move(__DIR__"xihu") ;
        tell_object(ob, HIG "你在湖面穿行，輕風徐來，滿面生暖。\n" NOR ) ;
        call_out("tostyy", 10 , ob );
        return 1 ;
}
void tostyy(object ob )
{
        tell_object(ob , "小舟輕輕靠上蘇堤。你走下船來。\n" ) ;
        ob->move (__DIR__"suti6") ;
}