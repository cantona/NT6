// Room: /d/huanggong/huangjimen.c

inherit ROOM;

void create()
{
        set("short", "皇極門");
        set("long", @LONG
皇極殿庭院的大門. 由此往北, 是皇帝休憩和太上皇養老飴孫的地
方, 俗稱 "外東路" . 門前就是享譽海內外的九龍壁了.
LONG
        );
        set("outdoors", "huanggong");
        set("exits", ([
                "north"     : __DIR__"ningshoumen",
                "south"     : __DIR__"jianting",
                "west"      : __DIR__"yuqinggong",
        ]));
        set("no_clean_up", 0);
	set("coor/x", -2790);
	set("coor/y", 7741);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}