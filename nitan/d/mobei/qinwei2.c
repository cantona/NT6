// Room: /d/mobei/qinwei2.c
// Last Modified by winder on May. 25 2001

inherit ROOM;

void create()
{
        set("short", "親衞營");
        set("long", @LONG
親衞營是專為保護鐵木真和其家人所設立的，多是鐵木真的遠親子
弟或武功高強者，地位在一般士兵之上。蒙古人崇尚樸實，所以營帳中
除了些刀槍外就沒有些什麼奢侈東西。
LONG
        );
        set("objects", ([ /* sizeof() == 1 */
                __DIR__"npc/qinwei2" : 2,
                __DIR__"npc/chilaowen" : 1,
        ]));
        set("exits", ([ /* sizeof() == 1 */
                "east" : __DIR__"road3",
        ]));
        set("no_clean_up", 0);

        set("coor/x", -230);
        set("coor/y", 5240);
        set("coor/z", 0);
        setup();
        replace_program(ROOM);
}