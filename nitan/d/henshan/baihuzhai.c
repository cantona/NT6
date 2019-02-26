#include <ansi.h>
inherit ROOM;

string show_hua();

void create()
{
        set("short", "百狐齋");
        set("long", @LONG
這裏就是杜鳳鄂的百狐齋，其實一看就知道這不過是一間破舊的
草堂， 只見堂內陳設簡陋，牆上卻掛滿了畫(hua)，這些都是杜鳳鄂
自己畫的他平時就靠賣這些畫為生。
LONG );
        set("objects", ([
                __DIR__"npc/dufeng" : 1,
        ]));

        set("exits", ([
                "north"  : __DIR__"xiaoxiang2",
        ]));

        set("no_fight", 1);

        set("item_desc", ([
                "hua" : (: show_hua :),
        ]));

	set("coor/x", -6880);
	set("coor/y", -5730);
	set("coor/z", 0);
	setup();

}

string show_hua()
{
        return HIW "\n只見每副畫所畫的均是狐，有白狐、赤狐、黑狐、藍狐、紫狐\n"
               "……或靜、或嬉、或怒、或媚，或狡黠、或機靈、或嬌憨，千\n"
               "姿百態，形神兼具。\n\n" NOR;
}