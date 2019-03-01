inherit ROOM;

void create()
{
        set("short", "內殿");
        set("long", @LONG
 這裡是雪山寺的內殿，也是掌門人見客的地方。雪山寺的掌門人、
貴為蒙古國師的金輪法王是西域一代高僧，也是西域不世出的武林宗
   師。他駐錫本寺後，雪山寺方聲名遠播。
LONG );
        set("exits", ([
                "east"  : __DIR__"zoulang3",
                "west"  : __DIR__"zoulang4",
                "north" : __DIR__"houdian",
        ]));

        set("objects", ([
                CLASS_D("xueshan") + "/fawang" : 1
        ]));

        setup();
        replace_program(ROOM);
}