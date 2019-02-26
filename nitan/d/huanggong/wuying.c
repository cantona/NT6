// Room: /d/huanggong/wuying.c

inherit ROOM;

void create()
{
        set("short", "武英殿");
        set("long", @LONG
這是武英殿, 在這陳列的是各式各樣的物飾儀器. 原來這裏是皇帝
齋戒之處. 後來這裏又是內務府屬下的造辦處, 並在此設立修書處, 揀
派翰林儒臣校刊書籍. 此處的新書遂稱"殿版"書.
LONG
        );
        set("exits", ([
                "east"      : __DIR__"guangchang",
                "west"      : __DIR__"xihuamen",
                "south"     : __DIR__"nanxundian",
                "north"     : __DIR__"neiwufu",
        ]));
        set("no_clean_up", 0);
	set("coor/x", -2810);
	set("coor/y", 7721);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}