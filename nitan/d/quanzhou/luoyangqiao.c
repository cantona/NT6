// Room: /d/quanzhou/luoyangqiao.c
// Last Modified by winder on May. 29 2001

inherit ROOM;

void create()
{
        set("short", "洛陽橋");
        set("long", @LONG
這是洛陽江上的一座譽滿天下的粱式石橋。橋長身寬，具橋墩四十
六座。橋上兩旁翼以扶欄，欄桿石掛上頭，雕鏤精致雄俊的石獅；更兼
七亭九塔，點綴其間，武士石像，分立兩端。橋之首尾，沿路植鬆七百
株。鬆翠橋白，水碧山青，勝狀令人驚嘆。相傳它是泉州知府蔡襄命一
吏名夏得海冒死下海送信，得海神相助而建。它是粵閩北上的陸路交通
要道，大部分南來北往的貨物，都由此經過。
LONG );
        set("outdoors", "quanzhou");
        set("no_clean_up", 0);
        set("exits", ([
                "west" : __DIR__"lingshan",
                "east" : __DIR__"tudimiao",
        ]));
	set("coor/x", -860);
	set("coor/y", -7720);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}