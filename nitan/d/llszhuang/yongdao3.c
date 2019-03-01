inherit ROOM;
#include <ansi.h>
int do_pick(string arg);
void create()
{
       set("short", "柳綠山莊");
        set("long",
"這是莊院的石階，石階呈現出一種奇異的死灰色。石階旁邊是一座假\n"
"山，假山石縫裡面插著一把鋼拐，直至沒柄。鋼拐旁邊斜倚著一具骷髏，\n"
"骷髏上的白發是銀灰色的。\n"
);
        set("no_magic", "1");

        set("exits", ([ /* sizeof() == 2 */
          "north" : __DIR__"dynamic/jiuqu1",
          "southeast" : __DIR__"yongdao2",
        ]));

        set("item_desc", ([
                "鋼拐": "這是一把精光閃閃的鋼拐，雖已歷經多年風雨，上面卻毫無鏽□□n",
        ]) );

        set("have_weapon",1);
        setup();
}
int init()
{
        add_action("do_pick","pick");
}

int do_pick(string arg)
{
        object me,killer;
        int i;

        me = this_player();

        if( !arg || arg != "鋼拐" )
                return 0;
        if( query("have_weapon") != 1 )
                return notify_fail("鋼拐已經被拔走了。\n");

        i=query("neili", me);
        if( random(i)<2000 )
        {
                i -= 200;
                if( i<1 ) i = 1;
                set("neili", i, me);
                return notify_fail("你使出吃奶的力氣狠命搖晃著鋼拐，可鋼拐紋絲不
動。\n");
        }
        addn("neili", -1000, me);
        message_vision("$N運足內力，把鋼拐從假山石縫中拔了出來。\n可是...\n"+BLU
"忽然一陣陰風吹起...還..我..命..來...\n"NOR,me);
        set("have_weapon",0);
        killer = new(__DIR__"npc/wraith");
        killer->move(this_object());
        killer->set_leader(me);
        killer->kill_ob(me);
        me->fight_ob(killer);
        return 1;
}
