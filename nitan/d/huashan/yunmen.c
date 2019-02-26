// yunmen.c

inherit ROOM;

void create()
{
        set("short", "雲門");
        set("long", @LONG
過莎蘿坪，是華山十八盤。十八盤的盡處就是『雲門』了。這裏
刻着『仙境』、『天下第一名山』等石刻。雲門之內的小盆地就是青
柯坪。
LONG );
        set("exits", ([ /* sizeof() == 2 */
            "northdown" : __DIR__"shaluo",
            "southup" : __DIR__"qingke",
        ]));

        set("no_clean_up", 0);
        set("outdoors", "huashan" );

        setup();
        replace_program(ROOM);
}
 