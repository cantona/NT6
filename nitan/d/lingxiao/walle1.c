// walle1.c

inherit ROOM;

void create()
{
        set("short", "城頭");
        set("long", @LONG 
這是凌霄城的城頭，從這極目遠望，只見萬里雪山，一片蒼
茫。黃雲萬丈之下，無數起伏的山脈向東奔騰而去。沉寂的雪嶺
之間，只偶爾傳來一陣陣狼嗷。
LONG );
        set("outdoors", "lingxiao");
        set("no_clean_up", 0);

        set("exits", ([
                "east"   : __DIR__"walle2",
                "westdown" : __DIR__"gate",
        ]));
        set("objects", ([
                __DIR__"npc/dizi" : 1,
        ])); 
        setup();
        replace_program(ROOM);
}
