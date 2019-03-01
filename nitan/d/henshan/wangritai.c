inherit ROOM;

void create()
{
        set("short", "望日台");
        set("long", @LONG
望日台緊鄰祝融殿。雞鳴夜起，登台東望，遙見海門，雲水皆赤，
倏忽異彩，日輪盪漾，若沉若浮，稍之奮湧而起，光耀奪目。
LONG );
        set("exits", ([
                "southdown"  : __DIR__"shiziyan",
                "northup"    : __DIR__"zhurongdian",
        ]));

        set("objects", ([
                __DIR__"npc/youke"    : 2,
        ]));    

        set("outdoors", "henshan");

        set("no_clean_up", 0);

	set("coor/x", -6930);
	set("coor/y", -5500);
	set("coor/z", 30);
	setup();
        replace_program(ROOM);
}