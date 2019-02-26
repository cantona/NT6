inherit ROOM;

void create()
{
        set("short", "松樹林");
        set("long", @LONG
你走進一片黑壓壓的松樹林，這裏的松樹枝繁葉茂，樹冠
相疊，遮天蔽日。幾素陽光從樹梢間照射下來，在淡淡的霧氣
中，形成一條條白色的光柱，煞是好看。你走着走着，忽然發
現自己已迷失在這片松林中，找不到出去的路了。
LONG);
        set("exits", ([
                  "west"  : __DIR__"sslin-4",
                  "east"  : __FILE__,
                  "south" : __DIR__ "sslin-2",
                  "north" : __FILE__,
        ]));
        set("no_clean_up", 0);
        setup();
        replace_program(ROOM);
}