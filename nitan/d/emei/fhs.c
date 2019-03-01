inherit ROOM;

void create()
{
        set("short", "伏虎寺");
        set("long", @LONG
伏虎寺是入山第一大寶剎，隱伏在高大的喬木林間，四周楠木參
天，多達十萬余株。伏虎寺氣象莊嚴，規模宏盛，殿堂寬敞，勢度巍
峨。寺剎雖掩覆于翠綠濃黛之中，但瓦卻無一片落葉。出寺西上解脫
坡便是觀音堂。
LONG );
        set("objects", ([
                __DIR__"npc/boydizi" : 1,
                __DIR__"npc/girldizi" : 1,
        ]));
        set("exits", ([
                "east"   : __DIR__"milin1",
                "westup" : __DIR__"milin2",
        ]));
        set("outdoors", "emei");
        set("coor/x", -380);
        set("coor/y", -230);
        set("coor/z", 10);
        setup();
        replace_program(ROOM);
}