// Room: /u/zqb/tiezhang/zoulang-1.c

inherit ROOM;

void create()
{
        set("short", "走廊");
        set("long", @LONG
你走在一條走廊上。北面的屋內傳來陣陣金屬的聲音。
LONG        );
        set("exits", ([ /* sizeof() == 3 */
  "north" : __DIR__"bqshi",
  "west" : __DIR__"wztang",
  "east" : __DIR__"zoulang-4",
]));
        set("no_clean_up", 0);

        setup();
        replace_program(ROOM);
}