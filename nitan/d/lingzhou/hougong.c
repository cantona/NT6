// Room: /d/lingzhou/hougong.c

inherit ROOM;

void create()
{
        set("short", "後宮");
        set("long", @LONG
這裏是宮廷的後宮，富麗堂皇，周圍懸着粉紅色的綢紗。一走進來
你的鼻端就飄來一縷似蘭似麝的幽香，不由你覺得有點心猿意馬起來。
西邊是宮女值夜和休息的偏殿。通過偏殿出去就是御花園。
LONG
        );
        set("exits", ([ /* sizeof() == 1 */
                "west" : __DIR__"piandian",
        ]));
        set("objects", ([
                CLASS_D("lingjiu") + "/li" : 1,
        ]));
        set("no_clean_up", 0);

        set("coor/x", -6265);
        set("coor/y", 2995);
        set("coor/z", 0);
        setup();
        replace_program(ROOM);
}