#include <room.h>
#include <ansi.h>
inherit ROOM;

int do_look(string arg);

void create()
{
    set("short", HIY"演武大門"NOR);
        set("long", @LONG
這是一個金色的門廊，往北是一個寬闊的走廊，盡頭就是比武大
廳。泥潭的頂級高手通過擂台比武一爭高低，比武大廳是泥潭所有武
者心中的聖地。如果能夠躋身十大高手金榜，更是無上榮譽，風光至
極。
LONG );

    set("no_fight",1);
    set("no_beg",1);
    set("no_steal",1);

    set("exits", ([
        "north" : "/d/city/biwu_road",
        "south" : "/d/city/wudao1",
    ]));

    set("no_clean_up", 0);
	set("coor/x", -60);
	set("coor/y", 0);
	set("coor/z", 0);
	setup();
}

int valid_leave(object me, string dir)
{
	int i;
        mapping conditions;
        object *inv;
 
        if (dir != "north") return 1;

        if (mapp(conditions = me->query_condition()))
               return notify_fail("對不起，你的身體狀況不好，不能進入！\n");

        if( query("eff_qi", me)<query("max_qi", me) )
               return notify_fail("對不起，你的氣血受傷了，不能進入！\n");

        if( query("eff_jing", me)<query("max_jing", me) )
               return notify_fail("對不起，你的精氣受傷了，不能進入！\n");

        inv = deep_inventory(me);
        for (i = 0; i < sizeof(inv); i++)
        {
                if (! userp(inv[i])) continue;
                tell_object(me, "你背的是誰？還不快快放下！\n");
                return 0;
        }

        inv = 0;
        return 1;
}