// Room: /d/lingzhou/yushufang.c

inherit ROOM;

void create()
{
        set("short", "御書房");
        set("long", @LONG
這裡是皇上的御書房，古色古香，居中一張特別大的書桌，東牆是
排椅子，南窗前是一排博物架，擺了不少珍稀古玩，北牆掛幅著『猛虎
下山』圖。皇上平時就在這裡批閱群臣的奏章和接見進諫的臣子。西夏
雖然是偏域番國，但皇上卻是雄才武略頗有大志，時用漢人高賢為官。
LONG
        );
        set("exits", ([ /* sizeof() == 2 */
                "north" : __DIR__"piandian2",
                "east" : __DIR__"xidian",
        ]));
        set("no_clean_up", 0);
        set("coor/x", -6285);
        set("coor/y", 2975);
        set("coor/z", 0);
        setup();
        replace_program(ROOM);
}