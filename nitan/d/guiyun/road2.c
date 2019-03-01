// Room: /d/guiyun/road2.c
// Last Modified by winder on Jul. 9 2001

inherit ROOM;

void quarter_pass();

void create()
{
        set("short", "湖濱小路");
        set("long", @LONG
一條湖濱的小路，往東面看遠處似乎橫著一條小河。往北面看是一
條不知有多長的小路。西邊靠湖是個熱鬧的碼頭，南面是一家小酒館。
LONG );
        set("no_clean_up", 0);
        set("outdoors", "guiyun");

        set("exits", ([
                "west" : __DIR__"matou",
                "east" : __DIR__"riverw",
                "north": __DIR__"road3",
                "south": __DIR__"jiuguan",
        ]) );
        set("objects", ([
                "/d/village/npc/kid" : 1,
        ]) );
        set("coor/x", 290);
        set("coor/y", -860);
        set("coor/z", 0);
        setup();
        quarter_pass();
}

void quarter_pass()
{
//        mixed *local;
        string time = NATURE_D->game_time();
/*
        local = localtime(time() * 60);
        if (local[2] < 6 || local[2] >= 21)
*/
        if( strsrch(time, "子時") >= 0 ||
                strsrch(time, "醜時") >= 0 ||
                strsrch(time, "寅時") >= 0 ||
                strsrch(time, "戌時") >= 0 ||
                strsrch(time, "亥時") >= 0)
        {
                set("long", @LONG
一條湖濱的小路，往東面看遠處似乎橫著一條小河。往北面看是一
條不知條不知有多長的小路。西邊靠湖是個熱鬧的碼頭，南面是一家打
烊了的小酒館。
LONG
                );
                delete("exits/south");
        }
        else {
                set("long", @LONG
一條湖濱的小路，往東面看遠處似乎橫著一條小河。往北面看是一
條不知條不知有多長的小路。西邊靠湖是個熱鬧的碼頭，南面是一家開
著的小酒館。
LONG
                );
                set("exits/south", __DIR__"jiuguan");
        }
        call_out("quarter_pass", 30);
}