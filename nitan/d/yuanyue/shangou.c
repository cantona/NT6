// This program is a part of NITAN MudLIB

#include <ansi.h>
inherit ROOM;

int do_jump(string arg);
void create()
{
        set("short", "山溝"); 
        set("long", @LONG
這裏是圓月山莊後園的一個山溝，旁邊是一片密密的松木林，四
週一片寂靜。
LONG);
        set("outdoors", "wansong");
        set("type","forest");
        set("exits",([
                "east":__DIR__"senling4",
        ]) );
        
        set("coor/x",-630);
        set("coor/y",250);
        set("coor/z",90);
        setup();
}   

void init() 
{ 
        if (NATURE_D->query_month() == 7 &&
            NATURE_D->query_day() == 15 || query("mojiao/715", this_player()))
        {
                add_action("do_jump", "jump");
        }
}

string long() 
{
        string msg; 
       
        msg = query("long"); 
 
        if (NATURE_D->query_month() == 7 &&
            NATURE_D->query_day() == 15)
                msg += HIW "山溝中的洪水滾滾而過，氣勢非凡，你見此情形頓時有想要跳入洪水中(jump hongshui)的衝動。" NOR;
        
        return sort_string(msg, 60, 4); 
}

int do_jump(string arg)
{
        object me = this_player();

        if (! arg || (arg != "hongshui" && arg != "shangou"))
                return notify_fail("你想跳入什麼？\n");

        message_vision(HIW "$N" HIW "縱身跳入山溝中的滾滾洪水之中，頓時沒有了身影。\n" NOR, me);        

        tell_object(me, HIW "山溝中的洪水太急，一股勁浪打來，你頓時暈了過去。\n" NOR);        
        
        me->unconcious(); 
        me->move(__DIR__"hole");
        if( !query("mojiao/715", me) ) set("mojiao/715", me);
        return 1;
}
