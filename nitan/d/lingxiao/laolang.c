inherit ROOM;

void create()
{
        set("short", "監獄走廊");
        set("long", @LONG
這是凌霄城監獄的走廊，兩邊關的都是凌霄城犯了門規的弟
子。此處地下高低不平，兩邊都是巨石築成，一旦被關進來，就
別想逃得出去。牆上點著一支支火把，火光照得四周牆上的影子
象要擇人而噬的怪物一樣，看起來這種地方還是快走比較好。
LONG );
        set("no_clean_up", 0);

        set("exits", ([
                "up" : __DIR__"jianyuting",
                "west" : __DIR__"jianyusun",
                "east" : __DIR__"jianyuzhu",
                "down" : __DIR__"didi",
        ]));
        set("objects", ([ 
                __DIR__"npc/dizi" : 1,
        ])); 
        setup(); 
        replace_program(ROOM);
}
