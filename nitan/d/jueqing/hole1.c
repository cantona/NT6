inherit ROOM;

void create()
{
        set("short", "潭底洞內");
        set("long", @LONG
鱷潭水氣蒸浸，洞中潮濕滑溜，腥臭難聞。
LONG);
        set("exits", ([
               "out"         : __DIR__"eyutan3",
               "northeast"   : __DIR__"hole2",
        ]));

       /* set("objects", ([
 
        ]));
       */

        set("no_clean_up", 0);

        setup();
        replace_program(ROOM);
}