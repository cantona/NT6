inherit ROOM;

void create()
{
        set("short", "景雲道");
        set("long", @LONG
景雲大道位於洛陽城裏的南面，是洛陽最繁華地段，青石板鋪成的街
面，寬闊而整潔，一到晚上，一派燈紅酒綠，尤為熱鬧。笑聲、歌聲、琴
聲、簫聲，匯成一片送入了你的耳朵，你不禁心猿意馬，很想就此停步享
受一番。北邊是一個熱鬧的洛陽中心廣場。東邊是一家客棧，名曰“白馬
客棧”。西邊則是方圓千里之內最大的一家當鋪。
LONG);
        set("outdoors", "luoyang");
        set("no_clean_up", 0);
        set("exits", ([
                  "east" : __DIR__"kezhan",
                  "south" : __DIR__"sroad2",
                  "north" : __DIR__"center",
                  "west" : __DIR__"dangpu",
        ]));
        set("objects", ([
                "/d/beijing/npc/youren" : 1,
        ]));
	set("coor/x", -6990);
	set("coor/y", 2170);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}