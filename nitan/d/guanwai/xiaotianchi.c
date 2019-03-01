// /guanwai/xiaotianchi.c

inherit ROOM;

void create()
{
        set("short", "小天池");
        set("long", @LONG
小天池又稱長白鏡湖，圓圓如鏡。湖水碧藍，林海峭壁倒映其間，風光
幽麗，一層綠裡透紅的細沙，均勻地舖在湖底，恰似展開著的一幅金絲絨毯。
相傳天上仙女每日天池中沐浴，洗畢就到天豁峰的峰顛，坐在兩個峰尖中間
的開闊巖石上，對著小天池打扮梳妝，故名鏡湖。
LONG );
        set("exits", ([
                "eastup"  : __DIR__"pubu",
                "west"    : __DIR__"heifengkou",
        ]));
        set("no_clean_up", 0);
        set("outdoors", "changbai");
        setup();
        replace_program(ROOM);
}