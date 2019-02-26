inherit ROOM;

void create()
{
        set("short", "景雲道");
        set("long", @LONG
景雲大道位於洛陽城裏的南面，是洛陽最繁華地段，青石板鋪成的街
面，寬闊而整潔，一到晚上，一派燈紅酒綠，尤為熱鬧。笑聲、歌聲、琴
聲、簫聲，匯成一片送入了你的耳朵，你不禁心猿意馬，很想就此停步享
受一番。東邊是一家雜貨鋪，提供人們日常生活所需的一些用品，西邊是
一個大戲院，供人消遣時間所用，不時的從戲院裏傳出陣陣叫好的聲音。
LONG);
        set("outdoors", "luoyang");
        set("no_clean_up", 0);
        set("exits", ([
                  "east" : __DIR__"xiyuan",
                  "south" : __DIR__"sroad5",
                  "north" : __DIR__"sroad3",
                  "west" : __DIR__"zahuopu",
        ]));

	set("coor/x", -6990);
	set("coor/y", 2140);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}