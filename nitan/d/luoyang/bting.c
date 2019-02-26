// Room: /u/a/agah/bting.c

inherit ROOM;

void create()
{
        set("short", "北廳");
        set("long", @LONG
這裏是衙門的北廳，乃是知府的書房。房中有一個亮敞的紅木書桌，
書案上凌亂地放着幾本發黃的古籍，牆上掛着幾副字畫，全部出自名家手
筆，一個小書童正在整理着書房中的書籍。
LONG
        );
        set("no_clean_up", 0);
        set("exits", ([ /* sizeof() == 1 */
  "south" : __DIR__"yamen",
]));

	set("coor/x", -6970);
	set("coor/y", 2210);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}