// Room: /d/wuxi/southroad1.c
// Winder 2000/02/22 

inherit ROOM;

void create()
{
        set("short", "南長街");
        set("long", @LONG
南長街乃是城裡的繁華地段，晚上一派燈紅酒綠。笑聲、歌聲、琴
聲、簫聲，匯成一片送入了你耳中，你不禁心猿意馬。北邊是一個熱鬧
的廣場。西邊是一家老字號的雜貨舖，東邊則傳出一股誘人的酒肉香氣，
那是江南有名的鬆鶴樓，裡面供應的無錫醬排骨更是名聞周邊，南邊是
江南運河，三鳳橋橫跨其上。
LONG );
        set("outdoors", "wuxi");
        set("exits", ([
                "south" : __DIR__"sanfengqiao",
                "north" : __DIR__"guangchang",
                "east"  : __DIR__"songhe",
                "west"  : __DIR__"zahuopu",
        ]));
        set("objects", ([
                        __DIR__"npc/lady1" : 1,
        ]));
        set("coor/x", 1040);
	set("coor/y", -740);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}