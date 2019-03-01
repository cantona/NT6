inherit ROOM;
#include <ansi.h>

void create()
{
        set("short", "高昌迷宮");
        set("long", @LONG
這是條黑沈沈的長甬道，甬道前出現了三條岔道。迷宮之
內並無足跡指引，你不知道要往哪條路走。俯身細看，見左首
右首和前方三條路上都有淡淡的足跡。你似乎迷失了方向，象
沒頭蒼蠅般到處亂闖。
LONG);
        set("exits", ([
                "west" : __DIR__"shulin7",
                "east" : __DIR__"shulin14",
                "south" : __DIR__"shulin" + (random(10) + 2),
                "north" : __DIR__"shulin" + (random(10) + 2),
        ]));

        set("outdoors", "gaochang");
        setup();
  //      replace_program(ROOM);
}
void init()
{
        object me = this_player();

        if (userp(me) && random(2) == 0)
                                {
                message_vision(HIR "\n$N"HIR"一不小心觸動了機關。\n\n"+
                                                                                                "$N"HIR"只聽得頭上一陣巨響，一塊巨石當頭落下。\n\n\n"+
                                                                                                "$N"HIR"一聲慘叫，痛得幾乎失去了知覺......\n\n" NOR, me);
                me->receive_damage("jing",240,"被巨石砸死了");
                me->receive_damage("qi",480,"被巨石砸死了");
                if( query("qi", me)<0 && query("jing", me)<0 )
                                                {
            set_temp("die_reason", "被巨石砸死了", me);
                                                me->die();
                                                } 
                                        else if( query("qi", me)<0 || query("jing", me)<0 )
                                                {
                                                        me->unconcious();
                                                }
                                }
}