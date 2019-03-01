// Room: /u/zqb/tiezhang/zoulang-3.c

inherit ROOM;

void create()
{
        set("short", "走廊");
        set("long", @LONG
你走在一條走廊上。北面傳來陣陣飯菜的香味。
LONG        );
        set("exits", ([ /* sizeof() == 2 */
  "north" : __DIR__"chufang",
  "east" : __DIR__"zoulang-2",
]));
        set("no_clean_up", 0);

        setup();
        replace_program(ROOM);
}