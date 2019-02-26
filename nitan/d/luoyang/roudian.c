inherit ROOM;

void create()
{
        set("short", "豬肉鋪");
        set("long", @LONG
髒稀稀的木板上放着幾塊顏色灰暗，不堪入目的生肉。一堆綠頭蒼蠅
忙忙碌碌的飛起飛落。幾個生了鏽的鐵勾上掛着半風乾了的羊頭，豬頭，
和牛頭。櫃枱的左角兒放着幾個木匣，匣中放着些煮熟了的雜碎和排骨。
LONG);
        set("outdoors", "luoyang");
        set("no_clean_up", 0);
        set("exits", ([
                  "west" : __DIR__"zashua",
                  "south" : __DIR__"wanju",
                  "east" : __DIR__"hutong3",
        ]));
        set("objects", ([
                "/d/beijing/npc/old1" : 1,
        ]));
	set("coor/x", -6950);
	set("coor/y", 2180);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}