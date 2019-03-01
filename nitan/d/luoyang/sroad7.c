inherit ROOM;

void create()
{
        set("short", "景雲道");
        set("long", @LONG
景雲大道位于洛陽城裡的南面，是洛陽最繁華地段，青石板舖成的街
面，寬闊而整潔，一到晚上，一派燈紅酒綠，尤為熱鬧。笑聲、歌聲、琴
聲、簫聲，匯成一片送入了你的耳朵，你不禁心猿意馬，很想就此停步享
受一番。再往南就要到南內城門了，遠遠望去，可以看見守城的官兵正在
檢查排隊出城的路人。這裡的東邊是一間花店，在裡面你可以買到名滿天
下的洛陽牡丹，西邊是魯氏木器店。
LONG);
        set("outdoors", "luoyang");
        set("no_clean_up", 0);
        set("exits", ([
                  "east" : __DIR__"miaopu",
                  "north" : __DIR__"sroad6",
                  "south" : __DIR__"nandoor",
                  "west" : __DIR__"muqipu",
        ]));

	set("coor/x", -6990);
	set("coor/y", 2110);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}