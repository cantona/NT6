inherit ROOM;

void create()
{
        set("short", "沉魚閣");
        set("long", @LONG
應入眼簾，首先是一幅佔據了一面牆的春宮圖，無疑為名家所著。畫
法細膩，毫發盡現。金盞玉杯，紅燭粉黛構成了一種奇特的脅調。廳正中
放著幾張玉石圓桌，桌上杯盞參差。此閣無頂。每當深夜，微風襲襲，繁
星點點；一輪明月，懸掛于正央。放眼眺望，洛陽城盡收眼底。蒼穹暗淡，
唯閣燭一盞；萬物盡淡，唯英雄美人。
LONG);
        set("no_clean_up", 0);
        set("exits", ([
                  "west" : __DIR__"jiyuan2",
        ]));

	set("coor/x", -6970);
	set("coor/y", 2130);
	set("coor/z", 10);
	setup();
        replace_program(ROOM);
}