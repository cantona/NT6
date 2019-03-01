// Room: /u/zqb/tiezhang/sslin-2.c

inherit ROOM;

void create()
{
        set("short", "鬆樹林");
        set("long", @LONG
你走進一片黑壓壓的鬆樹林，這裡的鬆樹枝繁葉茂，樹冠相疊，遮天蔽
日。幾素陽光從樹梢間照射下來，在淡淡的霧氣中，形成一條條白色的光柱，
煞是好看。你走著走著，忽然發現自己已迷失在這片鬆林中，找不到出去的
路了。
LONG        );
        set("exits", ([ /* sizeof() == 1 */
  "north" : __DIR__"sslin-3",
  "south" : __FILE__,
  "west" : __DIR__"sslin-1",
  "east" : __FILE__,
]));
        set("no_clean_up", 0);

        setup();
        replace_program(ROOM);
}