// Room: /u/zqb/tiezhang/road-1.c

inherit ROOM;

void create()
{
        set("short", "黃土路");
        set("long", @LONG
你走在一條塵土飛揚的黃土路上，兩旁是陰森森的樹林。這裡是川湘的
交界處，據說經常有土匪出沒，不可久留。
LONG        );
        set("exits", ([ /* sizeof() == 2 */
  "southwest" : __DIR__"road-2",
  "northeast" : __DIR__"lx",
]));
        set("no_clean_up", 0);
        set("outdoors", "wudang");

        setup();
        replace_program(ROOM);
}