inherit ROOM;

void create()
{
        set("short", "景雲道");
        set("long", @LONG
景雲大道位于洛陽城裡的南面，是洛陽最繁華地段，青石板舖成的街
面，寬闊而整潔，一到晚上，一派燈紅酒綠，尤為熱鬧。笑聲、歌聲、琴
聲、簫聲，匯成一片送入了你的耳朵，你不禁心猿意馬，很想就此停步享
受一番。西邊是洛陽城赫赫有名的壺記茶樓。東邊則是一家老字號的藥店
-同仁堂。
LONG);
        set("outdoors", "luoyang");
        set("no_clean_up", 0);
        set("exits", ([
                  "east" : __DIR__"yaodian",
                  "south" : __DIR__"sroad3",
                  "north" : __DIR__"sroad1",
                  "west" : __DIR__"chalou",
        ]));
        set("objects", ([
                "/d/beijing/npc/old1" : 1,
                "/d/beijing/npc/girl4" : 1,
        ]));
	set("coor/x", -6990);
	set("coor/y", 2160);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}