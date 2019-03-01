// wallw2.c

inherit ROOM;

void create()
{
        set("short", "城頭");
        set("long", @LONG 
高處不勝寒。不只是雪，連霜也紛紛而下。頭天晚上還是石
城木垛，一下子就霜雪漫天，萬物俱白。古詩雲‘天涯霜雪霽寒
霄’。大概也就是這個意思吧。
LONG );
        set("outdoors", "lingxiao");
        set("no_clean_up", 0);

        set("exits", ([
                "west" : __DIR__"wallw3",
                "east" : __DIR__"wallw1",
        ]));
        set("objects", ([
                __DIR__"npc/dizi" : 1,
        ])); 
        setup(); 
        replace_program(ROOM);
}
