inherit ROOM;

void create()
{
        set("short", "山神廟");
        set("long", @LONG
這是一個用木板和石頭壘成的小廟，廟前地上散落着一些然過的灰燼。
廟裏供奉着山神爺老把頭的靈位(lingwei)。傳説他是所有采參人的祖師爺，
所以每個進山挖參的參客都要來這裏祭拜，希望能得到他老人家的保佑。
LONG );
        set("item_desc", ([
                "lingwei"  : 
"
**************
*            *
*     山     *
*     神     *
*     爺     *
*     老     *
*     把     *
*     頭     *
*            *
*     孫     *
*     良     *
*            *
*     之     *
*     位     *
*            *
**************
"
        ]));
        set("exits", ([
                "out"  : __DIR__"huandi2",
        ]));
        set("objects", ([
                __DIR__"npc/yanji" : 1,
                "/clone/npc/walker" : 1,
        ]));
        set("outdoors", "guanwai");
        set("coor/x", 4019);
	set("coor/y", 9259);
	set("coor/z", -1);
	setup();
        replace_program(ROOM);
}