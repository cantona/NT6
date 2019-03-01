inherit ROOM;

void create()
{
        set("short", "開封鐵塔");
        set("long", @LONG
塔高五十五米，八角十三層。當年此地為宋開寶寺，故又名『開
寶寺塔』，塔身為褐色琉璃磚砌成混私鐵鑄，民間俗稱其為鐵塔。塔
身修長，氣勢雄偉，磚面飾以飛天、佛像、樂伎等數十種圖案，栩栩
如生。
LONG );
        set("outdoors", "kaifeng");
        set("exits", ([
                "west" : __DIR__"jieying",
                "east" : __DIR__"eroad3",
        ]));
        set("objects", ([
        ]));
        set("no_clean_up", 0);
	set("coor/x", -5040);
	set("coor/y", 2250);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}