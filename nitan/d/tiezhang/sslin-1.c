// Room: /u/zqb/tiezhang/sslin-1.c

inherit ROOM;

void create()
{
        set("short", "松樹林");
        set("long", @LONG
你走進一片黑壓壓的松樹林，這裏的松樹枝繁葉茂，樹冠相疊，遮天蔽
日。幾素陽光從樹梢間照射下來，在淡淡的霧氣中，形成一條條白色的光柱，
煞是好看。你走着走着，忽然發現自己已迷失在這片松林中，找不到出去的
路了。
LONG        );
        set("exits", ([ /* sizeof() == 1 */
  "east" : __DIR__"sslin-2",
  "west" : __FILE__,
  "south" : __DIR__ "shanlu-7",
  "north" : __FILE__,
]));
        set("no_clean_up", 0);

        setup();
        replace_program(ROOM);
}