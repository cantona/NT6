// Room: /u/zqb/tiezhang/zoulang-2.c

inherit ROOM;

void create()
{
        set("short", "走廊");
        set("long", @LONG
你走在一條走廊上，北面似乎有翻書的嘩嘩聲。
LONG        );
        set("exits", ([ /* sizeof() == 2 */
  "west" : __DIR__"zoulang-3",
  "east" : __DIR__"wztang",
]));
        set("no_clean_up", 0);

        setup();
        replace_program(ROOM);
}