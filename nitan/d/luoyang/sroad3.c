inherit ROOM;

void create()
{
        set("short", "景雲道");
        set("long", @LONG
景雲大道位於洛陽城裏的南面，是洛陽最繁華地段，青石板鋪成的街
面，寬闊而整潔，一到晚上，一派燈紅酒綠，尤為熱鬧。笑聲、歌聲、琴
聲、簫聲，匯成一片送入了你的耳朵，你不禁心猿意馬，很想就此停步享
受一番。東邊是有錢人享受的地方-洪德浴池，而西邊則是賭徒們的樂土-
長樂坊。
LONG);
        set("outdoors", "luoyang");
        set("no_clean_up", 0);
        set("exits", ([
                  "east" : __DIR__"yuchi",
                  "south" : __DIR__"sroad4",
                  "north" : __DIR__"sroad2",
                  "west" : __DIR__"duchang",
        ]));
        set("objects", ([
                "/d/beijing/npc/haoke1" : 1,
        ]));
	set("coor/x", -6990);
	set("coor/y", 2150);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}