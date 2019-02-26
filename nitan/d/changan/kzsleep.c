//Room: kzsleep.c

#include <ansi.h>

inherit ROOM;

void create()
{
        set("short", "客店睡房");
        set("long", @LONG
客棧的一間睡房，房間裏打掃得乾乾淨淨，不時的可以聽到從隔
壁客房裏傳出呼呼的打鼾聲，牆角有一張榻（ｂｅｄ），是供客人們
休息睡覺用的。
LONG );
        set("item_desc", ([ /* sizeof() == 1 */
                "bed" : "一張白色的軟榻，看上去極為精緻(bed)。",
        ]));
        set("exits", ([
                "down" : "/d/changan/kezhan",
        ]));

        set("no_fight", 1);
        set("coor/x", -10750);
	set("coor/y", 1950);
	set("coor/z", 10);
	setup();
}
void init()
{
        add_action("do_bed", "bed");
}
int do_bed()
{       object me;
        me=this_player();
        message_vision(HIY "$N掀開紗帳，準備上牀了。\n\n" NOR, me);
        me->move("/d/changan/bed");
        message_vision(HIY "\n沙帳輕輕一動，$N鑽了進來。\n" NOR, me);
        return 1;
}

int valid_leave(object me, string dir)
{
        delete_temp("rent_paid", me);
        return ::valid_leave(me, dir);
}