inherit ROOM;

void create()
{
          set ("short", "雜貨鋪");
          set ("long", @LONG
這裏是中州城西的一家雜貨鋪，雖然店內的東西不少，可
因為地處的比較偏僻，所以生意也是冷冷清清。
LONG);

          set("exits", ([  
                    "south" : __DIR__"yanling1",
 
        ]));
        set("objects" , ([
                __DIR__"npc/zhaolaoban" : 1,
        ]));
        set("coor/x", -9060);
	set("coor/y", -990);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}