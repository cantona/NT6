inherit ROOM;

void create()
{
        set("short", "煉藥堂");
        set("long", @LONG
這是一間不大的房間，房間中央是一個灶台，灶上支著一個
大沙鍋，咕嘟咕嘟的聲響在門外都能聽見，一個小童子在灶下拉
著風箱，另一個在看著鍋裡不時的放進一些藥材。
LONG
        );
        set("exits", ([ /* sizeof() == 1 */
  "west" : __DIR__"yz_xiaoyuan",
]));

        setup();
        replace_program(ROOM);
}
