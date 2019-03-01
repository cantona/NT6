// Room: /city/nandajie1.c
// YZC 1995/12/04 

inherit ROOM;

void create()
{
	set("short", "南大街");
        set("long", @LONG
南大街乃是城裡的繁華地段，一到晚上，一派燈紅酒綠，尤為熱
鬧。笑聲、歌聲、琴聲、簫聲，匯成一片送入了你的耳朵，你不禁心
猿意馬，很想就此停步享受一番。北邊是一個熱鬧的廣場。東邊是一
家店舖，牆上畫著個鬥大的『當』字，仔細傾聽，可以聽到壓低的討
價還價的聲音。西邊則是一片喧囂，歡呼聲、大罵聲不絕于耳，夾雜
著『一五一十』的數錢聲，原來那是方圓千裡之內最大的一家賭場。
LONG );
        set("outdoors", "city");
	set("exits", ([
		"east"  : "/d/city/dangpu",
		"south" : "/d/city/nandajie2",
		"west"  : "/d/city/duchang",
		"north" : "/d/city/guangchang",
	]));
	set("objects", ([
		"/d/city/npc/hunhun" : 1,
		"/d/city/npc/liumang": 4,
		"/d/city/npc/liumangtou" : 1,
		"/clone/npc/xunbu" : 1,
	]));

	set("coor/x", 0);
	set("coor/y", -10);
	set("coor/z", 0);
	setup();
	replace_program(ROOM);
}
