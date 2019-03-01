inherit ROOM;

void create()
{
        set("short", "景雲道");
        set("long", @LONG
景雲大道位于洛陽城裡的南面，是洛陽最繁華地段，青石板舖成的街
面，寬闊而整潔，一到晚上，一派燈紅酒綠，尤為熱鬧。笑聲、歌聲、琴
聲、簫聲，匯成一片送入了你的耳朵，你不禁心猿意馬，很想就此停步享
受一番。東邊是一家首飾店，裡面擺滿了金銀珠寶，西邊的水果店，常年
有新鮮水果供應。
LONG);
        set("outdoors", "luoyang");
        set("no_clean_up", 0);
        set("exits", ([
                  "east" : __DIR__"shoushi",
                  "south" : __DIR__"sroad7",
                  "west" : __DIR__"shuiguo",
                  "north" : __DIR__"sroad5",
        ]));

	set("coor/x", -6990);
	set("coor/y", 2120);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}