inherit ROOM;

void create()
{
        set("short", "放生池");
        set("long", @LONG
從三尺台階走下就是大街了。台階旁挖了一個小池子，邊上用白
石圍起了欄杆。北邊的池壁上『放生池』幾個字塗成了紅色。由於池
的一邊靠近街道，方便別人作出善舉，但整天見人把魚放下，卻是去
總看不見蹤影，多半是被附近的潑皮無賴晚上摸來作宵夜了。
LONG );
        set("no_clean_up", 0);
        set("exits", ([
                  "east" : __DIR__"qianshou",
                  "westdown" : __DIR__"wroad",
        ]));
        set("objects", ([
                "/clone/npc/walker" : 1,
        ]));
        set("outdoors", "kaifeng");

	set("coor/x", -5060);
	set("coor/y", 2220);
	set("coor/z", 10);
	setup();
        replace_program(ROOM);
}