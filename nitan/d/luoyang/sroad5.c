inherit ROOM;

void create()
{
        set("short", "景雲道");
        set("long", @LONG
景雲大道位于洛陽城裡的南面，是洛陽最繁華地段，青石板舖成的街
面，寬闊而整潔，一到晚上，一派燈紅酒綠，尤為熱鬧。笑聲、歌聲、琴
聲、簫聲，匯成一片送入了你的耳朵，你不禁心猿意馬，很想就此停步享
受一番。走到這裡，你突然感到一股強烈的胭脂花粉味從東面傳來，原來
那裡就是洛陽名樓-春月樓，西邊是一間打鐵舖，整天到晚叮叮咚咚響個
不停。
LONG);
        set("outdoors", "luoyang");
        set("no_clean_up", 0);
        set("exits", ([
                  "east" : __DIR__"jiyuan",
                  "south" : __DIR__"sroad6",
                  "west" : __DIR__"datie",
                  "north" : __DIR__"sroad4",
        ]));
        set("objects", ([
                "/d/beijing/npc/piaoke" : 1,
        ]));
	set("coor/x", -6990);
	set("coor/y", 2130);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}