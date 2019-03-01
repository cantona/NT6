// shegu.c 蛇谷
// maco 7/15/2000

#include <ansi.h>
#include "room.h"

inherit ROOM;

string look_mist();

void create()
{
        set("short", "蛇谷");
        set("long", @LONG
蛇谷是歐陽世家中最險惡的密境，棲息了無數毒蛇，因而得名。
此處便是進入歐陽世家蛇谷的要沖，巨大而狹長的山口，便像是張大
了的蛇口。谷前十數丈內的土地寸草不生，
LONG );

        set("exits", ([ 
                "south"     : __DIR__"road2",
                "northdown" : __DIR__"shegu2",
        ]));

        set("item_desc", ([
                "mist" : (: look_mist :),
                "霧"   : (: look_mist :),
                "紅霧" : (: look_mist :),
        ]));

        set("defense", 1);
        set("outdoors","baituo");
        set("shegu", 1);
        set("coor/x", -49970);
        set("coor/y", 20110);
        set("coor/z", 30);
        setup();
}

string long()
{
        string msg;

        msg = query("long");
        
        if( query("defense") )
                msg  += 
"土裡冒出陣陣紅霧(mist)，彌漫整個谷口，氣氛相當詭異。山谷"
"的外圍卻是碧草如茵，偶爾有些膽大的牧民在此放牧。谷底是一條人馬踩出來的"
"小道。";        
                else 
        msg  += 
"山谷的外圍卻是碧草如茵，偶爾有些膽大的牧民在此放牧。谷底"
"是一條人馬踩出來的小道。";

        return sort_string(msg, 64, 4);
}

string look_mist()
{
        string desc;
        if( query("defense") ) 
        {
                desc =  RED"一片血紅色的霧氣，不斷從土裡騰騰冒出，瑰麗之中，又顯得十分詭譎。\n"NOR;
                if( query("family/family_name", this_player()) == "歐陽世家" )
                desc += "歐陽世家莊在地下建有密窖，歐陽鋒將蛇場中的劇毒蛇種養在窖中，\n"
                        "利用群蛇呼出的毒氣做為屏障，以防外敵闖入蛇谷，毀了他捕蛇修煉的重地。\n";
                return desc;
        }
        else return "本來彌漫谷口的紅霧，現在完全消失了。\n";
}

int valid_leave(object me, string dir)
{
        int i, w;

        if (dir == "northdown") 
        {
                if (me->query_skill("poison",1)<100)
                        return notify_fail("蛇谷乃劇毒之地，不懂點用毒解毒之術怎敢進入？\n"); 
                if( !query("baituo/shegu_permit", me) && query("defense") )
                        return notify_fail("你看著彌漫谷前的紅霧，稍微走近，忽覺腥臭撲鼻，感覺竟有些暈眩。\n看來這是極為厲害的毒霧，難以強行通過。\n");

                if( query("family/family_name", me) == "歐陽世家"
                 && !query("baituo/shegu_permit", me) )
                        return notify_fail("你想了一想，覺得未經莊主歐陽鋒許可，還是別擅闖蛇谷得好。\n");
                if( query("baituo/shegu_permit", me) && query("defense") )
                        message_vision("$N無視於毒霧，大步走進了蛇谷。\n", me);
        }
        return ::valid_leave(me,dir);
}

void reset()
{
        ::reset();
        set("no_clean_up", 1);
}