// xiaocun.c 小村莊
// Winder Oct.10 1998

inherit ROOM;

void create()
{
        set("short", "小村莊");
        set("long", @LONG
這是一片小村莊，隱藏在一個小山坳裡。這裡的居民們都很少到
城裡去，雖然離武功鎮不過是五、六裡的山路，他們寧願秉承著男耕
女紡織、日出而作日落而歇的老傳統。日子雖然清貧，卻還算逍遙。
LONG
        );
        set("outdoors", "hanzhong");
        set("exits", ([
                "northwest" : __DIR__"guchang",
                "southdown" : __DIR__"shanlu",
        ]));
        set("no_clean_up", 0);
        set("coor/x", -12260);
	set("coor/y", 830);
	set("coor/z", 10);
	setup();
        replace_program(ROOM);
}