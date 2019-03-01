inherit ROOM;
 
void create()
{
        set("short", "小路");
        set("long", @LONG
這是一條通往後山的小徑。小路兩旁長滿了雜草。由于人們很少走這
條路，甚至連路中央也稀稀疏疏冒出了草芽。東邊有一個小山洞。
LONG );
        set("exits", ([
                "east"   : __DIR__"road4",
                "south"  : __DIR__"road2",
        ]));
        set("objects", ([
                "/clone/beast/dushe": 4,
        ]) );
        
        set("outdoors", "taohua");
       
        set("coor/x", 8980);
        set("coor/y", -2930);
        set("coor/z", 0);
        setup();
}