// Room: /d/mobei/qinwei.c
// Last Modified by winder on May. 25 2001

inherit ROOM;

void create()
{
        set("short", "親衛營");
        set("long", @LONG
親衛營是專為保護鐵木真和其家人所設立的，多是鐵木真的遠親子
弟或武功高強者，地位在一般士兵之上。蒙古人崇尚樸實，所以營帳中
除了些刀槍外就沒有些什麼奢侈東西。
LONG);
        set("objects", ([ /* sizeof() == 1 */
                __DIR__"npc/qinwei2" : 2,
        ]));
        set("exits", ([ /* sizeof() == 1 */
                "west" : __DIR__"road2",
        ]));
        set("coor/x", -190);
        set("coor/y", 5240);
        set("coor/z", 0);
        setup();
        replace_program(ROOM);
}