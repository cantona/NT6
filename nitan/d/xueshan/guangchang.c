inherit ROOM;

void create()
{
        set("short", "廣場");
        set("long", @LONG
 這裏是雪山寺內的廣場。廣場石埕鋪就，黃土墊砌，平整而堅實。
廣場的北面就是依山而建的雪山寺大殿。往西是塊練武場，南面是山
門。寺內有一些手持僧棍的僧兵在巡邏。
LONG );
        set("outdoors", "xueshan");
        set("exits", ([
                "east" : __DIR__"xiaoyuan",
                "west" : __DIR__"chang2",
                "north" : __DIR__"dadian",
                "south" : __DIR__"frontyard",
                "south" : "/d/xueshan/frontyard",
        ]));
        set("objects" , ([
                __DIR__"npc/seng-bing1"  : 4 ,
        ]));
        setup();
}